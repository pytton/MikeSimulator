#include "Control.h"

#include <iostream>

#include "IntegratorPosUI.h"
#include "UserInterface.h"
#include "MikeSimulator.h"
#include "Data.h"
#include "WidgetTable.h"
#include "MikeEnums.h"
#include "MikeTimer.h"

#include "PriceControlUI.h"
//#include "SimpleTableWindow.h"
#include "ManualInterface.h"
#include "MikePositionsOrders.h"
#include "MikeHelpers.h"

#include "PosOrders.h"

/////////////////////////////////
//erase after testing:
#include "PositionBook.h"
class PositionBook;
/////////////////////////////////
using namespace std;
//using namespace Mike;

class Mike::UserInterfaceLinked;


//     ___   ___                           __    __  _____  __     ___     __  ___ 
//    / __\ /___\ /\/\    /\/\    /\/\    /__\/\ \ \/__   \/ _\   /___\ /\ \ \/ _ \
//   / /   //  ///    \  /    \  /    \  /_\ /  \/ /  / /\/\ \   //  ///  \/ /\// /
//  / /___/ \_/// /\/\ \/ /\/\ \/ /\/\ \//__/ /\  /  / /   _\ \ / \_/// /\  /   \/ 
//  \____/\___/ \/    \/\/    \/\/    \/\__/\_\ \/   \/    \__/ \___/ \_\ \/    () 
//                                                                                 
//commment switch
//#define MIKE_COMMENTSON false


int frequency_of_primes(int n) {
	cout << "Primes calculating..." << endl;
	int i, j;
	int freq = n - 1;
	for (i = 2; i <= n; ++i) for (j = sqrt(i); j>1; --j) if (i%j == 0) { --freq; break; }
	return freq;
}


Control::Control(MikeSimulator * p, int starting_bid)
{
	ptr_to_mikesimulator = p;
	std::cout << "Control constructed. Starting bid: " << starting_bid << std::endl;

	////////////////////////////////////////////////////////////////////////

	//                                  _                          _   
	//    ___ __  __ _ __    ___  _ __ (_) _ __ ___    ___  _ __  | |_ 
	//   / _ \\ \/ /| '_ \  / _ \| '__|| || '_ ` _ \  / _ \| '_ \ | __|
	//  |  __/ >  < | |_) ||  __/| |   | || | | | | ||  __/| | | || |_ 
	//   \___|/_/\_\| .__/  \___||_|   |_||_| |_| |_| \___||_| |_| \__|
	//              |_|                                                

	
//	userInterface = new Mike::UserInterfaceLinked();
//	userInterface2 = new Mike::UserInterfaceLinked();
//	userInterface2->m_window1->label("Developing IntegratorUI");

	//integratedPositions = new Mike::IntegratorPosUI();

	//simpleTableWindow = new SimpleTableWindow(this, 3);
	////////////////////////////////////////////////////////////////////////

	userInterface = new UserInterface(this, /*p,*/ starting_bid);
	userInterface->m_window1->label("Positions");




	data = new Data(this, starting_bid);
	m_pPriceControlUI = new PriceControlUI(this, starting_bid);
	manualPositions = new MikePositionOrders("Manual", 1000000);
	userInterface->setTargetPositions(manualPositions);
	rePriceWidTable(userInterface);



	//work in proggress below:
	manualPositions2 = new MikePositionOrders("Manual2", 1000000);
	userInterface2 = new UserInterface(this, starting_bid);
	userInterface2->m_window1->label("Short Positions");
	userInterface2->setTargetPositions(manualPositions2);


	
	//setting up previous static variables in Control::timeoutfunction(void*p)
	timer.reset();
	resetTimer = true;
	previouselapsedtime = 0;
	
	//experimenting:
	experimentConstructor();

	controlUI = new Mike::ControlInterface();
	controlUI->setCallbackDestination(this);
	
	//end experiment
}

