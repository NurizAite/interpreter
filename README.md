## Content
* [What is an interpreter?](#basics)
* [Purpose](#purpose)
* [Arithmetic operations](#arithmetic)
* [Assignment](#assign)
 * [How map container works?](#map)
* [How to run program?](#run)

# <a name="basics"></a> What is an interpreter?

**An interpreter** is a computer program that directly executes instructions written in a programming or scripting language, without requiring them previously to have been compiled into a machine language program. 

An interpreter generally uses one of the following strategies for program execution:

<li> Parse the source code and perform its behavior directly;
<li> Translate source code into some efficient intermediate representation and immediately execute this;
<li> Explicitly execute stored precompiled code made by a compiler which is part of the interpreter system.

#  <a name="purpose"></a> Purpose

The pupose is to write a program that executes instructions written in a high-level language in interactive mode.

**Interactive mode** is a command line shell which gives immediate feedback for each statement, while running previously fed statements in active memory. As new lines are fed into the interpreter, the fed program is evaluated both in part and in whole. 

# <a name="arithmetics"></a> Arithmetic operations

The main purpose of arithmetic operations is to perform certain arithmetic operations on numerical data: add, subtract, multiply, divide, etc. This means that for arithmetic operations, all operands are calculated in a numerical scalar context. In this case, strings containing the correct numeric literals will be automatically converted to numeric values: if the string does not contain the correct numeric literal, the interpreter will try to extract a number from it, starting with the left character, and use it as an operand.


# <a name="assign"></a> Assignment

**An assignment** statement sets and/or re-sets the value stored in the storage location(s) denoted by a variable name; in other words, it copies a value into the variable.

**Variables** are containers for values. It is possible to put a value into a variable and later replace it with a new one. An assignment operation modifies the current state of the executing program. Consequently, assignment is dependent on the concept of variables. In an assignment:

* The expression is evaluated in the current state of the program.
* The variable is assigned the computed value, replacing the prior value of that variable.

The name of the variables and their values are stored in the program using the `std::map<std::string, int> varTable;`.

## <a name="map"></a> How map container works?

Maps are associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order.

In a map, the key values are generally used to sort and uniquely identify the elements, while the mapped values store the content associated to this key. The types of key and mapped value may differ, and are grouped together in member type `value_type` , which is a pair type combining both:

```typedef pair<const Key, T> value_type;```

Internally, the elements in a map are always sorted by its key following a specific strict weak ordering criterion indicated by its internal comparison object.

Map containers are generally slower than unordered_map containers to access individual elements by their key, but they allow the direct iteration on subsets based on their order. The mapped values in a map can be accessed directly by their corresponding key using the bracket operator.

Maps are typically implemented as binary search trees.

#  <a name="depend"></a> Dependencies

The program was written in the C ++ programming language, so for its compilation and further launch, you must install the **g++ compiler**

### Debian/Ubuntu/Mint

``` sudo apt-get update ```

``` sudo apt-get install g++ ```

### Fedora/CentOS

``` sudo dnf update ```

``` sudo dnf install g++ ```

# <a name="run"></a> How to run program?

First you need to compile the program using the Makefile:
```
make
```
Run program:
```
./bin/main
```

# <a name="qa"></a> Questions and suggestions

If you have any questions or suggestions, write to the email zhanmukanbetova.gulden@gmail.com


