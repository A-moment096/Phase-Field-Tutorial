#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

double laplacian(double eta_l, double eta_r, double eta_d, double eta_u, double eta_c, double dx) {
    return (eta_l + eta_r + eta_d + eta_u - 4.0 * eta_c) / (dx * dx);
}

double df_deta(double A, double B, double eta_square_sum, double this_eta) {
    return -1.0 * A * this_eta + B * this_eta * this_eta * this_eta + 2.0 * this_eta * (eta_square_sum - this_eta * this_eta);
}

std::ofstream create_vtk(std::string file_path, int time_step) {
    std::filesystem::create_directory(file_path);
    std::filesystem::path f_name{"step_" + std::to_string(time_step) + ".vtk"};
    f_name = file_path / f_name;

    std::ofstream ofs{f_name};
    return ofs;
}

void write_vtk_head(std::ofstream &ofs, std::string filename, double dx, size_t Nx, size_t Ny) {
    ofs << "# vtk DataFile Version 3.0\n";
    ofs << filename << std::endl;
    ofs << "ASCII\n";
    ofs << "DATASET STRUCTURED_GRID\n";

    ofs << "DIMENSIONS " << Nx << " " << Ny << " " << 1 << "\n";
    ofs << "POINTS " << Nx * Ny * 1 << " float\n";

    for (size_t i = 0; i < Nx; i++) {
        for (size_t j = 0; j < Ny; j++) {
            ofs << (double)i * dx << " " << (double)j * dx << " " << 1 << std::endl;
        }
    }
    ofs.close();
}

void write_vtk_data(std::vector<std::vector<double>> mesh, std::ofstream &ofs, std::string data_label, double dx) {
    size_t Nx{mesh.size()}, Ny{mesh.at(0).size()};
    ofs << "POINT_DATA " << Nx * Ny * 1 << std::endl;

    ofs << "SCALARS " << data_label << "float 1\n";
    ofs << "LOOKUP_TABLE default\n";
    for (size_t i = 0; i < Nx; i++) {
        for (size_t j = 0; j < Ny; j++) {
            ofs << mesh.at(i).at(j) << std::endl;
        }
    }
}
int main() {
    int Nx = 64;
    double dx = 0.5;
    double dt = 0.005;
    int nstep = 20000, pstep = 100;
    int radius = 7;
    double mobility = 5.0;
    double kappa = 0.1;
    double A = 1.0, B = 1.0;

    std::vector<std::vector<double>> grain_1(Nx, std::vector<double>(Nx, 0.0));
    auto grain_2 = grain_1;

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Nx; j++) {
            if ((i - Nx / 2) * (i - Nx / 2) + (j - Nx / 2) * (j - Nx / 2) <= radius * radius) {
                grain_1.at(i).at(j) = 1.0;
                grain_2.at(i).at(j) = 0.0;
            } else {
                grain_1.at(i).at(j) = 0.0;
                grain_2.at(i).at(j) = 1.0;
            }
        }
    }

    std::vector<std::vector<std::vector<double>>> grains = {grain_1, grain_2};
    std::vector<std::vector<std::vector<double>>> grains_temp = {grain_1, grain_2};

    for (int istep = 0; istep < nstep; istep++) {
        std::vector<std::vector<double>> grain_square_sum(Nx, std::vector<double>(Nx, 0.0));
        for (int igrain = 0; igrain < 2; igrain++) {
            for (int i = 0; i < Nx; i++) {
                for (int j = 0; j < Nx; j++) {
                    grain_square_sum.at(i).at(j) = grains.at(igrain).at(i).at(j) * grains.at(igrain).at(i).at(j);
                }
            }
        }
        for (int igrain = 0; igrain < 2; igrain++) {
            for (int i = 0; i < Nx; i++) {
                for (int j = 0; j < Nx; j++) {
                    int im = i - 1, ip = i + 1, jm = j - 1, jp = j + 1;
                    if (im == -1) {
                        im = Nx - 1;
                    }
                    if (jm == -1) {
                        jm = Nx - 1;
                    }
                    if (ip == Nx) {
                        ip = 0;
                    }
                    if (jp == Nx) {
                        jp = 0;
                    }
                    double eta_l = grains.at(igrain).at(im).at(j);
                    double eta_r = grains.at(igrain).at(ip).at(j);
                    double eta_d = grains.at(igrain).at(i).at(jm);
                    double eta_u = grains.at(igrain).at(i).at(jp);
                    double eta_c = grains.at(igrain).at(i).at(j);

                    grains_temp.at(igrain).at(i).at(j) = eta_c - 1.0 * dt * mobility * (df_deta(A, B, grain_square_sum.at(i).at(j), eta_c) - kappa * laplacian(eta_l, eta_r, eta_d, eta_u, eta_c, dx));
                }
            }
        }
        grains = grains_temp;

        if (istep % pstep == 0) {
            auto ofs = create_vtk("./result", istep);
            write_vtk_head(ofs, "step_" + std::to_string(istep), dx, Nx, Nx);
            write_vtk_data(grains.at(0), ofs, "grain_1", dx);
            write_vtk_data(grains.at(1), ofs, "grain_2", dx);
        }
    }
}