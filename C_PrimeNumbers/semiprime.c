#include<stdio.h>

int is_semiprime(int);
int main()
{
   int i;
  
      for ( i = 2 ; i < 1000 ; i++ )
      {
        if (is_semiprime(i)) printf(" %d\n", i);
      }

   return 0;
   
}

int is_semiprime(int x)
	{
	  int p, f = 0;
	  
	  for (p = 2; f < 2 && p*p <= x; p++)
	     while (0 == x % p)
	     x /= p, f++;
	  
	  return f + (x > 1) == 2;
	
	}
