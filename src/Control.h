#ifndef _CONTROL_H_INCLUDED_
#define _CONTROL_H_INCLUDED_

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
#include "UserInterface.h"
//#include "MktSnapshot.h"	//for Price and MktSnapshot



class Data;
class Control;
class MikeSimulator;

class Control
{
public:
	//constructor:
	Control(MikeSimulator*p);
	Control(MikeSimulator * p, int starting_bid);

	//member functions:
	void MainLoop();
	void ManualOrder(int type, long price);
	void CallbkWidTable();
	void CallbkWidTable(int row, int col, long price);
	void rePriceWidTable();
	//THIS NEEDS TO BE DONE!!! CURRENTLY JUST COPY/PASTE FROM uSERINTERFACE!!!
	//updates WidgetTable so that it shows prices around current bid/ask pulled from Data * data
	//updates slider in UserInterface the same way
//	void tryout1();
	void printCurrentAll();

	//THIS IS WHAT I NEED TO REFACTOR!!!
	//CALLBACK FUNCTIONS FOR USERINTERFACE:
	 void CallbkUserInt(UserInterface * p,
		 BtnPressed btn,
		 int parameter1 = 0,
		 int parameter2 = 0,
		 double parameter3 = 0.0);


	 //CALLBACKS FROM WIDGETTABLE:
	 static void button_cb(Fl_Widget *w, void * p);


	//int GetCurrentBid();	//Used by UserInterface
private:
		//members:
	MikeSimulator * ptr_to_mikesimulator;
	UserInterface * userInterface;
	Data * data;
	

};

#endif //_CONTROL_H_INCLUDED_
