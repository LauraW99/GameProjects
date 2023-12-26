#include "Random.h"
#include <random>
#include <chrono>

unsigned int Random::seed_ = 0;
std::mt19937 Random::gen;

unsigned int Random::GetSeed()
{
	return seed_;
}

void Random::Init()
{
    std::random_device rd;
    // seed value is designed specifically to make initialization
    // parameters of std::mt19937 (instance of std::mersenne_twister_engine<>)
    // different across executions of application
    std::mt19937::result_type seed = rd() ^ (
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count() +
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count());

    Init(seed);
}

void Random::Init(unsigned int newSeed)
{
    //manually seed
    gen.seed(newSeed);
	seed_ = newSeed;
}

