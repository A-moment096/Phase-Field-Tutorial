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
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// We are going to define a class called mesh, just like what we have done
// in Python:

class mesh {
public:
    int x_len{};
    // To make it simpler, we omit y_len;
    double dx{};
    // Here we only process the 2D situation
    std::vector<std::vector<double>> vals{};
    std::vector<std::vector<std::array<double, 2>>> grads{};
    std::vector<std::vector<double>> laps{};
    // Again, we assume periodic boundary condition

    // This is constructor of this class. It will be called when you
    // create an instance of this class. It's considered as a good
    // practice that you initialize your object with constuctor.
    mesh(int new_x_len, double new_dx);
    // Here we just declare this function. You also can define it
    // right now. And, as taking function as parameter is a little
    // beyond of the scope, we decide not initialize the values with
    // special function.

    // Below is called deconstructor. As its name indicates, it will
    // be called when the object is ending its life. Normally you
    // should delete any resource you applied explictly (with POINTERs) here, but
    // as we have no variable handled by us explicitly, we just leave it blank.
    ~mesh();

    // We also want to define some
};

mesh::mesh(int new_x_len, double new_dx) {
    // You can just call the variable / properties decided inside of class
    // by its name. It's different from Python, in which you must use "self".
    x_len = new_x_len;
    // Well, you still can explicitly use something to indicate "this object"
    // explicitly, using the built-in pointer: "this"
    this->dx = new_dx;
    // As "this" is a pointer, you use "->" to access the method/properties inside
    // of the object.

    // Below we put the initial zeros inside the value vectors, using "push_back" method.

    // First, this is an example to use constructor. It means create a vector with
    // "x_len" number of values 0.
    std::vector<double> row(x_len);
    std::vector<std::array<double, 2>> grad_row(x_len, {0, 0});
    for (int i = 0; i < x_len; i++) {
        vals.push_back(row);
        grads.push_back(grad_row);
        laps.push_back(row);
    }
}

mesh::~mesh() {
}

int main() {
}
