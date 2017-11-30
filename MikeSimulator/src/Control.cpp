#include "Control.h"
#include <iostream>


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
		//set up the user interface windows:
		dataControlWindow = new DataUI();
		dataControlWindow->m_window1->show();
		controlWindow = new ControlUI();
		controlWindow->m_window1->show();

		userinterface = new UserInterface(this);
		userinterface->m_window1->show();
	}


	Control::~Control()
	{
	}




	void Control::mainloop()
	{
		mainLoopRunning = true;

		//do everything that needs to be done:

		processData();
		processUserInput();
		printoutAll();
		processAlgos();

		mainLoopRunning = false;
		//start the loop again:
		mainloopTimeoutCallbackFLTK(this);		
	}

	void Control::mainloopTimeoutCallbackFLTK(void * ptrControlPointer)
	{
		Control * control = (Control*)ptrControlPointer;
		//check if we want to stop the loop. if not, call mainloop in SET_MAINLOOP_INTERVAL seconds
		if (!control->flagStopMainLoop) Fl::repeat_timeout(SET_MAINLOOP_INTERVAL,startloop , ptrControlPointer);
	}
	void Control::startloop(void * ptrControlPointer)
	{	
		Control * ptr = (Control*)ptrControlPointer;
		//make sure the trigger to stop the loop inside timeoutfunction is off:
		ptr->flagStopMainLoop = false;
		//check to see if the loop is already running. if it is not, start the loop:
		if (!ptr->mainLoopRunning) ptr->mainloop();
		//try again in 200 ms:
		else { Sleep(200); startloop(ptrControlPointer); }
	}
	void Control::stoploop()
	{
		//if the loop is already set up to be stopped, do nothing:
		if (flagStopMainLoop) return;
		//if it is not set to be stopped, set the trigger to stop it inside the timeoutfunction:
		flagStopMainLoop = true;
	}
	void Control::CallbkUserInt(UserInterface * p, BtnPressed btn, long longparameter1, long longparameter2, double parameter3)
	{
	}
	void Control::CallbkUserInt(UserInterface * p, long price, MikeOrderType OrderTypePressed, long orderSize)
	{
	}
	void Control::callbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed, int orderSize)
	{
	}
}//namespace Mike