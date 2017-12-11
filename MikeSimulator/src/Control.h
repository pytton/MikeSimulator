#pragma once
//ASCII ART FROM HERE: http://www.patorjk.com/software/taag/#p=display&h=0&c=c%2B%2B&f=Banner3&t=Control

#include <math.h>
#include <thread> //for this_thread
#include <mutex>

#include "FLUID\FluidControlInterface.h"


#include "MikeEnums.h"
#include "Data.h"
#include "UserInterfaces\ControlUI.h"

namespace Mike
{

	class UserInterface;

	/*!amount of seconds used by mainloopTimeoutCallbackFLTK() to determine how long to wait after mainloop() is finished before initiating another mainloop() function call*/
	const static double SET_MAINLOOP_INTERVAL = 0.3;

	class Control
	{	//   _                            _         __         
		//  | |_  _   _  _ __    ___   __| |  ___  / _| ___  _ 
		//  | __|| | | || '_ \  / _ \ / _` | / _ \| |_ / __|(_)
		//  | |_ | |_| || |_) ||  __/| (_| ||  __/|  _|\__ \ _ 
		//   \__| \__, || .__/  \___| \__,_| \___||_|  |___/(_)
		//        |___/ |_|                                    

		/*! ControlUI is a window handling the Control class */
	//	typedef FluidControlInterface ControlUI;

	public:
		Control();
		~Control();

		/*!This is how you start the program. Starts looping the MainLoop function. void pointer has to be of Control type*/
		static void startloop(void * ptrControlPointer);
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
		/*! Handles all events related to market data*/
		void processData() {}
		/*! All user interactions with graphical user interfaces handled here */
		static void processUserInput(void * ptrControlPointer);
		/*! Printing out all information to user interfaces handled here */
		void printoutAll() {}
		/*! Handles all algo events (checkfills, make decisions, place/modify/cancel orders */
		void processAlgos() {}



		/*! FLTK window for controlling the Control class */
		ControlUI * mptrControlWindow;
		/*! Used for market prices and OrderServer*/
		Data * mptrData;


	};
}

