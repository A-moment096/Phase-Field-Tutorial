/*
In this part we are going to go over some algorithms and implement
them in C++. To be honest, it's nothing but some similar
codes like Python, and nearly nothing new will appear in this part,
aside from some syntax difference between C++ and Python.
However, as C++ is a little too low-level, there is (as I know) no
good visualisation library in C++ that one can use them easily to
draw some beautiful graphs or figures.

But that's fine because we can still write things inside a text file,
and plot the curve or figure in other way, for example, Python. Here we
will focuse on implementing these algorithms.

So, the algorithms we have implemented are:
1. Forward (and Backward, if you finished exercise) Euler method;
2. Numerical integration (including Riemann, Quadrature, Simpson, Newton-Cotes)
3. Nabla operator ( gradient and laplacian )

Let's start it.
*/

// Here, <fstream> is for output to file;
// <sstream> is for string processing.
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// --- SUBPART I --- //
/*
Let's implement the Forward Euler Method first. Remember the formula
for this method? You just move the step length to the RHS (right hand side)
of the equation, which should be known from the last step calculation,
and then move the last calculated term to the RHS.

Then you will get:
LHS: The next step value of the result of your ODE/PDE;
RHS: The last step value of the result of your ODE/PDE.

And just store the next step value, using it in the next step, you finish
the Forward Euler Method.

Let's do it:
*/

// We will define a function, call it ForwardEuler.

// It should take a function
// as RHS of the ODE/PDE, a triple tuple to indicate start point, time step,
// and end point, and finally the initial value of the result function at
// the start point.

// Then this function should return a double vector as the result of the
// calculated result.

// To take a function as parameter, you just input the "type" of a function
// inside the parameter list, which is:
//              return_type fun_name(param_type1, param_type2, ...);
// You can see how to do it below:

// As the function on the RHS of the first order ODE should be taking time
// step and possibly the result function value of the last step, then output
// the result, hence RHS is defined as "double RHS(double, double)".

std::vector<double> ForwardEuler(double RHS(double, double), std::array<double, 3> x_axis, double init_val) {
    // initialize a result vector with the first value as initial_val
    std::vector<double> result{init_val};
    // Calculate the number of steps: (end - start)/dx
    int num_steps{(x_axis.at(2) - x_axis.at(0)) / x_axis.at(1)}; // Here happens auto convert from double to int

    for (int i = 0; i < num_steps; i++) {
        double u_last = result.at(i);                 // Find the last step result's value;
        double next_step = RHS(x_axis.at(1), u_last); // Calculate RHS;
        next_step *= x_axis.at(1);                    // RHS * dx
        next_step += u_last;                          // RHS * dx + u_last
        result.push_back(next_step);                  // u_this = RHS * dx + u_last
    }
    return result;
}

// So by using this function, you are able to integrate first order ODE with form
//              dy/dx = F(x,y)
// In practice, you can either write it as a function, or implement it just inside
// your main code. Now we shall move to another part.

//  --- SUBPART II --- //
/*
Now we are going to using C++ to implement the integral. Here we implement the
integrate algorithm for single variable function, y = f(x), with again 4 algorithms.

This algorithm should take a function and a triple tuple as parameters ... But wait,
there is a question about the "triple tuple": We must remember the mean of the value
inside of the array by ourselves. That's not the best practice as the code could be
hard to maintain.

To deal with this problem, here we introduce: "struct" and structure binding. We
can create a simple type (struct) called "x_axis" and then let this type stores three
values: begin_point, dx and end_point:
*/
struct x_axis {
    double begin_point{};
    double dx{};
    double end_point{};
};
/*
And then you can create a variable with type "x_axis", then config its detail values by
using ".", the dot operator, to get the properties. Just like what you have done in
Python's CLASS! (Actually, struct and class in C++ have only one difference: defalut
member access flag of class is private (access only by inside members), and that for
struct is public (everyone can access the inside members))

Now you can use this struct to write better code. Let's first implement the "Riemannian" way
to integrate a function:
*/

double RiemannIntegral(double fun(double), x_axis x) {
    double result{0};
    for (double x_step{x.begin_point}; x_step < x.end_point; x_step += x.dx) {
        result += fun(x_step);
    }
    result *= x.dx;
    return result;
}

// Quadrature way from interpolation polynomial:
double QuadratureIntegral(double fun(double), x_axis x) {
    double result{0};
    for (double x_step{x.begin_point}; x_step < x.end_point; x_step += x.dx) {
        result += fun(x_step);
    }
    result -= (fun(x.begin_point) + fun(x.end_point)) / 2.0;
    result *= x.dx;
    return result;
}

// Simpson formula:
double SimpsonIntegral(double fun(double), x_axis x) {
    double result{0};
    for (double x_step{x.begin_point}; x_step < x.end_point; x_step += x.dx) {
        result += fun(x_step) * 2;
        result += fun(x_step + 0.5 * x.dx) * 4;
    }
    result -= (fun(x.begin_point) + fun(x.end_point));
    result *= x.dx / 6.0;
    return result;
}

// Newton-Cotes formula:
double NCIntegral(double fun(double), x_axis x) {
    double result{0};
    for (double x_step{x.begin_point}; x_step < x.end_point; x_step += x.dx) {
        result += fun(x_step) * 14;
        result += fun(x_step + 0.25 * x.dx) * 32;
        result += fun(x_step + 0.5 * x.dx) * 12;
        result += fun(x_step + 0.75 * x.dx) * 32;
    }
    result -= (fun(x.begin_point) + fun(x.end_point)) * 7.0;
    result *= x.dx / 90.0;
    return result;
}