void Control::timeoutfunction(void*p)
{
	using namespace std;
	Control * control = (Control*)p;
	if (control->resetTimer) {
		control->timer.reset(); control->resetTimer = false;
	}
	
//	cout << "\MainLoop process time: "<< (control->timer.elapsed() - control->previouselapsedtime - 150) << endl;//150 because 0.15 in Fl::repeat_timeout(0.15, timeoutfunction,(void*) p);
	control->previouselapsedtime = control->timer.elapsed();
	control->MainLoop();
	if (!control->stopMainLoop) Fl::repeat_timeout(0.15, timeoutfunction,(void*) p);	
}


void Control::MainLoop()
{
	//experimenting:
	//TODO: Erase this after finished experimenting
	if (mExperimentActive) experimenting();
	//end experiment

	using namespace std;
	mainLoopfinished = false;//to ensure that the timeoutfunction does not call it again while it is executing
								 
	//TODO: work on 1 and 2 first
	//1 check prices	-- this is done by manual up/down now
	int tickerId = 3;//1-EUR, 2-GBP, 3-SPY, 4-DIA, 5-IWM, 6-QQQ
	if (livedatafeed) data->updateLiveData(tickerId);
	//2 check fills

	manualPositions->checkFills(data->GetBidPrice(), data->GetAskPrice());
	manualPositions->updateOpenOrdersByPrice();

	manualPositions2->checkFills(data->GetBidPrice(), data->GetAskPrice());
	manualPositions2->updateOpenOrdersByPrice();

	
	//2a check/print current position, profit/loss, etc
	//3 make decisions	-- now just manual orders
	//4 display results/decisions
//	data->PrintoutDataInConsole();
	

	//TODO: May 2019 - will this work?
	//printCurrentAll();
	printCurrentAll(userInterface, manualPositions);
	printCurrentAll(userInterface2, manualPositions2);
	
	//add other functions as needed
	//5 send orders		-- for algos - nothing now
	if (userInterface != nullptr) userInterface->PrintBidAsk(data->GetBidPrice(), data->GetAskPrice());
	if (userInterface2 != nullptr) userInterface2->PrintBidAsk(data->GetBidPrice(), data->GetAskPrice());

	//print out the size in bytes of positionbook for testing purposes:
//	cout << sizeof(*(manualPositions->GetMikePositions())) << endl;
	//cout << sizeof(*manualPositions) << endl;
//	PositionBook * tempPos;
//	tempPos = manualPositions->positionbook;
	//cout << tempPos->positionBook.size() << endl;
	//cout << sizeof(MikePosition) * (tempPos->positionBook.size()) << endl;
	//
	//cout << sizeof(*tempPos) << endl;
//	cout << sizeof(MikePosition) << endl;
//	cout << manualPositions->positionbook.size() << endl;

	mainLoopfinished = true;//to ensure that the timeoutfunction does not call it again while it is executing
}

void Control::printCurrentAll(UserInterface * myInface, MikePositionOrders * myPosOrders)
{
	Data* myData = data;
	UserInterface* myInterface = myInface;
	MikePositionOrders* myPositionOrders = myPosOrders;

	if (myData == nullptr) return;
	if (myInterface == nullptr) return;
	if (myPositionOrders == nullptr) return;

	const MikePosVect * constPositions = myPositionOrders->GetMikePositions();

	const std::vector<MikeOrdersAtPrice> * ordersAtPrice = myPositionOrders->GetOpOrdersbyPrice();

	long
		totalOpenPos,
		totalOpenPL,
		totalClosedPL,
		totalPL,
		askPrice,
		bidPrice;

	double averagePrice = myPositionOrders->CalcAvgPos();

	askPrice = myData->GetAskPrice();
	bidPrice = myData->GetBidPrice();

	totalOpenPos = myPositionOrders->CalcTotalOpenPos();
	totalOpenPL = myPositionOrders->CalcAllOpenPL(bidPrice, askPrice);
	totalClosedPL = myPositionOrders->CalcAllClosedPL(bidPrice, askPrice);
	totalPL = myPositionOrders->CalcAllTotalPL(bidPrice, askPrice);

	myInterface->PrintAll(
		totalOpenPos,
		totalOpenPL,
		totalClosedPL,
		totalPL,
		askPrice,
		bidPrice,
		constPositions,
		ordersAtPrice,
		averagePrice
	);
}

