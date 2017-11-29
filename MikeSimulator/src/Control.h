#pragma once

#include <math.h>

#include "FluidPriceControl.h"

namespace Mike
{
	int frequency_of_primes(int n) {
		int i, j;
		int freq = n - 1;
		for (i = 2; i <= n; ++i) for (j = sqrt(i); j>1; --j) if (i%j == 0) { --freq; break; }
		return freq;
	}




	/*!amount of seconds used by mainloopTimeoutCallbackFLTK() to determine how long to wait after mainloop() is finished before initiating another mainloop() function call*/
	const static double SET_MAINLOOP_INTERVAL = 0.1;

	class Control
	{

		typedef FluidPriceControlUI DataUI;
		typedef int ControlUI;
	public:
		Control();
		~Control();

		/*!This is how you start the program. Starts looping the MainLoop function*/
		void startloop();
		/*!Use this to pause execution of the program. Stops looping the MainLoop function*/
		void stoploop();
	private:
		/*! The core of the program. This function runs in a continous loop and handles all events.
		Everything that happens is handled by functions inside this loop. */
		void mainloop();
		/*! Makes the mainloop() function loop continously in intervals set by SET_MAINLOOP_INTERVAL. Has to be static per FLTK.*/
		static void mainloopTimeoutCallbackFLTK(void * ptrControlPointer);
		/*!used internally by mainloopTimeoutCallbackFLTK, startloop and stoploop */
		bool flagStopMainLoop = false;
		/*!'Thread guard' used by mainloopTimeoutCallbackFLTK, startloop and stoploop */
		bool mainLoopRunning = false;
		/*!this a 'thread guard' for the Fl::add_timeout function timeoutfunction - to ensure that another run of the MainLoop is not initiated before the MainLoop is finished processing*/		
		bool mainLoopfinished = false;






		/*!
		DataUI is a User Interface Window used to control everything associated with market price data.
		This is designed to grow. Market price data can be either pulled from Interactive Brokers using
		Jan Boonen's library or it can be switched to 'manual' to explore behaviour of algos.
		*/
		DataUI * priceControl;
	};
}

