#include "MikeHelpers.h"

#include <sstream>


Mike::StringInputFLTK::StringInputFLTK()
{
	mWindow1->begin();
	mOkButton->callback(okBtnCallback, (void*) this);
	mWindow1->hide();
	mWindow1->redraw();
//	mWindow1->show();
}

void Mike::StringInputFLTK::okBtnCallback(Fl_Widget * w, void * window)
{
	StringInputFLTK * mywindow = (StringInputFLTK *) window;
	//put the value present in input window into mReturnString and let class know it is ready:
	mywindow->mReturnString= mywindow->mInputField->value();
	mywindow->mValueReady = true;
}

std::string Mike::StringInputFLTK::getStringValue(std::string query)
{
	if (!mWindowIsDisplayed) {
		mDisplayedQuery = query;
		//change the label and show the window:
		mInputField->label(query.c_str()); //what is the name of the thing you are asking for?
		mWindow1->redraw();
		mWindow1->show();
	}
	mWindowIsDisplayed = true;
	//wait for OK button has been pressed - if yes, then return string:
	if (!mTimeoutRunning) Fl::add_timeout(0.1, timeoutFunction, (void*)this);

	if (mValueReady) {
		//	while (!mOkBtnPressed) { Sleep(10); }
		mWindow1->hide();
		return mReturnString;
	}
}

void Mike::StringInputFLTK::timeoutFunction(void * p)
{
	StringInputFLTK * myWidget = (StringInputFLTK *)p;
	if (!myWidget->mValueReady) Fl::repeat_timeout(0.1, timeoutFunction, p);
	myWidget->getStringValue(myWidget->mDisplayedQuery);
}

Mike::SimpleStringInputFLTK::SimpleStringInputFLTK(std::string query)
{
	std::stringstream buffer;
	buffer << query;

	mWindow1->begin();
	mOkButton->callback(okBtnCallback, (void*) this);

//	mInputField->label(buffer.str().c_str());
//	mInputField->label(query.c_str()); //what is the name of the thing you are asking for?
	mWindow1->end();

	mWindow1->hide();
	mWindow1->redraw();
	mWindow1->show();
}

void Mike::SimpleStringInputFLTK::okBtnCallback(Fl_Widget * w, void *window)
{
	SimpleStringInputFLTK * mywindow = (SimpleStringInputFLTK *)window;
	//put the value present in input window into mReturnString and let class know it is ready:
	mywindow->mReturnString = mywindow->mInputField->value();
	mywindow->mValueReady = true;
}
