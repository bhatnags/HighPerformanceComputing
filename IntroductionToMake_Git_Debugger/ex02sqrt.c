#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define EPSILON 1e-6

/**
 * Purpose: calculate the square root of a floating point number,
 * using the High/Low method.
 */


/**
 * High/Low method
 * Find integers a,b such that a^2 <= x <= b^2
 * Note that a and b do not have to be the largest (for a)
 * or smallest (for b) integers that satisfy the inequality.
 * The bisection method will work, so long as they satisfy the
 * inequality. It will converge quicker if a,b are better guesses,
 * but it will converge nonetheless.
 *
 * Thus we can set:
 *   - a = 0.0 (easy)
 *   - b = ceil(x + epsilon)^2
 *     (b is the square of the next integer after x)
 *
 * Then loop:
 *   - calculate c = (a+b)/2
 *   - if (c^2 - x) or (b-a)/2 is within the tolerance, then finish
 *   - otherwise replace a or b (whichever is closer) with c, and repeat
 */
double my_sqrt(double x, double epsilon) {
    double a, b, c;

    // quick sanity check - is x positive?
    if (x < 0.0) {
        fprintf(stderr, "my_sqrt: error: x must be positive\n");
        exit(EXIT_FAILURE);
    }

    // find integers a,b such that a^2 <= x <= b^2
    // the lower bound is easy: 0.0
    // the upper bound is b^2, where b is the next integer
    // after 'x'. we find this by adding epsilon to x, and then
    // getting the ceil() of that.
    //
    // note: we could probably do a better search here for the
    // starting a and b, using a bisection search to find the
    // next lowest and next highest square. however, since
    // we're going to bisect the resulting a,b anyhow, maybe
    // it's simpler to just calc simple guesses and let the
    // bisection loop below do the work
    a = 0.0;
    b = ceil(x+epsilon) * ceil(x+epsilon);

    while (1) {
        c = (a+b)/2.0;

#if DEBUG
        printf("a = %lf; b = %lf; c = %lf, real sqrt(x) = %lf\n", a, b, c, sqrt(x));
#endif

        // is the new c close? does c^2 almost equal x ?
        // or have we shrunk the interval (a,b) too much ?
        // 
        // in particular, note that we cannot simply test "c*c == x" because
        // we're dealing with floats! we have to use an epsilon test, with
        // fabs() because we don't know which side is larger
        if ( (fabs(c*c-x) < epsilon) || ((b-a)/2.0 < epsilon) ) {
            return c;
        }

        // use c as the new a or b, depending on which is closer

        // if c^2 < x, then the guess is too small, and hence
        // is closer to 'a'; so move 'a' up
        if ( (c*c < x) ) {
            a = c;
        }
        else {
            // else bring b down (the guess is closer to 'b')
            b = c;
        }
    }
}


/**
 * For a given epsilon, determine how many digits of precision
 * it needs to be printed fully in printf.
 *
 * Simply multiply by 10 repeated until it is greater than 1.
 *
 * (an alternative might be to snprintf(%e) it to a string, then parse
 * the number after the exponent)
 *
 * The input should be between 0 and 1. If not, return 0 digits
 * of precision.
 */
int find_precision(double epsilon) {
    int count = 1;

    // sanity check: negative numbers, just return 0
    if (epsilon < 0.0) return 0;

    // sanity check: greater than 1, just return 0
    if (epsilon > 1.0) return 0;

    while ( (epsilon *= 10.0) < 1.0 ) count++;

    return count;
}


int main(int argc, char *argv[]) {
    double x, epsilon, sq;
    int precision;  // used to indicate how precise the printf should be

    // there should be one command-line arg
    if (argc < 2) {
        fprintf(stderr, "Usage: %s x [epsilon]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        x = atof(argv[1]);
    }

    // an optional second command-line arg is the
    // desired precision
    // note that atof() can parse both '0.001' and '1e-3' as
    // inputs
    if (argc >= 3) {
        epsilon = atof(argv[2]);
    } else {
        // else default to the constant
        epsilon = EPSILON;
    }

    // quick sanity check - is x positive?
    if (x < 0.0) {
        fprintf(stderr, "%s: error: x must be positive\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // another quick sanity check - is epsilon 0<e<1 ?
    if (epsilon <= 0.0 || epsilon >= 1.0) {
        fprintf(stderr, "%s: error: epsilon must be between 0.0 and 1.0\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // another quick sanity check - is epsilon too small ??
    // DBL_EPSILON is the smallest e such that (x + e != x)
    if (epsilon < DBL_EPSILON) {
        fprintf(stderr, "%s: error: epsilon is too small: the smallest we can take is %e\n", argv[0], DBL_EPSILON);
        exit(EXIT_FAILURE);
    }

    // how many digits in our epsilon?
    // add one to it, because we'd like to illustrate the difference between our calc and
    // the library sqrt() function.
    precision = find_precision(epsilon) + 1;

    // do the work
    sq = my_sqrt(x, epsilon);

    // print our answer, and calc how far away from the library function we are
    printf("The square root of '%lf' is '%.*f' (+/- %.*f)\n", x, precision, sq, precision, fabs(sq-sqrt(x)));

    exit(EXIT_SUCCESS);
}

