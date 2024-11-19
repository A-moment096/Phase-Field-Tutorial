## Welcome to the world of C++ !

C++ is an awsome programming language with balance between performance and grammar.
It supports multiple programming paradigm, for example, procedural programming like C,
object orienting programming like many languages, and so on. Its grammar, due to its
strongly static typed native, is a little bit compilicated than Python we have
encountered before, but to some extend is clearer with the aid of types.

So first is, still, the comments. 
```cpp
/*
You can see that these texts are bounded by a pair of slash and asterisk. This is the multi-line comment. 
Such comment is suitable for explanation at the begining of the source codes. 
*/
```
You also can have a single line comment, which starts with double slash:
```cpp
// This is a double slash one-line comment.
// While, you still can repeat this double slash to start a comment.
```
You should notice that the double slash can comment out anything from the begining of `//` to
the end of the line. But *multiline comment* can live inside one line and only contents
inside of the comment will be ignore by compiler.

Great, let's start our first code.

```cpp
#include <iostream> // You can open a comment like this.
```
`iostream` is a standard library that enabling you to read input from user and output the
contents to the console. It might be the most frequently used library among many libraries.
This library is actually a text file with many variable, function and class declaration
`#include` will just copy the contents to your file.

If you want to use something not supported natively (for example, something other than
basic type, and some algorithms), you often include that like this.
In this file, we will include another two libraries: string and vector.
```cpp
#include <string>
#include <vector>
```
C++ program will always be executed from a special function. Typically it's called
"main" funciton. Indeed everything C++ program will do is simply just
run the function "main" you defined. There are something you should follow to define this
program entrance function:

1. This function must return type int. (integer)
2. Its name, if you don't use Microsoft Windows API, must be "main"
3. It accepts no parameters, or two parameters : int and string pointer/string vector.
```cpp
int main() {
    // As this program is not going to recieve any parameter from outside, you leave it blank.
    // By defining this function, you will always put the type at first, then your function name,
    // then a parenthesis to accept parameters, and finally a curly bracket to indicates where your
    // function start and end.

    // Well, so much for this. Let's say hello to the C++ world! And we will explain these in
    // the next example.
    std::vector<std::string> greet = {"Hello", "C++", "World!"};
    for (auto word : greet) {
        std::cout << word <<" ";
    }
}
```