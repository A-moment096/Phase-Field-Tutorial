/*
Hi, this file will present the type of C++ world.
C++ is type strict, which means that you can't just operate your variable
as you want, for example, an integer can be casted to float when you need,
and function can almost accept anything as long as it can process.

That's not the situtation in C++. So, it's worth to introduce these features
in C++ to help you get used to programming with C++.
*/

// As usual, we start with including some libraries we are going to use:
#include <iostream>
#include <string>
#include <vector>

// And, we define our main function as the entrance of the program.
int main() {
    // As a programming language, you of course define variables.
    // You can define variables in Python by simply write its name and value.
    // Well, in C++, you will use a type name to define something.

    // C++ is a forward declaration language. You first write something's type, then following
    // with its name. Let's declare some variables first.
    int myint = -1;
    float myfloat = 2.0;
    double mydouble = 3e3;
    bool IamTrue = true;
    char mychar = 'a';
    std::string mystr = "this is a string";
    // You should be aware that, in C++, sentences are ended with semicolon ; Don't forget that!
    // You can see the integer is simply some number, positive or negative. float numbers and double
    // numbers are similar to Python, while double is "double percision float", which cost more
    // memory space to gain higher percision. bool type is slightly different from Python, they
    // are all lowercase: "true" or "false", not "True" or "False".
    // chars are surrounded by single quotes, and strings are surrounded by double quotes.
    // That's very different from Python, which doesn't have such restriction. In Python,
    // both stands for a string.

    // Now you should feel good with these declaration. To use these variable, just call their name.

    // Wait, what if std::string? Well, it's also a type, as we just included <string> library.
    // As there are so many names that one can easily mess some names from your code with names
    // from libraries, everything inside STANDARD libraries should be called by prepending std:: with
    // their name. std is a namespace, which helps you not mess up with other names.

    // For thouse who interested in "string" type (I mean, std::string, not raw string or C style string),
    // std::string is actually a CLASS. Ah, again, a class. Well, if you already got some points on Python's
    // class, you should understand the class here better. As C++ is type strict, you must declare
    // a variable with its type. So, here you may know what I mean before: CLASS IS A DEFINED COMPLEX TYPE

    // So, now we can print these variables to our screen. To achieve this, you will need std::cout.
    std::cout << "myint: " << myint << "\n";
    std::cout << myfloat << std::endl;
    std::cout << mydouble << std::endl;
    std::cout << mychar << std::endl;
    std::cout << IamTrue << std::endl;
    std::cout << mystr << std::endl;
    // By using std::cout, you can consider this as your screen, then "<<" will tell your screen to
    // display what on the screen. When you want to start a new line, you will need to print "\n" or
    // use std::endl to indicate the end of a line.

    // As a data scientist (temporarily), you often need to process data with "float" type, in Python.
    // While, in C++, personally I recommend you to use "double", stands for double percision float type.
    // Generally, you can perform the basic add, substract, et. al. as usual.

    // **********************
    // While, please note taht:
    // C++ is a STRICT TYPE language, that you should ALWAYS use proper data type all the time, and
    // try your best to NOT convert the data type unless you have to for some reason.
    // **********************

    // I should mention that, in C++ you can, but not encouraged to, declare a variable without any
    // value. for example:
    int no_initial_val;
    // This is not encouraged because this int value may contain trash value that not be cleaned by system.
    // And, in modern C++, you can initialise variable with "initialiser list":
    int init_with_list_form{114514};
    // It's your or your group's choice to use which style. Booth initialise styles are good, but please
    // be consistent.

    // Last, I want to introduce more special type: template class
    // Sometimes you may want to have something to hold your data, but usually there is no type that
    // matches your need exactly, originally. Well, maybe "template" libraries can help you.
    // Here I'm not going to introduce how you can define a template. That's beyond this tutorial too much.
    // So basically just introduce how you can use that. One of the best example can be: std::vector
    std::vector<int> i_vector{1, 3, 5, 7, 9};
    // Now here is a vector, with int inside of that. What is a "vector" in C++? It's a kind of container,
    // such that you can use that to store something and group them together. It's just like
    // List in Python, you can push some values in, delete some value inside, and you can get the value
    // inside of this container. But it's different from List in Python: List accepts any kind of data,
    // but vector can only store the value type you defined inside the angled bracket <>. In this example,
    // it's int, so you can only store int inside of this vector.

    // Let's print its third value. Don't forget that the index starts from 0.

    std::cout << i_vector.at(2) << std::endl;

    // It's recommended to find the value of a vector by calling its method, at(int). However, you can just
    // use bracket to do the similar thing:
    // std::cout<<i_vector[2]<<std::endl;
    // There are slightly delicate difference between these two methods (I mean, boundary check). You can
    // search it if you like to know more about that. Generally, method at can be a better choice.

    // You can imagine that use vector to store vector of int. That's of course and totally okay!

    std::vector<std::vector<double>> d_2D_vector {{2.3},{4.7},{0.003,1234.0}};

    // You can try to play arround with the nested thing. We will introduce more about vector later,
    // and we will stop the types for now. These basic knowledge should be suffice for basic programming.
    // Next we will explore the flow control, like loop and conditional phrase.
}