void Control::printCurrentAll()
{
	UserInterface * myInterface = userInterface;
	MikePositionOrders * myPositionOrders = manualPositions;

	printCurrentAll(myInterface, myPositionOrders);
}


//callbacks:
//                _  _  _                   _            
//    ___   __ _ | || || |__    __ _   ___ | | __ ___  _ 
//   / __| / _` || || || '_ \  / _` | / __|| |/ // __|(_)
//  | (__ | (_| || || || |_) || (_| || (__ |   < \__ \ _ 
//   \___| \__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)
//                                                       

//USERINTERFACE HANDLED HERE:
//btn chooses what to do, UserInterface *p
//provides the data, parameters optional
void Control::CallbkUserInt(UserInterface * p, BtnPressed btn)
{
	MikePositionOrders * manualPositions = p->m_pTargetPositions;
	if (btn == BtnPressed::EXTRABTN)
	{
	//	cout << "Extra button pressed - implement this!!!!" << endl;
		rePriceWidTable(p);
	}
	if (btn == BtnPressed::PRINTORDERSBTN)
	{

		cout << "manualPositions->printoutAllOrders();" << endl;
	//	manualOrders->printoutAllOrders();
		//TODO: Print orders in WidgetTable
	}
	if (btn == BtnPressed::CHECKFILLS)
	{
		long bidPrice, askPrice;
		bidPrice = data->GetBidPrice();
		askPrice = data->GetAskPrice();

		manualPositions->checkFills(bidPrice, askPrice);
	}
	if (btn == BtnPressed::PRINTPOS)
	{
		long bidprice = data->GetBidPrice();
		long askprice = data->GetAskPrice();
		manualPositions->printoutActivePositions(bidprice, askprice);
	}
	if (btn == BtnPressed::CANCELALLORDERS)
	{
		cout << "Cancelling all orders" << endl;
		manualPositions->cancelAllOpenOrders();
		printCurrentAll();
	}
	if (btn == BtnPressed::CLEARALLPOSITIONS)
	{
		cout << "Clearing all positions" << endl;
		manualPositions->clearAllPositions();
		printCurrentAll();
	}
}
//WIDGETTABLE:
/*
Call sequence is as follows:
1. user presses button inside WidTableBase.cpp
2. this calls static void WidTableBase::button_cb(Fl_Widget *w, void * p)
3. which calls virtual void WidTableBase::virtButtonCb(Fl_Widget *w, void * p) - this is an empty function which needs to be implemented in derived classes.
4. in WidgetTable.ccp - void WidgetTable::virtButtonCb(Fl_Widget * w, void * p) which:
5. determines what button was pressed, at what price, and sends this info to:
6. virtual void UserInterfaceBase::callbkWidTable(int rowPressed, int colPressed, long price) which:
7. determines what type of button was pressed, gets the value of the order from Fl_Input which is part of UserInterfaceBase, and send callback to virtual function implemented in derived classes. In this case:
8. void UserInterface::sendWidTableCallback(int rowPressed, int colPressed, long price, MikeOrderType tempOrderType, int orderSize) which calls:
9. void Control::callbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed, int orderSize)

SUGGESTION - put all of this in one function located in UserInterfaceLinked
*/



void Control::callbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed, int orderSize, MikePositionOrders* targetPos)
{
	MikePositionOrders* manualPositions = targetPos;
	//send order to OrderBook if order type is not 'cancel order':	
	if (OrderTypePressed != CXLORDER) { manualPositions->newOrder(OrderTypePressed, price, orderSize); }
	if (OrderTypePressed == CXLORDER) { manualPositions->cancelAllOrdAtPrice(price); }
	//check for fills:
	manualPositions->checkFills(data->GetBidPrice(), data->GetAskPrice());
	MainLoop();
	

}


