## Prefix Notation Calculator

In this problem, you will be tasked with implementing a not so simple command-line based calculator program.  Your program will accept inputs like this (wherein underlined text represents user input):

```
./calc + - 3 4 5
4.000000
```

or, like this

```
./calc x - 3.4 5.6 7.9
-17.3799999
```

such that the user can perform all five of the basic math operations that C permits — addition, subtraction, multiplication, division, and modulo.

But wait. Part of that isn’t familiar.

```
x - 3.4 5.6 7.9
```

What’s that?

That, actually, is what is known as *prefix notation*. Though not as common as the *infix notation* we all learned about in elementary school, it turns out that prefix notation and its closely related cousin *postfix notation* (also known, respectively, as Polish and Reverse Polish notation) are much easier for machines to parse.

Converting the above to more familiar infix notation would result in the expression `(3.4 - 5.6) x 7.9`. For more on prefix notation, check out [its Wikipedia page](https://en.wikipedia.org/wiki/Polish_notation) and/or Google!

Obviously, you’re going to need to do math at some point, but you may have already done that. Can you leverage some of your code from your first version of Calc?

## Stacks on Stacks on Stacks

So, how should we go about implementing this prefix calculator? One easy approach might be to use a stack. Let’s see why.

The basic idea behind prefix notation is that an operation operates on the two numbers immediately to its right, and all three (the operator and its so-called *operands*) are then replaced in the line by the answers, moving from right to left.

Here’s an example using one fairly straightforward approach:

```
+ - / 4 2 24 x 8 9
```

The first operation we encounter going right to left is `x` (multiplication). So we look to the two operands to its right (`8 9`), multiply them together, and leave the result where `x 8 9` used to be:

```
+ - / 4 2 24 72
```

The next operator from right to left is `/`. 4 divided by 2 is of course 2, and so we leave `2` where `/ 4 2` used to be:

```
+ - 2 24 72
```

Next up is `- 2 24`, replaced by `-22` (the result of `2 - 24`):

```
+ -22 72
```

And all that then remains is `-22 + 72`, or `50`!

Visually, this approach of "finding the rightmost operator and applying it to the two numbers to its right" is an intuitive way for humans to parse prefix notation, but computers can be a bit smarter about this, without ever having to look at each operand or operator more than once, if instead we store all the information in a stack as we see it.

If the computer parsed this input by starting at the right side (aka the last element of `argv`) and pushing *numbers* onto a stack as it came across them, then when it came upon an operation all that would need to happen is to pop the top two numbers off the stack, apply the operation, and push the result back on!

## What to do

You are expected to take all input in the command line.  Floating point numbers and integers are both fair game.  You may not assume well formatted input. Here is what you can assume:

- There will never be more than 20 numbers in the stack

That’s it.

Note that you cannot assume that everything will be a float or an operation, or that the order of numbers and operands will work out nicely. Better check those yourself!

To start go to the root of your directory, `pset5` should already be created, if it is not then run the command `mkdir pset5` and then `cd pset5` and finally `mkdir calc`.  Now run the command `wget https://raw.githubusercontent.com/csbaxter/docs/main/calc/calc.c` inside the directory and open file `calc.c` to find much of the code you need already implemented.  Study the code that's there to understand what is going on and how a stack is being used to implement the solution.  Your job is to find the areas of code where "TODO" is indicated, and implement the necessary code to complete the program.

To test the correctness of your prefix calculator, you can run `check50` with:

```
check50 csbaxter/problems/2021/x/calc
```

When you are ready to submit, use the following `submit50` command:

```
submit50 csbaxter/problems/2021/x/calc
```
