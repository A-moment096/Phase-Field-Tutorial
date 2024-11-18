/*

 --- EXTRA PART --- EXTRA PART --- EXTRA PART --- EXTRA PART ---

In this part, we are going to talk about the class in C++ programming.

As what we have done in Python, we also want to create a "mesh" class
to manage our simulation mesh. Personally speaking, it doesn't have
much difference from the class in Python. Or to some extent, OOP in
every languages, at the start stage, are basically the smae. The difference
presented in different languages are merely just some syntaxical details.

We have already implemented this in Python, and the basic algorithms
are, also, have been implemented in last part. If you are not interested in
C++'s OOP implementation, you can just safely ignore this chapter and go ahead.
*/

#include <array>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// We are going to define a class called mesh, just like what we have done in Python:

class mesh {
    // below is a keyword: public.
    // *public* means everything below this keyword can be accessed from outside.
    // There are also other two access control keywords: private and protect.
    // *private* means things only can be accessed by this class's members/methods;
    // *protect* means only this class and its derived class can have access to
    // things below this keyword.
public:
    int x_len{};
    // To make it simpler, we omit y_len;
    double dx{};
    // Here we only process the 2D situation
    struct gradient {
        double x_grad{};
        double y_grad{};
    };

    std::vector<std::vector<double>> vals{};
    std::vector<std::vector<gradient>> grads{};
    std::vector<std::vector<double>> laps{};
    std::vector<std::vector<double>> grads_x{};
    std::vector<std::vector<double>> grads_y{};

    // Again, we assume periodic boundary condition

    // This is constructor of this class. It will be called when you
    // create an instance of this class. It's considered as a good
    // practice that you initialize your object with constuctor.
    mesh(int new_x_len, double new_dx);
    // Here we just declare this function, and don't define it. You also can define it
    // right now. And, as taking function as parameter is a little
    // beyond of the scope, we decide not initialize the values with
    // special function.

    // Below is called deconstructor. As its name indicates, it will
    // be called when the object is ending its life. Normally you
    // should delete any resource you applied explictly (with POINTERs) here, but
    // as we have no variable handled by us explicitly, we just leave it blank.
    ~mesh();

    // We also want to define some other functions.
    // For example, assign the nearby points according to the boundary conditions:

    //  like calculating gradients and laplacians.
    void cal_grads();
    void cal_laps();
};

// You can define the functions outside of the class/struct

mesh::mesh(int new_x_len, double new_dx) {
    // You can just call the variable / properties defined inside of class
    // by its name. It's different from Python, in which you must use "self".
    x_len = new_x_len;
    // Well, you still can explicitly use something to indicate "this object"
    // explicitly, using the built-in pointer: "this"
    this->dx = new_dx;
    // As "this" is a pointer, you use "->" to access the method/properties inside
    // of the object.

    // Below we put the initial zeros inside the value vectors, using "push_back" method.

    // This is also an example to use constructor. It means create a vector with
    // "x_len" number of values 0.
    std::vector<double> row(x_len);
    // This means initialize a vector of x_len "gradient"s.
    std::vector<gradient> grad_row(x_len);

    // Push back the rows
    for (int i = 0; i < x_len; i++) {
        vals.push_back(row);
        grads.push_back(grad_row);
        // Use row before as they are all 0 valued.
        laps.push_back(row);
        grads_x.push_back(row);
        grads_y.push_back(row);
    }
}

mesh::~mesh() {
}

void mesh::cal_grads() {
    for (int i = 0; i < this->x_len; i++) {
        for (int j = 0; j < this->x_len; j++) {
            // We can use a little math to process the periodic boundary condition:
            // (-1+x_len)%x_len = x_len -1; (x_len + x_len)%x_len  = 0;
            // Avoid "if" check.
            this->grads.at(i).at(j).x_grad = (this->vals.at((i + x_len + 1) % x_len).at(j) - this->vals.at((i + x_len - 1) % x_len).at(j)) / (2 * this->dx);
            this->grads_x.at(i).at(j) = this->grads.at(i).at(j).x_grad;
            this->grads.at(i).at(j).y_grad = (this->vals.at(i).at((j + x_len + 1) % x_len) - this->vals.at(i).at((j + x_len - 1) % x_len)) / (2 * this->dx);
            this->grads_y.at(i).at(j) = this->grads.at(i).at(j).y_grad;
        }
    }
}

void mesh::cal_laps() {
    for (int i = 0; i < this->x_len; i++) {
        for (int j = 0; j < this->x_len; j++) {
            this->laps.at(i).at(j) =                               //
                (                                                  //
                    this->vals.at((i + x_len + 1) % x_len).at(j)   //
                    + this->vals.at((i + x_len - 1) % x_len).at(j) //
                    + this->vals.at(i).at((j + x_len + 1) % x_len) //
                    + this->vals.at(i).at((j + x_len - 1) % x_len) //
                    - 4.0 * this->vals.at(i).at(j)                 //
                    ) /                                            //
                (this->dx * this->dx);                             //
        }
    }
}

// Here, we use Normal Distribution's function to assign value for
// our mesh
double Normal_CDF(double x, double mu, double sigma) {
    return 0.5 * (1.0 + std::erf((x - mu) / (sigma * std::sqrt(2.0))));
}

// Use this function to output the values from the vector to csv file.
void to_csv_3D(std::vector<std::vector<double>> vec_val, std::string fname) {
    std::string filename{"./results/" + fname + ".csv"};
    std::ofstream ofs(filename);
    if (ofs) {
        ofs << "x" << "," << "y" << "," << "val\n";
        for (int i = 0; i < vec_val.size(); i++) {
            for (int j = 0; j < vec_val.at(0).size(); j++) {
                ofs << i << "," << j << "," << vec_val.at(i).at(j) << std::endl;
            }
        }
        ofs.close();
    }
}

int main() {
    std::filesystem::create_directory("./results");
    mesh m1(100, 0.1);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            // This will initialize a round plate

            // if ((i - 50) * (i - 50) + (j - 50) * (j - 50) < 10 * 10) {
            // m1.vals.at(i).at(j) = 1.0;
            // }

            // Use the function defined before to initialize.
            m1.vals.at(i).at(j) = Normal_CDF(double(i), 50, 5);
        }
    }
    // Call the method defined before to calculate the gradients and laplacians
    m1.cal_grads();
    m1.cal_laps();

    // Output the data into csv files.
    to_csv_3D(m1.vals, "vals");
    to_csv_3D(m1.grads_x, "gradx");
    to_csv_3D(m1.grads_y, "grady");
    to_csv_3D(m1.laps, "laps");
}
