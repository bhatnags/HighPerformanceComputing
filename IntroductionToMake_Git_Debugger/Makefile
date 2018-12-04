# set variables
CC=gcc
CFLAGS=-Wall
#CFLAGS=-Wall -g	# turn on debugging - for gdb
#CFLAGS=-Wall -DDEBUG	# turn on debugging - in the code
LDFLAGS=-lm

################################################################################
# custom variables
################################################################################

targets        = ex01numbers      ex02sqrt     
objects        = ex01numbers.o    ex02sqrt.o   
tests          = ex01numbers-test ex02sqrt-test


################################################################################
# default build target, and test target
################################################################################

default: $(targets)

test: $(tests)

################################################################################
# individual build targets
################################################################################

ex01numbers: ex01numbers.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
ex02sqrt: ex02sqrt.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

################################################################################
# individual test targets
################################################################################

ex01numbers-test: ex01numbers
	./$< 121

ex02sqrt-test: ex02sqrt
	./$< 2
	./$< 2 1e-05
	./$< 2 0.01
	./$< 3
	./$< 4
	./$< 99
	./$< 100
	./$< 123.45 1e-8


################################################################################
# clean targets
################################################################################

# phony target to get around problem of having a file called 'clean'
.PHONY: clean
clean:
	$(RM) $(objects) $(targets)


