/*
In this part, we are going to calculate the one dimensional heat transfer equation:

$$
 \frac{\partial T}{\partial t} = \mu \frac{\partial ^2 T}{\partial x^2};
$$
$$
\mu = \frac{\lambda}{\rho c_p},
$$

which is from the book *Programming Phase-Field Modeling*, Chapter 4.2.

First, we include some headers and define some global variables.
*/
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// The following parameters are from the example.
const int Nx = 128; // The cell dimension
const double dx = 1.0;
const double dt = 0.2;
const double mu = 1.0; // \mu = \frac{\lambda}{\rho c_p}
const int nstep = 30000;
const int pstep = 200; // Print step (0, 200, 400, 600)

// And here is the `main` function we are going to use. We don't define
// any outside function here.

int main() {
    // Time counter, record the begin time of this program.
    auto begin_time{std::chrono::high_resolution_clock::now()};
    // Set a string as the folder's name
    std::string result_dir{"./results/"};
    // Create a folder named "results" to hold the results
    std::filesystem::create_directories(result_dir);

    // Set an empty string to hold different file name for different type of BC.
    std::string result_type{};

    // Initialize the grid:
    std::vector<double> mesh(Nx, 0.0);
    for (int i = 0; i < Nx; i++) {
        if (i >= 44 && i <= 84) {
            mesh.at(i) = 1.0;
        }
    }
    // Use temp_mesh to hold the result calculated for next step
    std::vector<double> temp_mesh(mesh);
    // ----- Begin Simulation ----- //

    // Time loop (in nstep):
    for (int istep = 0; istep < nstep + 1; istep++) {

        // loop each point (in Nx):
        for (int i = 0; i < Nx; i++) {
            int im = i - 1;
            int ip = i + 1;
            double val_m{0.0}, val_p{0.0};

            // Assign BC according to bound_type
            // Fixed boundary condition (to 0)
            if (-1 == im) {
                val_m = 0.0;
            } else {
                val_m = mesh.at(im);
            }
            if (Nx == ip) {
                val_p = 0.0;
            } else {
                val_p = mesh.at(ip);
            }
            result_type = "fixed_step_";

            // Calculate:
            // The double partial differential is discretized as
            // (T_{i+1} + T_{i-1} - 2 T_i)/ dx^2
            // So the result will be:
            temp_mesh.at(i) = mesh.at(i) + mu * dt * ((val_m + val_p - 2.0 * mesh.at(i)) / (dx * dx));
        }
        // Assign the new step result in temp_mesh to mesh
        mesh = temp_mesh;

        // Every pstep, output the results to a file with specific names.
        if (istep % pstep == 0) {
            // Concatenate the file name. Create CSV file.
            std::string of_name{result_dir + result_type + std::to_string(istep) + ".csv"};
            // Open a file
            std::ofstream ofs(of_name);
            // If the file is indeed opened
            if (ofs) {
                // First line will indicate the columns
                ofs << "pos" << "," << "val" << std::endl;
                for (int i = 0.0; i < Nx; i += 1) {
                    ofs << i << "," << mesh.at(i) << std::endl;
                }
                // Close the file after write
                ofs.close();
            }
        }
        // End of one timestep;
    }

    // Time counter, record the end time of this program.
    auto end_time{std::chrono::high_resolution_clock::now()};
    // Calculate time duration and cast to double type, then count the time and print it out.
    std::cout << "The time cost in this simulation is " << std::chrono::duration<double>(end_time - begin_time).count() << "s\n";
    // for "main" function, "return 0;" is optional.
    return 0;
}

/*
After you execute this program, you will see a new folder 
(or maybe you already have this folder) named
"results", and inside of this folder there will be a lot of files named 
as "fixed_step_xxx.csv". Those are the results of this program, and you 
can visualize the result with methods you like.

Here I recommend the following ways:
- Using Python to plot the results. You can utilize the `matplotlib` 
    module to plot the results after using `pandas` or `np.loadtxt` to 
    load the data from csv file to the program.
- Using Paraview to visualize the result. Paraview have built-in CSV 
    file parser, and can plot the result very quickly. It can also 
    display animation with group of files. We shall use this software 
    after to visualize the phase field simulation results in the future.
- Using other program, such as MATLAB or Wolfram Mathematica to do 
    the curve plotting if you are familar to these software.

*/
