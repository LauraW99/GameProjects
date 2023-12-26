#pragma once
#include <random>
#include "../Math/Math.h"
class Random
{
	static unsigned int seed_;

	static std::mt19937 gen;


public:
	static unsigned int GetSeed();

	static void Init();
	static void Init(unsigned int newSeed);


	template<typename T>
	static T Next()
	{
		return static_cast<T>(gen());
	}

	template<typename T>
	static T Next(T Min, T Max)
	{
		T v = static_cast<T>(gen());
		T mmin = static_cast<T>(gen.min());
		T mmax = static_cast<T>(gen.max());
		T rM = RemapValueRange<T>(v, mmin, mmax, Min, Max);
 		return rM;
	}
};
