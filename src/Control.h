#ifndef _CONTROL_H_INCLUDED_
#define _CONTROL_H_INCLUDED_

//#include <iostream>
//#include <fstream>
//#include <string>
#include <vector>
//#include "MikeEnums.h"
//#include "WidgetTable.h"
//#include "MikePositionsOrders.h"
#include "MikeTimer.h"


class WidgetTable;
class Data;
class Control;
class MikeSimulator;
class PriceControlUI;
class SimpleTableWindow;
class UserInterface;
class MikePosition;
class MikeOrder;
class MikePositionOrders;
class Fl_Widget;
class Timer;

enum BtnPressed;
enum MikeOrderType;

class Control
{
public:
	//constructor:

	Control(MikeSimulator * p, int starting_bid);

	static void timeoutfunction(void * p);

	//member functions:
	void MainLoop();
//	void ManualOrder(int type, long price);

	void rePriceWidTable(UserInterface * InterfaceToReprice);
	void rePriceWidTable();
	//THIS NEEDS TO BE DONE!!! CURRENTLY JUST COPY/PASTE FROM uSERINTERFACE!!!
	//updates WidgetTable so that it shows prices around current bid/ask pulled from Data * data
	//updates slider in UserInterface the same way
	void printCurrentAll();
	void printCurrentAll(long totalOpenPos,
		long totalOpenPL,
		long totalClosedPL,
		long totalPL,
		long askPrice,
		long bidPrice,
		std::vector <MikePosition> openPositions,
		std::vector <MikeOrder> openOrders);

	//THIS IS WHAT I NEED TO REFACTOR!!!
	//CALLBACK FUNCTIONS FOR USERINTERFACE:
	 void CallbkUserInt(UserInterface * p,
		 BtnPressed btn,
		 long longparameter1 = 0,
		 long longparameter2 = 0,
		 double parameter3 = 0.0);
	 void CallbkUserInt(UserInterface * p,
		 long price, 
		 MikeOrderType OrderTypePressed,
		 long orderSize = 100);
	 //CALLBACKS FROM WIDGETTABLE:
//	 virtual void CallbkWidTable(int row, int col, long price);
	 virtual void CallbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed);
	 virtual void CallbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed, int orderSize);
	//CALLBACKS FROM PRICECONTROLUI:
	 void CallbkPriceControlUI(PriceControlUI * p,
		 BtnPressed btn,
		 Fl_Widget * widgetPressed,
		 int parameter1 = 0,
		 int parameter2 = 0,
		 double parameter3 = 0.0);
	 //CALLBACKS FROM SIMPLETABLEWINDOW:
	 void CallbkSmplTableWin(int rowPressed, int colPressed, long price, short windownumber);

	 //getters/setters:
	 PriceControlUI * GetPriceControlUI(){ return m_pPriceControlUI; }

	//int GetCurrentBid();	//Used by UserInterface
private:
	//members:
	MikeSimulator * ptr_to_mikesimulator;	

	UserInterface * userInterface;
	
	Data * data;

	PriceControlUI * m_pPriceControlUI;

	MikePositionOrders * manualPositions;

	SimpleTableWindow * simpleTableWindow;
	
	//ManualInterface * manualInterface1;

	void startloop();//starts looping the MainLoop function
	void stoploop();//stops looping the MainLoop function
	bool stopMainLoop = false;//used by startloop and stoploop
	bool mainLoopActive = false;//used by startloop and stoploop
	bool mainLoopfinished = false;//this for the Fl::add_timeout function timeoutfunction - to ensure that another run of the MainLoop is not initiated before the MainLoop is finished processing
	bool livedatafeed = false;

	//static variables moved here and changed to non-static:
public:
	Timer timer;
	bool resetTimer;
	long previouselapsedtime;
};


#endif //_CONTROL_H_INCLUDED_
