/*C function for Fibonacci series using O(k) method*/

#include<stdio.h>
 
int fib(int n)
{
  int f[n+1];
  int i;
  f[0] = 0;
  f[1] = 1;

  for (i = 2; i <= n; i++)
  {
	f[i] = f[i-1] + f[i-2];
  }
 
  return f[n];
}
 
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

