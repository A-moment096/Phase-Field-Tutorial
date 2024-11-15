/*
Flow control is a very basic part for every programming languages.
You have already a basic knowledge about how flow control works in Python,
and for now the only thing is let you know how C++ can achieve the same thing,
in a possibly more way.

As usual, we include the following libraries and begin to define our main function.
*/
#include <iostream>
#include <string>
#include <vector>

int main() {
    // Let's output something simple, for example, add a number by 2 for five times.
    // We need to initialise a number, say, 3. You can see the final result is 3+5*2=13.
    int a = 3;
    // Let's try "for" loop first.
    for (int i = 0; i < 5; i++) {
        a += 2;
    }
    std::cout << a << std::endl;
    // Let's see what happened in this loop. From the first line, it should be the most
    // complex part. First, you initialised a variable called i, with
    // value 0; Then, you set a condition for loop, in this example, when i is smaller than 5;
    // Finally, you will decide what to do at the end of the loop, and here you will let i
    // increase itself by 1.
    // Then you start what to do inside of the loop, which is surrounded by curly bracket.
    // Here we simply let a increase itself by 2.

    // So, to sum it up, you define a helper variable i with initial value 0, then you
    // begin your loop: increase a by 2. And at the end of each loop, you increase the
    // helper by 1. This loop will end when program find that the helper variable i is
    // bigger or equal than 5, or in another way, this loop will continue if i is smaller than 5.

    // Beside the for loop, you can also have while loop. We will do the same thing, but
    // with variable b, start from 5. The final result of b should be 25.
    int b = 5;
    int j = 0;
    while (j < 5) {
        b += 2;
        j++;
    }
    // So this code structure is basically the same as for loop. There is possibly only one
    // difference between while loop and for loop if you use loop in this way:
    // The helper variable, i, in for loop, is "local", which you can't access outside of
    // the for loop. While, the helper variable j, in while loop, is avaiable outside of
    // the loop.
    // You can also use do while loop, which you can consider just change the code structure.
    int c = 7;
    int k = 0;
    do {
        c += 2;
    } while (k < 5);

    // And to end this loop part, allow me introduce another newer feature in C++: range loop.
    // Let's initialise a vector of int first. I will print these value out with for range loop.
    std::vector<int> vec_int = {1, 3, 5, 7, 9};
    // Here comes the range for loop.
    for (int i : vec_int) {
        std::cout << i << std::endl;
    }
    // So here, i is a variable represent the elements inside of the vector. You might feel
    // familar about this grammar: In Python, when you need to loop inside of a list, you just
    // do the follows:
    /*
    for i in my_list:
        foo()
        bar()
    */
    // That's really similar, right? But please notice that you can't use this method to change the
    // capicity of the container, or you will get terrible thing: a bug.

    // *****************************************************

    // Now let's see how C++ process the conditions. The following lines will print yes if number a
    // is bigger than number b; print no if number a is smaller than b; print ? when two numbers are
    // equal. Quite simple example.
    int num_a = 0, num_b = 0; // You can initialise the numbers in one line if they have the same type.
    std::cout << "please input number a:\n";
    std::cin >> num_a; // You use std::cin to input something from console.
    std::cout << "please input number b:\n";
    std::cin >> num_b;
    // Here comes conditions:
    if (num_a > num_b) {
        std::cout << "yes" << std::endl;
    } else if (num_a == num_b) { // So you will need two equal symbols to represent equality.
        std::cout << "?" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
    // It should be very clear that everything comes naturally.

    // I'm not going to introduce "switch-case" expression and "goto". You can explore them by yourself.
    // However, please notice that, you should not use goto as it easily gets you into troubles with bugs. 

    // We have encountered "function" for many times. But before function, allow me to introduce the
    // so called "the most difficult part of C/C++": pointers and references, in the next part.
}