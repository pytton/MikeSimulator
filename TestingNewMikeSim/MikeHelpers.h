#ifndef _MIKEHELPERS_H_INCLUDED_
#define _MIKEHELPERS_H_INCLUDED_

//Various helpful classes

#include "FLUID\CFluidInputUI.h"

#include <string>

namespace Mike {
	//simple class to get a string from an input window. Usage: create class, then call getStringValue function
	//passing the name of the thing you are asking for as a parameter
	class StringInputFLTK : public CFluidInputUI
	{
	public:
		StringInputFLTK();
		static void okBtnCallback(Fl_Widget * w, void *);
		std::string getStringValue(std::string query);
		std::string mReturnString;


	private:
		bool mWindowIsDisplayed = false;
		bool mValueReady = false;
		static void timeoutFunction(void * p);
		bool mTimeoutRunning = false;
		std::string mDisplayedQuery;
	};

	class SimpleStringInputFLTK : public CFluidInputUI
	{
	public:
		SimpleStringInputFLTK(std::string query);
		static void okBtnCallback(Fl_Widget * w, void *);
		std::string getStringValue(std::string query);
		std::string mReturnString;



		bool mWindowIsDisplayed = false;
		bool mValueReady = false;
		static void timeoutFunction(void * p);
		bool mTimeoutRunning = false;
		std::string mDisplayedQuery;
	};
}//namespace Mike


#endif //_MIKEHELPERS_H_INCLUDED_