#ifndef _MIKETIMER_INCLUDED_
#define _MIKETIMER_INCLUDED_

/******************************************************************************************************
simple timer class for measuring performance using the <time.h> library
has the following functions:
.reset - restarts the clock
.print - prints to console using cout the time elapsed from last .reset in miliseconds
.elapsed - returns a long which contains the time in miliseconds from when the last .reset was called
******************************************************************************************************/


	class Timer
	{
	public:
		Timer();

		void reset();
		void print();
		long elapsed();

	private:
		long start;
		long now;
	};



#endif // !_MIKETIMER_INCLUDED_
