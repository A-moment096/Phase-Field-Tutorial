/*
You must already see many functions. I mean, the "main" function.
Yes, that is a function, but not perfect and ideal as an example.
Here, we will define some functions, and use them inside of our
"main" function. Let's do it.

As usual:
*/

#include <iostream>
#include <string>
#include <vector>

// Now please have a look at the following simple but full featured function:

int add(int a, int b) {

    int c = 0;
    c = a + b;

    return c;
}

/*
Ah, a boring example. It just add two int number and return the sum of it!
But please have a close at it:

First, you declare it with the *return type* and give this function a name;
Second, you open a parenthesis, list the *parameter list*, that is what you
    are going to accept the parameter from the outside and pass to inside
    of the function;
Then, you open a curly bracket and write down the setences you want to do.
    That is the so called "function body";
And finally, you *return* a value, which should match the type you defined
    before, the *return type*.

So, I'm saying that this is a fully featured example of basic function.
But why we are bothering with function? That's because we want to reuse
some logic. You can package some repeated procedures inside of a function,
and when you need that, you just use the function. That makes things simplier.

*****************************************************************************

Someone may argue that: I can Ctrl+C Ctrl+V to achieve the same thing! Well,
function has another function(?): abstraction, and control the variables
inside and outside, make them visable or invisable to others. You can't access
the int c from the outside, as that is a *local variable* to this function.

Also, you can recursively call the function itself. But we won't cover this here.
If you are interested in that, you can write a small function to calculate the
factorial of an integer. That can be the best example for recursive calling.

Finally, Copy-Paste may harm your mental health. Please use function if you
don't want to lose your mind when you can package some logics into a function.
*/

/*
Well, where is pointer and reference? We said that these things will come here and
show something deeper. Here it comes. Suppose I want to modify some outside variable
inside of the function, say, increase an integer by 1:
*/

void increase_by_1(int increased) { // here, you use "void" to indicate that this
                                    // function has no return value.
    increased += 1;
}
// Please call this function inside of your main function. After using it, you
// will find something weird.

// Note: Please come back after you compile and run this code.

// The result doesn't change! That's because: this function is trying to
// pass value by COPYing.

// So, let's see more about "passing value".

/*
When you are trying to pass a value to a function, there are basically 3 methods:
    1. Pass by value. That's what we mean by "pass by copying value". The function
        will copy the value from the variables, and then just pass these value to the
        parameters. It's like:
        out_var -> {inner_var} -> {change inner_var} ->out of function, nothing
        changed (inner_var deleted)
        So, the "out_var" is never changed and you only change the inner_var.
    2. Pass by reference. This is the way when you want to change the outside variables
        in the parameter list. Below is a simple illustration:
        out_var -> {reference_out_var} -> {change reference_out_var} -> changed out_var
    3. Pass by pointer. By this way, you just pass the value of the address of a variable.
        Although you pass the address by copying it to function, the address is not changed.
        When you dereference the pointer and modify the value stored inside the address, the
        address itself is not matter, and the modified value bypass the function scope.
        Illustration:
        out_var --- pass its pointer (address) ---> {our_var_p} -> {change val_inside_out_var}
        -> out_var_p not changed, but inside value of the address is changed.
As a result, to change the value of the passed variable, you must use "reference" or "pointer".
I recommend you to use reference, which is easier to use, its grammar is more friendly and you
don't have to handel the pointers by your hand.

Here is an example about how to change the variable using function:
*/

void increase_1_ref(int &increased) {
    increased += 1;
}

// Here if you use this function and try to achieve the things we did before, you shall do it
// as you wish. I'd like not introduce the pointer way here. If you are interested in, you shall
// easily find the resources related to that.

// And by the discussion above, you can see that, the variable used by function are only passed
// from the outside, and you can define how these variables are passed to. There is also
// another variables that you don't need to pass it in the parameter list, which is called
// global parameter. For example:

int g_i = 1000;

// Yes, you just define that outside of any function (also outside of "main" function).
// By this way your function defined below this variable can then access this variable.

void print_g_i() {
    std::cout << g_i << std::endl;
    g_i += 2;
}

// So here print_g_i doesn't accept any variable, but still can get the value of g_i, and modify it.
// Please refer to the part that this function is got called.

// Actually, function can be defined by two step, which you can see in more advanced use of function.
// You can declare the function at first, and realize it after. Your program will read the declaration
// first, and then search for its definition accross the whole document and outside libraries.
double declare_first(double, int);
// You even don't need to assign the parameter list's names, just declare the following things:
// 1. Return type; 2. Function name; 3. Parameter list's types.
// You should implement it after, but in this way you can call this function inside the other function
// defined below this declaration already, for exmaple, the "main" function.

int main() {
    // First we initialize two variables, just call them num1 and num2:
    int num1 = 10, num2 = 3;
    // And initialize a variable with value 0:
    int sum = 0;
    // Let's see how we use the function "add" and pass its result to the variable "sum" :
    sum = add(num1, num2);
    std::cout << sum << std::endl;
    // Yes, you just fill the number in, like what you have done in Python.

    // Now, let's try the function above, called "increase_by_1", with num_2 as parameter:
    // You may hope this function will let num_2 be 4.
    increase_by_1(num2);
    std::cout << num2 << std::endl;
    // Wow, it's still 3! Why? Please jump back to the position before the "main" function.

    increase_1_ref(num2);
    std::cout << num2 << std::endl;
    
    // To pass reference, you just pass the name. That's really simple, and it indicates
    // that: to control a variable wheather is modifiable by function, you just decide
    // "pass by value" and write the plain parameter list, or "pass by reference" and write
    // the parameter list append with ampersand. You can use these function in a consistent style.

    print_g_i();
    std::cout << g_i << std::endl;
    // You shall see you print the value of g_i, which is 1000, then increase it by two, and
    // finally, you print the value of g_i again, which is 1002.

    declare_first(2.34, 2);
    // Please run this function and see what will happen.
}

// Here you should implement the function you declared before:

double declare_first(double num_1, int num_2) {
    std::cout << num_1 << std::endl;
    std::cout << num_1 * double(num_2) << std::endl; // Here I use force cast, casting int to
    // double, which is  definitely a bad idea.
    // But sometimes, you have to.
    return int(num_1) * num_2;
}

// Let's draw a conclusion:
// Function is not complex in C++, but you need to know how to pass the outside variable to 
// the function through the parameter list. And there are three ways to pass values to the
// function, you should pick one with proper grammar and clear goal, and avoid using pointer.

// By now, you should have acquired the basic knowledge and features of C++. All you need now
// is try to use C++ and write something simple, expand your ability step by step, and finally
// write codes confidently. 
// When you meet bugs, please search that online. As a old-fashioned language, there are already
// a lot of great resources and discussion boards or forums. You may find way to solve your question
// by just searching online.

// The next part, we will quickly review the algorithms we dicussed before, 
// and just combine what we have already, together with some knowledge from Python.