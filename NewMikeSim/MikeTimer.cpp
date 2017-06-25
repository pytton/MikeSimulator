#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <iostream>
#include "MikeTimer.h"

//using namespace Mike;

//namespace Mike {
	Timer::Timer()
	{
		start = clock();
		now = clock();
	}

	void Timer::reset()
	{
		start = clock();
		now = clock();
	}

	void Timer::print()
	{
		long tempnow = clock();
		long elapsedTime;
		elapsedTime = tempnow - start;

		std::cout << " Time elapsed: " << elapsedTime << std::endl;
	}

	long Timer::elapsed()
	{
		now = clock();
		long elapsedTime;
		elapsedTime = now - start;

		return elapsedTime;
	}

//}