//PRICECONTROLUI
void Control::CallbkPriceControlUI(PriceControlUI * p, BtnPressed btn, Fl_Widget * widgetPressed, int parameter1, int parameter2, double parameter3)
{
	if (btn == BtnPressed::UPBTN)
	{
		PriceControlUI * myPriceControl = (PriceControlUI*)p;
		Data * myData = data;
		//change bid ask prices:
		myData->SetPrevAskPrice(myData->GetAskPrice());
		myData->SetPrevBidPrice(myData->GetBidPrice());
		myData->SetAskPrice(myData->GetAskPrice() + 1);
		myData->SetBidPrice(myData->GetBidPrice() + 1);
		//update slider value:
		myPriceControl->Getm_slider1()->value((double)myData->GetBidPrice());
		//do something:
		//startloop();//HACK:experimenting, erase once finished experimenting
		this->MainLoop();

	}
	if (btn == BtnPressed::DOWNBTN) {
		//REFACTOR THIS:

	//	cout << "refactored  m_down_btn_cb called" << endl;
		PriceControlUI * myPriceControl = (PriceControlUI*)p;
		Data * myData = data;
		//change bid ask prices:
		myData->SetPrevAskPrice(myData->GetAskPrice());
		myData->SetPrevBidPrice(myData->GetBidPrice());
		myData->SetAskPrice(myData->GetAskPrice() - 1);
		myData->SetBidPrice(myData->GetBidPrice() - 1);
		//update slider value:		
		myPriceControl->Getm_slider1()->value((double)myData->GetBidPrice());
		//do something:
		//stoploop();//HACK:experimenting, erase once finished experimenting
		this->MainLoop();
		
	}
	if (btn == BtnPressed::SLIDER1)
	{
		//REFACTOR COMPLETE

		PriceControlUI * myPriceControl = (PriceControlUI*)p;
		Fl_Value_Slider * mySlider = (Fl_Value_Slider*) widgetPressed;
		Data * myData = data;
		Control * myControl = this;
		double sliderVal = mySlider->value();

		//change bid ask prices:
		myData->SetPrevAskPrice(myData->GetAskPrice());
		myData->SetPrevBidPrice(myData->GetBidPrice());
		long differenceBidAsk;	//preserve bid ask spread
		differenceBidAsk = myData->GetAskPrice() - myData->GetBidPrice();
		myData->SetAskPrice((long)sliderVal + differenceBidAsk);
		myData->SetBidPrice((long)sliderVal);
		//do something:
		myControl->MainLoop();
	}
	if (btn == BtnPressed::PRINTBUT)
	{
		MainLoop();
		//printCurrentAll();

	}
	if (btn == BtnPressed::LIVEDATACONSOLEPRINTOUT) {

		PriceControlUI * myPriceControl = (PriceControlUI*)p;
		Data * myData = data;
		//PRINTOUT LIVE DATA IN THE CONSOLE:
		data->PrintoutDataInConsole();
	}
	if (btn == BtnPressed::CONNECTLIVEDATA) {

		PriceControlUI * myPriceControl = (PriceControlUI*)p;
		Data * myData = data;
		//ATTEMPT TO CONNECT TO TWS LIVE DATAFEED:
		data->ConnectLiveData();
	}
	if (btn == BtnPressed::STARTLOOP) {

		PriceControlUI * myPriceControl = (PriceControlUI*)p;
		Data * myData = data;
		cout << "\nControl Startloop called." << endl;
		//If Control mainloop is stopped, start it:
		if (!mainLoopActive) {
			startloop();
			//change the label of the button to "Stop Loop":
			myPriceControl->m_btnStartLoop->label("Stop Loop");
			return;
		}
		//If Control mainloop is running, stop it:
		if (mainLoopActive) {
			stoploop();
			//change the label of the button to "Start Loop":
			myPriceControl->m_btnStartLoop->label("Start Loop");
			return;
		}
	}
	if (btn == BtnPressed::EXPERIMENT) {
		cout << "Experiment called" << endl;
		if (userInterface != nullptr) {
			userInterface->m_window1->show();
			/*delete userInterface;
			userInterface = nullptr;*/
		}
	}
}

