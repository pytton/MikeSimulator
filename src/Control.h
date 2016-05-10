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
//	void tryout1();
	void printCurrentAll();

	//THIS IS WHAT I NEED TO REFACTOR!!!
	//CALLBACK FUNCTIONS FOR USERINTERFACE:
	void m_down_btn_cb(Fl_Widget *w, void * p);
	 void m_up_btn_cb(Fl_Widget *w, void * p);
	 void m_slider1_cb(Fl_Widget *w, void * p);

	//OLD CALLBACKS FOR REFERENCE:
	 void experimental2_cb(Fl_Widget *w, void * p);
	 void experimental_cb(Fl_Widget *w, void * p);
	 void experim3(Fl_Widget *w, void * p);	//THIS FUNCTION CHANGES SIZE OF WIDGETTABLE
	 void rePriceWidTable(Fl_Widget *w, void*p);	//UNDER CONSTRUCTION
	 void rePriceWidTable2(Fl_Widget *w, void*p);

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
