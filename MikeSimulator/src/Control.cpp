#include "Control.h"
#include <iostream>
#include <time.h> //for time(NULL)



using namespace std;
namespace Mike
{
	/*! used for testing purposes to occupy CPU */
	int frequency_of_primes(int n) {
		int i, j;
		int freq = n - 1;
		for (i = 2; i <= n; ++i) for (j = sqrt(i); j>1; --j) if (i%j == 0) { --freq; break; }
		return freq;
	}

	Control::Control()
	{
		//initialize and show the control window:
		mptrControlWindow = new ControlUI();
		//mptrControlWindow->mWindow->show();

		//initialize data:
		mptrData = new Data();

	}


	Control::~Control()
	{
		if (NULL != mptrData) delete mptrData;
		if (NULL != mptrControlWindow) delete mptrControlWindow;
	}

	void Control::mainloop()
	{
		mainLoopRunning = true;
		
		//do everything that needs to be done:
		cout << "mainloop called " << time(NULL) << endl;

		processData();
		processUserInput(this);
		printoutAll();
		processAlgos();

		mainLoopRunning = false;
		//start the loop again:
		mainloopTimeoutCallbackFLTK(this);		
	}

	void Control::processUserInput(void * ptrControlPointer)
	{
		Control * ptr = (Control*)ptrControlPointer;
		//Testing here:

		if (ptr->mptrControlWindow->eventsWaiting()) {
			ControlUIEvent myEvent = ptr->mptrControlWindow->getNextEvent();
			switch (myEvent.mButtonPressed)
			{
			case ControlUIButton::START_LOOP:
				cout << "Start loop button pressed." << endl;
				startloop(ptr);
				break;
			case ControlUIButton::STOP_LOOP:
				cout << "STOP loop button pressed." << endl;
				break;
				
			case ControlUIButton::POSITIONS1:
				cout << "Positions1 button pressed." << endl;
				break;
			default:
				break;
			}
		}
	}

	void Control::mainloopTimeoutCallbackFLTK(void * ptrControlPointer)
	{
		Control * control = (Control*)ptrControlPointer;
		//check if we want to stop the loop. if not, call mainloop in SET_MAINLOOP_INTERVAL seconds
		if (!control->flagStopMainLoop) Fl::add_timeout(SET_MAINLOOP_INTERVAL, startloop, ptrControlPointer);
	}
	void Control::startloop(void * ptrControlPointer)
	{
		Control * ptr = (Control*)ptrControlPointer;
		//make sure the trigger to stop the loop inside timeoutfunction is off:
		ptr->flagStopMainLoop = false;
		//check to see if the loop is already running. if it is not, start the loop:
		if (!ptr->mainLoopRunning) ptr->mainloop();
	}

	void Control::stoploop()
	{
		//if the loop is already set up to be stopped, do nothing:
		if (flagStopMainLoop) return;
		//if it is not set to be stopped, set the trigger to stop it inside the timeoutfunction:
		flagStopMainLoop = true;
	}

}//namespace Mike