// The underlying algorithm doesn't change during the transformation from
// Python code to C++ code. You can use these function freely to integrate
// some single variable functions.

//  --- SUBPART II --- //
/*
Now we are going to implement the algorithm calculating the gradient and
laplacian of a mesh. This time we prefer not using the class and methods, just calculate
using normal function, and store these data inside simple variable, such as
vectors and so on.

So, for function calculating gradient, it will accept a 2D vector of double value,
and output a vector of two double values as gradients of x and y direction. To
store the value efficiently, we create a small struct called "gradient":
*/
struct gradient {
    double x_grad{};
    double y_grad{};
};
/*
And for function calculating laplacian, its parameter and return value are both vector of
double value. Now let's implement these two functions. Here we use the periodic boundary
condition:
*/

// Nabla, Gradient:
std::vector<std::vector<gradient>> cal_grad(std::vector<std::vector<double>> mesh, double dx) {
    int Nx{mesh.size()}, Ny{mesh.at(0).size()};
    gradient grad{};
    std::vector<gradient> row_grad(Ny, grad);
    std::vector<std::vector<gradient>> result(Nx, row_grad);
    // for loop has some shorthands:
    // for (...); will loop nothing as nothing is after conditions (...);
    // for (...) XXX; will loop only XXX. You should be careful when using single line form.
    // for (...) {XXX; YYY;} will loop the whole loop body.
    // And, you may fingure out that "{}" can be considered as an empty sentence with semicolon
    // appended (except for list initializing):
    // for (...); = for (...){}

    // Here is a single loop with XXX be another loop.
    for (int i = 0; i < Nx; i++)
        for (int j = 0; j < Ny; j++) {
            // Boundary Assigment (periodic)
            int jp = j + 1;
            int jm = j - 1;
            int ip = i + 1;
            int im = i - 1;
            if (im == -1)
                im = Nx - 1;
            if (ip == Nx)
                ip = 0;
            if (jm == -1)
                jm = Ny - 1;
            if (jp == Ny)
                jp = 0;
            // Tempory value assigment
            double val_u{mesh.at(i).at(jp)};
            double val_l{mesh.at(im).at(i)}, val_c{mesh.at(i).at(j)}, val_r{mesh.at(ip).at(j)};
            double val_d{mesh.at(i).at(jm)};
            // Calculate
            result.at(i).at(j).x_grad = (val_r - val_l) / (2.0 * dx);
            result.at(i).at(j).y_grad = (val_u - val_d) / (2.0 * dx);
        }
    return result;
}

// Nabla^2, Laplacian:
std::vector<std::vector<double>> cal_lap(std::vector<std::vector<double>> mesh, double dx) {
    int Nx{mesh.size()}, Ny{mesh.at(0).size()};
    // You can use "auto" when the compiler can guess what indeed the type of this variable is
    // by searching context.
    auto result{mesh};
    for (int i = 0; i < Nx; i++)
        for (int j = 0; j < Ny; j++) {
            // Boundary Assigment (periodic)
            int jp = j + 1;
            int jm = j - 1;
            int ip = i + 1;
            int im = i - 1;
            if (im == -1)
                im = Nx - 1;
            if (ip == Nx)
                ip = 0;
            if (jm == -1)
                jm = Ny - 1;
            if (jp == Ny)
                jp = 0;
            // Tempory value assigment
            double val_u{mesh.at(i).at(jp)};
            double val_l{mesh.at(im).at(i)}, val_c{mesh.at(i).at(j)}, val_r{mesh.at(ip).at(j)};
            double val_d{mesh.at(i).at(jm)};
            // Calculate
            result.at(i).at(j) = (val_r + val_l + val_u + val_d - 4.0 * val_c) / (dx * dx);
        }
    return result;
}

/*
Now we implemented these three algorithms, but we haven't use them by now.

You can write something below in the main function, to test the algorithms implemented
above. You should define your function for testing as in C++, function definition
can not nested inside other function's definition (except for lambda expression, maybe
you will find it interesting).
*/

// Below is an example how to output text and numbers to a file. You may need this
// to output your result and store as file, then process and plot that with orther tools.
int main() {
    // We create a output file stream, called ofs.
    // The string inside of the parenthesis is path of this file, "./" means relative to
    // this program executable's path.
    std::ofstream ofs("./test_file.txt");
    // We should make sure that this file is actually opened and ready for writing.
    if (ofs.is_open()) {
        // You use "<<" to output things. When you need a new line, use std::endl or "\n".
        ofs << "Hello" << " " << "Test File" << std::endl;
        for (int i = 0; i < 10; i++) {
            // Not only string, you can also output the numbers.
            // But when you want to output other things, you may have to implement "<<" behaviour
            // by yourself.
            ofs << double(i) << " " << double(i * i) / 4.0 << "\n";
        }
    }
}

/*
So much for this part. This part is presented for you to have a quick look about how the algorithms
implemented before in Python are implemented in C++. You can do your experiments here to test
these algorithms and concreate your C++ skills.

The next part, which regards for the class and OOP in C++, is an optional part for you to read and try.
If you are interested in OOP syntax in C++ and/or more details about C++, you can have a look at that.

But if you find it hard or just want to skip that optional part to the main part, the final part:
calculation of heat transfer equation, you can just ignore the No.7 part.
*/