#include <random>
#include <functional>

#include "myrand.h"


//Get random number between 0 and limit
// [0, limit)
int randFunctions::mersenneRand(int limit){

	seed = seed_generator();
	mt19937 mersenne_generator(seed);
	uniform_int_distribution<unsigned> distribution(0, limit);

	random = distribution(mersenne_generator);

	return random;
}

//returns a bool
bool randFunctions::randomBool() {
	static auto gen = bind(uniform_int_distribution<>(0,1),default_random_engine());
	return gen();
}
