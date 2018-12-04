/*C function which outputs the kth entry in the Fibonacci seq using RECURSION*/

#include <stdio.h>
int fib(int);

int main()
    {
        int number;
        int result;
        printf("Enter the nth number in fibonacci series: ");
        scanf("%d", &number);

        if (number < 0)
        {
            printf("Fibonacci of negative number is not possible.\n");
        }

        else
        {
            result = fib(number);
            printf("The %d number in fibonacci series is %d\n", number, result);
        }
        return 0;
    }


int fib(int number)
    {
        if (number == 0)
        {
            return 0;
        }
        else if (number == 1)
        {
            return 1;
        }
        else
        {
            return(fib(number - 1) + fib(number - 2));
        }
    }
