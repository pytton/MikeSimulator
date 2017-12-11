#include "ControlUI.h"
#include <iostream>

using namespace std;

namespace Mike {
	ControlUI::ControlUI()
	{
		//assign the callbacks:
		mBtnStartLoop->callback(STARTLOOPfltkKBtncallback, (void*)this);
		mBtnStopLoop->callback(STOPLOOPfltkKBtncallback, (void*)this);
		mBtnShowPositions1->callback(POSITIONS1fltkKBtncallback, (void*)this);

		//show the window:
		mWindow->show();
	}

	ControlUI::~ControlUI()
	{
	}

	ControlUIEvent ControlUI::getNextEvent()
	{
		ControlUIEvent returnedEvent;
	
		//check if there are any elements to be processed. If there are none, return a dummy event set to EMPTY:
		if (mEventQueue.empty()) { 
			returnedEvent.mButtonPressed = ControlUIButton::EMPTY;
			return returnedEvent; }
		else
		{
			//get the first element, return it and remove it from the queue
			returnedEvent = mEventQueue.front();
			mEventQueue.pop();
			return returnedEvent;
		}
	}

	void ControlUI::addUserEvent(ControlUIButton btnPressedByUser)
	{
		//create the event and set which button has been pressed:
		ControlUIEvent pressedButton;
		pressedButton.mButtonPressed = btnPressedByUser;
		//add this event to the queue of this instance:
		mEventQueue.push(pressedButton);
	}

	void ControlUI::STARTLOOPfltkKBtncallback(Fl_Widget * w, void * pointerPassed)
	{
		ControlUIButton btnPressed = ControlUIButton::START_LOOP;
		cout << "Start loop button pressed." << endl;
		//pointerPassed is a void pointer to this instance of the class
		//add this event to the queue of this instance:
		((ControlUI*)pointerPassed)->addUserEvent(btnPressed);
	}

	void ControlUI::STOPLOOPfltkKBtncallback(Fl_Widget * w, void * pointerPassed)
	{
		ControlUIButton btnPressed = ControlUIButton::STOP_LOOP;

		//pointerPassed is a void pointer to this instance of the class
		//add this event to the queue of this instance:
		((ControlUI*)pointerPassed)->addUserEvent(btnPressed);
	}

	void ControlUI::POSITIONS1fltkKBtncallback(Fl_Widget * w, void * pointerPassed)
	{
		ControlUIButton btnPressed = ControlUIButton::POSITIONS1;

		//pointerPassed is a void pointer to this instance of the class
		//add this event to the queue of this instance:
		((ControlUI*)pointerPassed)->addUserEvent(btnPressed);
	}




}//namespace Mike