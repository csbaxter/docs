#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constant
#define MAXNUMS 20

// stack definition and function prototypes
typedef struct
{
    int size;
    float nums[MAXNUMS];
}
stack;

// prototypes
void stack_push(stack *s, float num);
float stack_pop(stack *s);
bool is_number(const char *s);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "Usage: calc2 expression\n");
        exit(1);
    }

    // TODO initialize stack (two lines)

    // TODO implement for loop to iterate over command line arguments 
    for (int i = ... )
    {
        // perform the mathematical operation corresponding to the operator string
        if (!strcmp(argv[i], "+"))
        {
            float op1 = stack_pop(&s);
            float op2 = stack_pop(&s);
            stack_push(&s, op1 + op2);
        }
        else if (!strcmp(argv[i], "-"))
        {
            // TODO implement subtraction
        }
        else if (!strcmp(argv[i], "x"))
        {
            // TODO implement multiplication
            stack_push(&s, op1 * op2);
        }
        else if (!strcmp(argv[i], "/"))
        {
            // TODO implement division
            stack_push(&s, op1 / op2);
        }
        else if (!strcmp(argv[i], "%"))
        {
            float op1 = stack_pop(&s);
            float op2 = stack_pop(&s);
            stack_push(&s, fmod(op1, op2));
        }
        else if (is_number(argv[i]))
        {
            stack_push(&s, atof(argv[i]));
        }
        else
        {
            fprintf(stderr, "error: invalid input: %s\n", argv[i]);
            exit(1);
        }
    }
    printf("%f\n", stack_pop(&s));
}

/**
 * Pushes value onto stack.
 */
void stack_push(stack *s, float num)
{
    if (s->size == MAXNUMS)
    {
        fprintf(stderr, "error: cannot push to full stack.\n");
        exit(1);
    }
    s->nums[(s->size)++] = num;
}

/**
 * Pops value from stack.
 */
float stack_pop(stack *s)
{
    if (s->size == 0)
    {
        fprintf(stderr, "error: cannot pop from empty stack.\n");
        exit(1);
    }
  
    // TODO pop value of stack and return it
}

/**
 * Checks to see if given string represents a number.
 * Accepts valid negative & float numbers.
 */
bool is_number(const char *s)
{
    int len = strlen(s);
    int i = 0;
    int decimals = 0;

    // negatives are numbers, too
    if (s[0] == '-' && len > 1)
    {
        i = 1;
    }
    for (; i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            if (s[i] == '.')
            {
                // i.e. if this is the first decimal point, that's fine
                if (decimals++ == 0)
                {
                    continue;
                }
            }
            return false;
        }
    }
    return true;
}