void Control::CallbkSmplTableWin(int rowPressed, int colPressed, long price, short windownumber)
{
	cout << "Callback received in Control" << " price: " << price << " windownumber: " << windownumber << endl;
}

void Control::startloop()
{
	//check to see if the loop is already running. if it is not, start the loop:
	if(!mainLoopActive){
		Fl::add_timeout(0.1, timeoutfunction, (void*) this);
		mainLoopActive = true;
		//and make sure the trigger to stop the loop inside timeoutfunction is off:
		stopMainLoop = false;
		//enable the live data feed - prices will be pulled from TWS:
		livedatafeed = true;
	}
	
}

void Control::stoploop()
{
	//if the loop is already set up to be stopped, do nothing:
	if (stopMainLoop) return;
	//if it is not set to be stopped, set the trigger to stop it inside the timeoutfunction:
	stopMainLoop = true;
	//and let the class know it is not running:
	mainLoopActive = false;
	//stop the livedatafeed:
	livedatafeed = false;
}


void Control::experimentConstructor()
{
}

//TODO: Erase this after finished experimenting
void Control::experimenting()
{


}

void Control::callbkControlInterface(int callback)
{
	cout << "Callback from Control Interface!!!!!!!" << endl;

	if (callback == 1) { 
		if (userInterface != nullptr) {userInterface->m_window1->show();}
	}
}


//Helpler functions for other classes:

//TODO:this is bad code. part of it needs to be moved into WidgetTable
void Control::rePriceWidTable(UserInterface * InterfaceToReprice)
{
	using namespace std;

	cout << "new rePriceWidTable called" << endl;

	UserInterface* pUI = InterfaceToReprice;
	
	//update prices shown in UserInterface:
	pUI->rePriceWidTable(data->GetBidPrice());

	//determine row which holds the price corresponding to current bid:
	int scrollposition = pUI->GetTable()->GetTopRowPrice() - data->GetBidPrice();
	//scroll the table to current bid with a 15 row offset:
	pUI->GetTable()->row_position(scrollposition - 15);

	//modify slider in PriceControlUI:
	//update the slider minimum and maximum settings:
	//setting initial Slider max/min values to that of bid/ask - offset of 95:

	int value, max, min;
	value = (int)data->GetBidPrice();
	min = (int)data->GetBidPrice() + 95 /* 3 offset for safety*/;
	max = (int)data->GetBidPrice() - 95 /* 3 offset for safety*/;

	m_pPriceControlUI->setSlider(value, max, min);
	//TODO: calling rePriceWidTable messes up the printout in WidgetTable - the index located now in WidgetTable::printPositions telling which rows to clear before printing fresh values - does not get cleared when rePriceWidTable is called. messes up the printout really bad
	InterfaceToReprice->GetTable()->widgetTableNeedsClearAll = true;


}

void Control::rePriceWidTable()

//Updates prices displayed in WidgetTable to between 100 above and below
//current bid price in Data class
//Updates slider in PriceControlUI to current Bid price
{
	UserInterface* pUI = userInterface;

//	WidgetTable * pTable = pUI->GetTable();

	//update prices shown in UserInterface:

	pUI->rePriceWidTable(data->GetBidPrice());

	
	//modify slider in PriceControlUI:
	//update the slider minimum and maximum settings:
	//setting initial Slider max/min values to that of bid/ask - offset of 95:

	int value, max, min;
	value = (int)data->GetBidPrice();
	min = (int)data->GetBidPrice() + 95 /* 3 offset for safety*/;
	max = (int)data->GetBidPrice() - 95 /* 3 offset for safety*/;

	m_pPriceControlUI->setSlider(value, max, min);

}

void ControlPrinter::printall()
{
	cout << "ControlPrinter printall function called" << endl;
	if (positions == NULL || table == NULL){ cout << "Null pointer! exiting!" << endl; return;}



}
