#pragma once

#include <random>
#include <functional>


#ifndef MYRAND_H_
#define MYRAND_H_

using namespace std;

class randFunctions{
public:
	int mersenneRand(int limit);
	bool randomBool();
private:
    random_device seed_generator;
    mt19937 mersenne_generator;
    uniform_int_distribution<int> distribution;
    unsigned seed;
    unsigned random = distribution(mersenne_generator);
};



#endif /* MYRAND_H_ */



//https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
