//ASCII ART FROM HERE: http://www.patorjk.com/software/taag/#p=display&h=0&c=c%2B%2B&f=Banner3&t=Control
//   ____  ____  _      _____  ____  ____  _    
//  /   _\/  _ \/ \  /|/__ __\/  __\/  _ \/ \   
//  |  /  | / \|| |\ ||  / \  |  \/|| / \|| |   
//  |  \__| \_/|| | \||  | |  |    /| \_/|| |_/\
//  \____/\____/\_/  \|  \_/  \_/\_\\____/\____/
//                                              



#ifndef _CONTROL_H_INCLUDED_
#define _CONTROL_H_INCLUDED_

#include <vector>
#include "MikeTimer.h"

#include "PosOrders.h"



class WidgetTable;
class Data;
class Control;
class Simulator;
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

	typedef std::vector<MikePosition> MikePosVect;
public:
	//constructor:

	Control(Simulator * p, int starting_bid);


	//member functions:
	void MainLoop();
	static void timeoutfunction(void * p);
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
		MikePosVect openPositions,
		std::vector <MikeOrder> openOrders);


	//                _  _  _                   _            
	//    ___   __ _ | || || |__    __ _   ___ | | __ ___  _ 
	//   / __| / _` || || || '_ \  / _` | / __|| |/ // __|(_)
	//  | (__ | (_| || || || |_) || (_| || (__ |   < \__ \ _ 
	//   \___| \__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)
	//                                                       
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
	 void CallbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed, int orderSize);
	//CALLBACKS FROM PRICECONTROLUI:
	 void CallbkPriceControlUI(PriceControlUI * p,
		 BtnPressed btn,
		 Fl_Widget * widgetPressed,
		 int parameter1 = 0,
		 int parameter2 = 0,
		 double parameter3 = 0.0);
	 //CALLBACKS FROM SIMPLETABLEWINDOW:
	 void CallbkSmplTableWin(int rowPressed, int colPressed, long price, short windownumber);


	 //                _    _                        __            _    _                       
	 //    __ _   ___ | |_ | |_   ___  _ __  ___    / / ___   ___ | |_ | |_   ___  _ __  ___  _ 
	 //   / _` | / _ \| __|| __| / _ \| '__|/ __|  / / / __| / _ \| __|| __| / _ \| '__|/ __|(_)
	 //  | (_| ||  __/| |_ | |_ |  __/| |   \__ \ / /  \__ \|  __/| |_ | |_ |  __/| |   \__ \ _ 
	 //   \__, | \___| \__| \__| \___||_|   |___//_/   |___/ \___| \__| \__| \___||_|   |___/(_)
	 //   |___/                                                                                 
	 //getters/setters:
	 PriceControlUI * GetPriceControlUI(){ return m_pPriceControlUI; }

	//int GetCurrentBid();	//Used by UserInterface
private:
	//members:
	Simulator * ptr_to_mikesimulator;//ptr to class creating this one
	UserInterface * userInterface;
	Data * data;
	PriceControlUI * m_pPriceControlUI;
	MikePositionOrders * manualPositions;
	SimpleTableWindow * simpleTableWindow;//testing new things
	
	//ManualInterface * manualInterface1;

	//starts looping the MainLoop function:
	void startloop();
	//stops looping the MainLoop function
	void stoploop();
	//used by startloop and stoploop
	bool stopMainLoop = false;
	//used by startloop and stoploop
	bool mainLoopActive = false;
	//this for the Fl::add_timeout function timeoutfunction - to ensure that another run of the MainLoop is not initiated before the MainLoop is finished processing
	bool mainLoopfinished = false;
	bool livedatafeed = false;

	//static variables moved here and changed to non-static:
protected:
	Timer timer;
	bool resetTimer;
	long previouselapsedtime;
};




#endif //_CONTROL_H_INCLUDED_
