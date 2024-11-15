/*
Pointers can be the most distinct feature of C/C++ from other languages.
Some one find that pointer is the most difficult part for C/C++,
and yes, this could be right, but only when you try to do kernel-level
programming and need to manage many resources with raw pointers by hand.
That would be awful if you are not a skillful C/C++ programmer with
deep understanding of C/C++. But, fortunately, we don't need to handel
such crucial things: we only need to understand a little about memory
management and how a pointer looks like, then we will introduce another
much more friendly concepts, reference, which will be a great feature
for C++ only.
*/

// As usual:

#include <iostream>
#include <string>
#include <vector>

/*
Here is a notice: it would be great if you can understand what is,
indeed, a pointer, and that's basically what we want in this part.
If you have ability to use pointers freely, that would be awsome.
But if you find it difficult, please just remember that,
DO NOT use pointer if you don't have to, and,
BE CAREFUL when you try to handel code with pointers involved.

You shall use another more friendly concepts, reference, which
(together with not use raw pointers,) is also much more encouraged
in modern C++.
*/

int main() {
    // Now, let's initialize a simple int variable first.
    int i = 0;
    // Quite simle one, and here comes pointer: a pointer points to the
    // variable i we declared before:
    int *p_i = &i;
    // Oh, here comes two weird symbols at once. That variable, p_i
    // (notice, not *p_i, asterisk is not allowed in variable name)
    // IS a pointer that points to i.

    /*
    To continue, let's first try to understand how program manage
    its resources during running.

    I. Declaration and initialization

    When you run a program, there will be a lot of resource be managed
    by this program. How can program store these resources? Well,
    every resources need a "space" to store that resource.

    By declaring and initializing a new variable i, program will
    do the following things:
    1. Find a memory space, which is not used by any other variables,
    and mark this space as "used".
        By this step 1, a variable find its "home", but that could be
        a dirty "home". So here comes step 2:
    2. Use the value you give to initialize the variable, that is, fill
    the memory space you got before with the value you need.
        By this step 2, this "home" is cleaned and your "furnitures" are
        moved in.

    Now you can see why you could declare a variable first and then give
    it a value. You nee, *allocate* the space first by declaration, then
    give it a value to initialize it. But what if you declare something,
    don't give it a value and just use that? By the steps before, you
    should fingure out that, the variable will contain trashes you don't want.
    That's the reason we encourage declaration a variable with initializing it.

    II. Find your resource by NAME and ADDRESS

    Now you have a variable i, how can you use that variable? The most common
    way is by just call its name. In C/C++, all variable under one scope
    have their own distinct, unique name after compiling, such that program
    can easily find what resources you are trying to use instantly.

    Well, this is one method you can use variable. I believe most programming
    languages use this method, and probably only use this method. But, by
    explanation above about how program find space for your resource, you can
    fingure out another way to use resources.

    Yes, by "address". You can consider your home has a name, for example,
    "John's sweet home", then you can go there by finding "John's sweet home"
    from the map. While, another way to go there is by finding its geographical
    address, for example, "11A5lA, Big Street, Small Town".

    Now let's back to our program. When you declare a variable, program find a
    space, and remember its address. Then you can access that address by just
    use that. But here is a question: the address is also complicated. What if
    one can store that address into another variable?

    Yeah, that's pointer. So, to sum it up, pointer is primarily a variable,
    which hold a special value: an address of another variable. When we say
    a pointer points to another variable, we mean that this pointer variable
    has value of another variable's address.

    III. Use pointers

    Hope it's clear for you to understand what a pointer is. Let's see some more
    about grammar. It's acturally very simple:
    */
    int *p_i2 = &i;
    /*
    Here is another pointer, p_i2, which points to i. To initialise a pointer
    that pointing to int variable, you declare pointer with that type and append
    with an asterisk. To assign value to that pointer, as you need the address of
    the variable you want to point to, you use ampersand (&) prepend to that
    variable, and then you got the address of that variable.

    Let's try to print the value of p_i2, the pointer. You will see some weird
    number, and that's "address" of variable i.
    */
    std::cout << p_i2 << std::endl;
    // Well, I said we can access the value of i by using pointer, but how?
    // It's also really simple. You just use asterisk prepend to the pointer's name.
    // Using * asterisk to get the value stored in an address is called "dereference".
    std::cout << *p_i2 << std::endl; // This will print the value of i, which is 0.
    // Now let's increase i by 5, which will become 5.
    i += 5;
    // And let's see what the pointer p_i, the pointer we declared before, holds:
    std::cout << *p_i << std::endl;
    // You shall see that's 5. Of course, it should be 5, as it also holds i's address.
    // That make sense. And if you try to print *p_i2, you will get the same result.

    // What if modifying the *pointer*'s value? Well, I hope you DO NOT do that.
    // You'd better NOT modify pointer's value, as it holds address of another variable.
    // If you modify that, you are easily getting wrong data which is not managed
    // by your program. Please only do that IF YOU HAVE TO.

    // To sum it up, every variable have four information:
    // 1. It's type. C++ is type strict, you never get something without type.
    // 2. It's name. You often use name to access your variable.
    // 3. It's value. That's always the thing we really want to access and process.
    // 4. It's address. That's where your data stored inside of the program.
    // And you can take the address of a variable as a value, and store it inside
    // another variable. This "another" variable is pointer.
    // You use
    // type *pointer_name = &variable_name
    // To access address of "variable_name", and store that to pointer_name, which
    // has type of "type *".

    // So much for this. That's quite a long story about pointer, but that of course
    // not the whole story. There are too many details about pointers, but we only
    // need to know what is a pointer, how it looks like, and AVOID using them,
    // if you want to save your life from debugging.

    // The next one can be related with pointer, but is much easier to use, and
    // encouraged to use it. That is: reference.

    // ******************************************************************************

    // What's a reference? Someone says that's better version of pointers, and some
    // one argues that's completely different concept. I partially agree with the
    // former one, as it will be easier to understand, from a "higher view".

    // Reference can be considered as "nickname" of a variable. You can't declare
    // a reference without having a variable first (otherwise, what nickname you
    // are going to use for?). Remember? We have a variable i with value 5.
    // Let's give it a nickname, or say, reference:

    int &John = i;

    // Some may wonder: Ampersand? Are you mean that you assign a value to an address?
    // Well, please consider "int &" as a whole: it a type name, reference to int, and
    // should not be understanded as "int" and "address" separately.

    // Now, you can use "Jonh" as what you want to do with "i". Let's print John and i first.
    std::cout << John << " " << i << std::endl;
    // Add 1 to i, the result should be 6, for both, as they are essentially the same.
    i += 1;
    std::cout << John << " " << i << std::endl;
    // And divide John by 2, the result should be 3, for both.
    John /= 2;
    std::cout << John << " " << i << std::endl;

    // That's so simple that not interesting at all!
    // But really? Why someone just say "reference is syntactic sugar of pointer?"
    // --- Warning ---
    // There will be something you don't need understand all of them. Please just
    // take it as an extended part.
    // --- Warning ---
    // Now we have seen many types. While, there are also some "modifier" you can
    // assign to a type. For example, "static" assert will make your variable be
    // accessed everywhere; "const" assert will make your variable a constant, 
    // that is, can't be modified. 

    // A pointer can be a const pointer, that is, can't be modified once you 
    // declare and initialise it. Not mean to make you confuse, but there are
    // also pointer to const value, which, literally, just a pointer that points to 
    // a variable, and the variable is declared as const. 

    // So, if a pointer is const pointer, you will never be able to modify the address
    // it stores. And how is this const pointer related to reference?
    // Well, someone says: reference is a "dereferenced const pointer", and must be
    // initialized with some variable's name (as already be dereferenced, no address
    // should be provided, only its name is necessary).

    // --------------------------

    // Personally, well I don't agree too much with this explanation. But this explanation
    // provides a good view about how reference and pointer and plain variables behave
    // inside a function, especially when they are used in function's parameter list.

    // So, let's end this part, and just move to another important concept, which you 
    // already meet in Python: function.
}