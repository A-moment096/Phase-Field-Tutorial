## Heat Transfer Simulation

### Introduction
In this part, we are going to calculate the one dimensional heat transfer equation:

$$
 \frac{\partial T}{\partial t} = \mu \frac{\partial ^2 T}{\partial x^2};
$$
$$
\mu = \frac{\lambda}{\rho c_p},
$$

which is from the book *Programming Phase-Field Modeling*, Chapter 4.2.

### Headers and Global Constants
First, we include some headers and define some global variables.
```cpp
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
```

The following parameters are from the example.
```cpp
const int Nx = 128; // The cell dimension
const double dx = 1.0;
const double dt = 0.2;
const double mu = 1.0; // \mu = \frac{\lambda}{\rho c_p}
const int nstep = 30000;
const int pstep = 200; // Print step (0, 200, 400, 600)
```

### Main functions
And here is the `main` function we are going to use. We don't define
any outside function here. 

We will, again, break this function in parts.
Please remember that the code blocks below should be considered as a whole.
#### Preparation
First, we prepare things not tightly related with the simulation, such as
time counter, data output, file storage and so on. 
```cpp
int main() {
    // Time counter, record the begin time of this program.
    auto begin_time{std::chrono::high_resolution_clock::now()};
    // Set a string as the folder's name
    std::string result_dir{"./results/"};
    // Create a folder named "results" to hold the results
    std::filesystem::create_directories(result_dir);

    // Set an empty string to hold different file name for different type of BC.
    std::string result_type{};
```
#### Mesh Initialization

Here we declare and initialize two `vector`s, one of which will hold the data of grid
in present step, and another one will hold the data in the next step.
```cpp

    // Initialize the grid:
    std::vector<double> mesh(Nx, 0.0);
    for (int i = 0; i < Nx; i++) {
        if (i >= 44 && i <= 84) {
            mesh.at(i) = 1.0;
        }
    }
    // Use temp_mesh to hold the result calculated for next step
    std::vector<double> temp_mesh(mesh);
```

#### Double Loop

Now we shall start the simulation.

We shall have three loop: one loop for time dimension, and one loop for the 1D space.

The time loop will be the outmost one, and suppose any other things we calculate will
happen inside of this little time step.

```cpp
    // Time loop (in nstep):
    for (int istep = 0; istep < nstep + 1; istep++) {

        // loop each point (in Nx):
        for (int i = 0; i < Nx; i++) {
```
#### Boundary Assignment
Here we use fixed boundary condition and fix the value to 0. 
```cpp
            int im = i - 1;
            int ip = i + 1;
            double val_m{0.0}, val_p{0.0};

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
```
#### Calculation
The double partial differential is discretized as
$$\dfrac{(T_{i+1} + T_{i-1} - 2 T_i)}{dx^2}$$
So the result will be:
```cpp
            temp_mesh.at(i) = mesh.at(i) + mu * dt * ((val_m + val_p - 2.0 * mesh.at(i)) / (dx * dx));
        }
        
```
And one loop should be ended here, because after this loop, each points are traveled though and calculated. 
#### Assign New Results
After all points are calculated, the result stroed for the next step should be assigned to the last step,
that is, assign the value of `temp_mesh` to the `mesh`.
```cpp
        mesh = temp_mesh;
```
#### Output into files
We can't output each step's result as that will cost too much time, and we only want to grab the essiential
result from the simulation. So here, we choose to output the result every `pstep` step. You can modify the
number stored inside `pstep` to control the frequency of data output.

```cpp
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
```
#### End Simulation
After all the time steps are iterated, the main simulation is finished. As we set the time counter before, we can
have a look at the time cost of this simulation.
```cpp
    // Time counter, record the end time of this program.
    auto end_time{std::chrono::high_resolution_clock::now()};
    // Calculate time duration and cast to double type, then count the time and print it out.
    std::cout << "The time cost in this simulation is " << std::chrono::duration<double>(end_time - begin_time).count() << "s\n";
    // for "main" function, "return 0;" is optional.
    return 0;
}
```

### Results

After you execute this program, you will see a new folder (or maybe you already have this folder) named
"results", and inside of this folder there will be a lot of files named as "fixed_step_xxx.csv". Those
are the results of this program, and you can visualize the result with methods you like.

Here I recommend the following ways:
- Using Python to plot the results. You can utilize the `matplotlib` module to plot the results after using `pandas` or `np.loadtxt` to load the data from csv file to the program.
- Using Paraview to visualize the result. Paraview have built-in CSV file parser, and can plot the result very quickly. It can also display animation with group of files. We shall use this software after to visualize the phase field simulation results in the future.
- Using other program, such as MATLAB or Wolfram Mathematica to do the curve plotting if you are familar to these software.

And, the exercise for this tutorial is as follows:

### Exercise

Now that you have this code, please do some modifications and then execute it to see the effects.

First will be some aspect about C++ language:

1. Please modify the code structure, such that the **calculation step** is packaged inside of a function;
2. Please package the **file output step** into another function to make the `main` function neat and well structured.
3. *Optional:* If you like, please try to use class to package the data structure we used here, mainly the mesh we used to store the value and the method to calculate the laplacian (or, the calculation step).
4. *Optional:* If you like, please try to make this code interactive. That is, you can input the parameters from the outside of the program, such that you don't have to modify this source code when you just want to modify some parameters.

Then there are still more things you can do with C++ language only. You even can write a Python script to plot the result and save the figures, and then call this script inside of this C++ program to output the processed images directly, instead of output raw data. But, let's stop language part.

Below are exercises mainly about this simulation (some language things are involved):

1. The boundary condition used here is fixed boundary condition. Please modify this boundary condition, run the simulation and compare the results with the fixed boundary condition. Here you are encouraged to try different boundary conditions, like fix the boundary value to other values; try some dynamic boundaries (such that boundary value will change with time but fixed). And of course, you are welcomed to just try the periodic boundaries, which we have encountered many times.
2. Here we initialized the mesh with the central points' value to 1.0, and value of other part are zero. Please modify the initial value distribution and compare that with the original result. Please notice that you'd better do this under the same boundary conditions.
3. Please modify the parameter of the heat transfer model, namely the $\mu$ inside of this model, and compare the result with the original result.
4. *Optional:* If you like, please try to consider the parameter $\mu$ as a function of time or temperature, and implement it to see the result.
5. *Optional:* If you like, please add another term on the right hand side of the governing equation. The term you add might be considered as a heat source. For example, you can set it as a constant value, meaning that this heat source will contribute heat constantly despite the time influence. Or it can change with time, say, gradually decreasing as the time goes. You can even set this heat source as a function of time and *space* to localize the influence of this heat source. There are so much you can do to this equation.

As exercises, I hope you will find them easy to follow, simple to finish, and interesting to explore. After finishing these exercises, I believe you can start your jounary of Phase-Field simulation. And in the next tutorial, we will together have a look at the first case study, the spinodal decomposition simulation. 
