#ifndef _CONTROL_H_INCLUDED_
#define _CONTROL_H_INCLUDED_

//#include <iostream>
//#include <fstream>
//#include <string>
#include <vector>
//#include "MikeEnums.h"
//#include "WidgetTable.h"
//#include "MikePositionsOrders.h"



class WidgetTable;
class Data;
class Control;
class MikeSimulator;
class PriceControlUI;
class UserInterface;
class MikePosition;
class MikeOrder;
class MikePositionOrders;
class Fl_Widget;

enum BtnPressed;
enum MikeOrderType;

class Control
{
public:
	//constructor:

	Control(MikeSimulator * p, int starting_bid);

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
	//CALLBACKS FROM PRICECONTROLUI:
	 void CallbkPriceControlUI(PriceControlUI * p,
		 BtnPressed btn,
		 Fl_Widget * widgetPressed,
		 int parameter1 = 0,
		 int parameter2 = 0,
		 double parameter3 = 0.0);

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
	
	//ManualInterface * manualInterface1;

};


#endif //_CONTROL_H_INCLUDED_
