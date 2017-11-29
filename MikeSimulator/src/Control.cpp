#include "Control.h"
#include <iostream>
#include <mutex>

using namespace std;
namespace Mike
{
	Control::Control()
	{
		priceControl = new DataUI();

		priceControl->m_window1->show();
	}


	Control::~Control()
	{
	}




	void Control::mainloop()
	{
		mainLoopRunning = true;

		std::cout << "Printed from mainloop" << std::endl;

		int processTime = frequency_of_primes(20000);

		cout << "Searched for primes: " << processTime << endl;


		mainLoopRunning = false;
		
	}

	void Control::mainloopTimeoutCallbackFLTK(void * ptrControlPointer)
	{
		Control * control = (Control*)ptrControlPointer;

		////commented out. this used to monitor the execution time of mainloop:
		//if (control->resetTimer) {
		//	control->timer.reset(); control->resetTimer = false;
		//}
		////	cout << "\MainLoop process time: "<< (control->timer.elapsed() - control->previouselapsedtime - 150) << endl;//150 because 0.15 in Fl::repeat_timeout(0.15, timeoutfunction,(void*) p);
		//control->previouselapsedtime = control->timer.elapsed();


		std::cout << "mainloopTimeoutCallbackFLTK called" << std::endl;
		//check if mainloop has finished executing. if it has, execute the code in mainloop:
		/*if (!control->mainLoopRunning)*/ { control->mainloop(); std::cout << "starting mainloop" << std::endl; }
		//check if we want to stop the loop. if not, call mainloop in SET_MAINLOOP_INTERVAL seconds
		if (!control->flagStopMainLoop) Fl::repeat_timeout(SET_MAINLOOP_INTERVAL, mainloopTimeoutCallbackFLTK, (void*)ptrControlPointer);
	}
	void Control::startloop()
	{
		std::cout << "startloop called" << std::endl;
		//check to see if the loop is already running. if it is not, start the loop:
		if (!mainLoopRunning) {
			Fl::add_timeout(SET_MAINLOOP_INTERVAL, mainloopTimeoutCallbackFLTK, (void*) this);
			mainLoopRunning = true;
			//and make sure the trigger to stop the loop inside timeoutfunction is off:
			flagStopMainLoop = false;
			return;
		}
		else startloop();

	}

	void Control::stoploop()
	{
		//if the loop is already set up to be stopped, do nothing:
		if (flagStopMainLoop) return;
		//if it is not set to be stopped, set the trigger to stop it inside the timeoutfunction:
		flagStopMainLoop = true;
	}
}