#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_plain.h>

/* Computation of the integral,
      I = int x (dx)   over (0) to (1).  
    The exact answer is 1/2. */

double exact = 0.5;

double g (double k, size_t dim, void *params)
{
  (void)(dim); /* avoid unused parameter warnings */
  (void)(params);
  //double A = k;
  return k; 
}

void
display_results (char *title, double result, double error)
{
  printf ("%s ==================\n", title);
  printf ("result = % .6f\n", result);
  printf ("sigma  = % .6f\n", error);
  printf ("exact  = % .6f\n", exact);
  printf ("error  = % .6f = %.2g sigma\n", result - exact,
          fabs (result - exact) / error);
}

int main (void)
{
  double res, err;

  double xl[1] = {0};
  double xu[1] = {1};

  const gsl_rng_type *T;
  gsl_rng *r;

  gsl_monte_function G = { &g, 1, 0 };

  size_t calls = 500000;

  gsl_rng_env_setup ();

  T = gsl_rng_default;
  r = gsl_rng_alloc (T);

  {
    gsl_monte_plain_state *s = gsl_monte_plain_alloc (1);
    gsl_monte_plain_integrate (&G, xl, xu, 1, calls, r, s, &res, &err);
    gsl_monte_plain_free (s);

    display_results ("plain", res, err);
  }

  gsl_rng_free (r);

  return 0;
}

