#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Purpose: test whether an integer is a triangular
 * number (can form an equilateral triangle of objects)
 * or a square number (an int which is a square of an
 * int) or both.
 */


/**
 * Simple test for whether a number is square:
 * Get the (floating point) sqrt, convert that
 * to the nearest rounded integer, square that
 * new number, and test if it is the same as your original.
 * Note that we're only testing integers here, so the
 * rounding off doesn't cause a problem.
 */
int is_square(int n) {
    double d;
    int i;

    // get the floating point sqrt
    d = sqrt(n);
    // convert back to an int
    i = round(d);

    // and see if our sqrt squared is equal to n
    return i*i == n;
}

/**
 * Ref: http://en.wikipedia.org/wiki/Triangular_number#Triangular_roots_and_tests_for_triangular_numbers
 * An integer x is triangular if and only if 8x + 1 is a square
 * Re-use the is_square() function.
 */
int is_triangular(int n) {
    return is_square(8 * n + 1);
}

int main(int argc, char *argv[]) {
    int i, n;
    int square, triangular;

    // there should be one command-line arg
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        n = atoi(argv[1]);
    }

    // quick sanity check - is n positive?
    if (n < 0) {
        fprintf(stderr, "%s: error: n must be positive\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // loop up to n
    for (i=1; i<=n; i++) {
        // assume not until proven otherwise
        square = triangular = 0;

        // do the work
        square     = is_square(i);
        triangular = is_triangular(i);

        printf("%4d: ", i);

        // print results
        if (square && triangular) {
            printf("square and triangular\n");
        }
        else if (square) {
            printf("square\n");
        }
        else if (triangular) {
            printf("triangular\n");
        }
        else {
            printf("neither\n");
        }
    }

    exit(EXIT_SUCCESS);
}

