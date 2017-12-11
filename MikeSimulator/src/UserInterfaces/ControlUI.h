#pragma once

#include "..\FLUID\FluidControlInterface.h"
#include <queue>


namespace Mike {
	enum class ControlUIButton {
		START_LOOP,
		STOP_LOOP,
		POSITIONS1,
		EMPTY
	};

	/*! Simple struct holding buttons/events pressed by user. Yes perhaps in this class it could be a simple enum instead - but creating this for symmetry in other classes where additional parameters might need to be passed.*/
	struct ControlUIEvent
	{
		ControlUIButton mButtonPressed;
	};

	/*! Creates a window with buttons for controlling the Control class. Use FLUID software to design/modify the window described in FluidControlInterface.h - this class inherits from it. */
	class ControlUI : public FluidControlInterface
	{
		friend class Control;
	public:
		/*! Constructor. Displays the window by default. Assign callbacks here. */
		ControlUI();
		~ControlUI();

		/*! Returns true if there are any callbacks in the queue (mEventQueue) that are waiting to be handled. False if queue is empty.*/
		bool eventsWaiting() { return !mEventQueue.empty(); }

		/*! Not thread safe. Check that queue is not empty using eventsWaiting() before calling this. Returns the next event from the mEventQueue and removes that item from the queue. If this event is notprocessed by the caller then it is lost. Returns a dummy event with mButtonPressed = EMPTY if there are no elements in the queue and the caller decided to call this function without checkig for that.  */
		ControlUIEvent getNextEvent();

	private:
		/*!Queue for handling callbacks. All callbacks are added to a queue.
		Use method bool eventsWaiting() to check if any button have been pressed.
		Use method getNextEvent to get next callback and remove it from the queue
		*/
		std::queue<ControlUIEvent> mEventQueue;
		/*!Used by FLTK static callbacks to add buttons pressed by user to mEventQueue*/
		void addUserEvent(ControlUIButton btnPressedByUser);

		//CALLBACKS:
		/*!FLTK callback for pressing StartLoop button*/
		static void STARTLOOPfltkKBtncallback(Fl_Widget * w, void * pointerPassed);
		/*!FLTK callback for pressing StopLoop button*/
		static void STOPLOOPfltkKBtncallback(Fl_Widget * w, void * pointerPassed);
		/*!FLTK callback for pressing Positions1 button*/
		static void POSITIONS1fltkKBtncallback(Fl_Widget * w, void * pointerPassed);

		
	};
}//namespace Mike