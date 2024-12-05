#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void write_vtk(std::vector<std::vector<double>> mesh, std::string file_path, int time_step, double dx) {
    std::filesystem::create_directory(file_path);
    std::filesystem::path f_name{"step_" + std::to_string(time_step) + ".vtk"};
    f_name = file_path / f_name;

    std::ofstream ofs{f_name};
    size_t Nx{mesh.size()}, Ny{mesh.at(0).size()};

    ofs << "# vtk DataFile Version 3.0\n";
    ofs << f_name.string() << std::endl;
    ofs << "ASCII\n";
    ofs << "DATASET STRUCTURED_GRID\n";

    ofs << "DIMENSIONS " << Nx << " " << Ny << " " << 1 << "\n";
    ofs << "POINTS " << Nx * Ny * 1 << " float\n";

    for (size_t i = 0; i < Nx; i++) {
        for (size_t j = 0; j < Ny; j++) {
            ofs << (double)i * dx << " " << (double)j * dx << " " << 1 << std::endl;
        }
    }
    ofs << "POINT_DATA " << Nx * Ny * 1 << std::endl;

    ofs << "SCALARS " << "CON " << "float 1\n";
    ofs << "LOOKUP_TABLE default\n";
    for (size_t i = 0; i < Nx; i++) {
        for (size_t j = 0; j < Ny; j++) {
            ofs << mesh.at(i).at(j) << std::endl;
        }
    }

    ofs.close();
}

void energy_curve(std::vector<double> f_list, double kappa, std::string file_path, int pstep) {
    std::filesystem::create_directory(file_path);
    std::filesystem::path f_name{"energy_time.csv"};
    f_name = file_path / f_name;

    std::ofstream ofs;
    ofs.open(f_name);
    ofs << "time" << "," << "value\n";
    for (size_t i = 0; i < f_list.size(); i++) {
        ofs << i * pstep << "," << f_list.at(i) << std::endl;
    }
    ofs.close();
}

double laplacian(double cl, double cr, double cd, double cu, double cc, double dx) {
    return (cl + cr + cd + cu - 4.0 * cc) / (dx * dx);
}

double df_dc(double mu, double kappa, double lap_c) {
    return mu - kappa * lap_c;
}

double chem_potential(double A, double c) {
    return 2.0 * A * (c * (1 - c) * (1 - c) - c * c * (1 - c));
}

double chem_energy(double A, double c) {
    return A * c * c * (1 - c) * (1 - c);
}

double F_total(std::vector<std::vector<double>> mesh, double kappa, double A) {
    double energy{0};

    for (size_t i = 0; i < mesh.size() - 1; i++) {
        for (size_t j = 0; j < mesh.at(0).size() - 1; j++) {
            double cc = mesh.at(i).at(j);
            double cr = mesh.at(i + 1).at(j);
            double cu = mesh.at(i).at(j + 1);

            energy += (cr - cc) * (cr - cc) * kappa / 2.0;
            energy += (cu - cc) * (cu - cc) * kappa / 2.0;
            energy += chem_energy(A, cc);
        }
    }
    return energy;
}

const int Nx = 64;
const double dx = 1.0;
const double dt = 0.01;
const int nstep = 10000;
const int pstep = 50;
const double c0 = 0.4;
// const double dc = 0.1;
const double mobility = 1.0;
const double kappa = 0.5;
const double A = 1.0;

int main() {

    std::vector<std::vector<double>> mesh(Nx, std::vector<double>(Nx, 0));
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Nx; j++) {
            mesh.at(i).at(j) = c0 + (double)(100 - rand() % 200) / 1000.0;
        }
    }
    std::vector<double> F_time_curve{};

    auto df_dc_mesh{mesh};

    for (int istep = 0; istep < nstep + 1; istep++) {
        for (int i = 0; i < Nx; i++) {
            for (int j = 0; j < Nx; j++) {
                int im = i - 1;
                if (im == -1)
                    im = Nx - 1;
                int ip = i + 1;
                if (ip == Nx)
                    ip = 0;
                int jm = j - 1;
                if (jm == -1)
                    jm = Nx - 1;
                int jp = j + 1;
                if (jp == Nx)
                    jp = 0;
                double cl{mesh.at(im).at(j)};
                double cr{mesh.at(ip).at(j)};
                double cd{mesh.at(i).at(jm)};
                double cu{mesh.at(i).at(jp)};
                double cc{mesh.at(i).at(j)};

                df_dc_mesh.at(i).at(j) = df_dc(chem_potential(A, cc), kappa, laplacian(cl, cr, cd, cu, cc, dx));
            }
        }
        for (int i = 0; i < Nx; i++) {
            for (int j = 0; j < Nx; j++) {
                int im = i - 1;
                int ip = i + 1;
                int jm = j - 1;
                int jp = j + 1;
                if (im == -1)
                    im = Nx - 1;
                if (ip == Nx)
                    ip = 0;
                if (jm == -1)
                    jm = Nx - 1;
                if (jp == Nx)
                    jp = 0;
                double df_dc_l{df_dc_mesh.at(im).at(j)};
                double df_dc_r{df_dc_mesh.at(ip).at(j)};
                double df_dc_d{df_dc_mesh.at(i).at(jm)};
                double df_dc_u{df_dc_mesh.at(i).at(jp)};
                double df_dc_c{df_dc_mesh.at(i).at(j)};

                mesh.at(i).at(j) += dt * mobility * laplacian(df_dc_l, df_dc_r, df_dc_d, df_dc_u, df_dc_c, dx);
            }
        }
        if (istep % pstep == 0) {
            write_vtk(mesh, "./result", istep, dx);
            F_time_curve.push_back(F_total(mesh, kappa, A));
            // F_time_curve.push_back(ENERGY(Nx, Nx, mesh, kappa));
        }
    }
    energy_curve(F_time_curve, kappa, "./result", pstep);
}