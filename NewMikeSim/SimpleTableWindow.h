#ifndef _SIMPLETABLEWINDOW_H_INCLUDED_
#define _SIMPLETABLEWINDOW_H_INCLUDED_

#include "FLUID\FluidSimpleTableWindow.h"
#include <string>
class FluidSimpleTableWindow;
class WidgetTable;
class Control;


class SimpleTableWindow :  FluidSimpleTableWindow
{
public:
	SimpleTableWindow();
	SimpleTableWindow(Control * ptrControl, short windownumber);
	~SimpleTableWindow();

	void rePriceWidTable(long bidprice);

	WidgetTable * widTable;
	
	short thiswindownumber; //for use by class creating SimpleTableWindow - if more than one instance of SimpleTableWindow is used. for callbacks which have to be static in FLTK
	
};

#endif //_SIMPLETABLEWINDOW_H_INCLUDED_
