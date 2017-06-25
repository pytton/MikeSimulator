#include "Control.h"

#include <iostream>

#include "UserInterface.h"
#include "MikeSimulator.h"
#include "Data.h"
#include "WidgetTable.h"
#include "MikeEnums.h"
#include "MikeTimer.h"

#include "PriceControlUI.h"
#include "SimpleTableWindow.h"
#include "ManualInterface.h"
#include "MikePositionsOrders.h"

#include "PosOrders.h"

/////////////////////////////////
//erase after testing:
#include "PositionBook.h"
class PositionBook;
/////////////////////////////////
using namespace std;

Control::Control(Simulator * p, int starting_bid)
{
	ptr_to_mikesimulator = p;
	std::cout << "Control constructed. Starting bid: " << starting_bid << std::endl;

//	userInterface = new ManualInterface(this, /*p,*/ starting_bid);
//	userInterface = new UserInterface(this, /*p,*/ starting_bid);
	
	data = new Data(this, starting_bid);
	m_pPriceControlUI = new PriceControlUI(this, starting_bid);
	
	simpleTableWindow = new SimpleTableWindow(this, 0 );

	manualPositions = new MikePositionOrders("Manual", 1000000);
	rePriceWidTable(userInterface);
	
	//setting up previous static variables in Control::timeoutfunction(void*p)
	timer.reset();
	resetTimer = true;
	previouselapsedtime = 0;
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
	using namespace std;
	mainLoopfinished = false;//to ensure that the timeoutfunction does not call it again while it is executing
	
//	cout << "\nMainLoop Called. " << endl;
							 
	//TODO: work on 1 and 2 first
	//1 check prices	-- this is done by manual up/down now
	int tickerId = 3;//1-EUR, 2-GBP, 3-SPY, 4-DIA, 5-IWM, 6-QQQ
	if (livedatafeed) data->updateLiveData(tickerId);
	//2 check fills

	manualPositions->checkFills(data->GetBidPrice(), data->GetAskPrice());
	manualPositions->updateOpenOrdersByPrice();

	
	printCurrentAll();
	

	userInterface->PrintBidAsk(data->GetBidPrice(), data->GetAskPrice());


	mainLoopfinished = true;//to ensure that the timeoutfunction does not call it again while it is executing
}

void Control::printCurrentAll()
{
	//Data * myData = data;
	//UserInterface * myInterface = userInterface;
	//MikePositionOrders * myPositionOrders = manualPositions;

	//const MikePosVect *constPositions = myPositionOrders->GetMikePositions();

	//const std::vector<MikeOrdersAtPrice> *ordersAtPrice = myPositionOrders->GetOpOrdersbyPrice();

	//long 
	//	totalOpenPos,
	//	totalOpenPL,
	//	totalClosedPL,
	//	totalPL,
	//	askPrice,
	//	bidPrice;

	//askPrice = myData->GetAskPrice();
	//bidPrice = myData->GetBidPrice();

	//totalOpenPos = myPositionOrders->CalcTotalOpenPos();
	//totalOpenPL = myPositionOrders->CalcAllOpenPL(bidPrice, askPrice);
	//totalClosedPL = myPositionOrders->CalcAllClosedPL(bidPrice, askPrice);
	//totalPL = myPositionOrders->CalcAllTotalPL(bidPrice, askPrice);

	//myInterface->PrintAll(
	//	totalOpenPos,
	//	totalOpenPL,
	//	totalClosedPL,
	//	totalPL,
	//	askPrice,
	//	bidPrice,
	//	constPositions,
	//	ordersAtPrice
	//	);

}

void Control::startloop()
{
	//check to see if the loop is already running. if it is not, start the loop:
	if (!mainLoopActive) {
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
void Control::CallbkUserInt(UserInterface * p, BtnPressed btn,
	long parameter1,	long parameter2,	double parameter3)
{

	if (btn == EXTRABTN)
	{
		cout << "Extra button pressed - implement this!!!!" << endl;
		rePriceWidTable(p);
	}
	if (btn == PRINTORDERSBTN)
	{

		cout << "manualPositions->printoutAllOrders();" << endl;
	//	manualOrders->printoutAllOrders();
		//TODO: Print orders in WidgetTable
	}
	if (btn == CHECKFILLS)
	{
		long bidPrice, askPrice;
		bidPrice = data->GetBidPrice();
		askPrice = data->GetAskPrice();

		manualPositions->checkFills(bidPrice, askPrice);
	}
	if (btn == PRINTPOS)
	{
		long bidprice = data->GetBidPrice();
		long askprice = data->GetAskPrice();
		manualPositions->printoutActivePositions(bidprice, askprice);
	}
}
//WIDGETTABLE:

void Control::CallbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed, int orderSize) {
	using namespace std;

	//send order to OrderBook if order type is not 'cancel order':	
	if (OrderTypePressed != CXLORDER) { manualPositions->newOrder(OrderTypePressed, price, orderSize); }
	if (OrderTypePressed == CXLORDER) { manualPositions->cancelAllOrdAtPrice(price); }
	//check for fills:
	manualPositions->checkFills(data->GetBidPrice(), data->GetAskPrice());
	MainLoop();
	//printCurrentAll();
}
//PRICECONTROLUI
void Control::CallbkPriceControlUI(PriceControlUI * p, BtnPressed btn, Fl_Widget * widgetPressed, int parameter1, int parameter2, double parameter3)
{
	if (btn == UPBTN)
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
	if (btn == DOWNBTN) {
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
	if (btn == SLIDER1)
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
	if (btn == PRINTBUT)
	{
		MainLoop();
		//printCurrentAll();

	}
	if (btn == LIVEDATACONSOLEPRINTOUT) {

		PriceControlUI * myPriceControl = (PriceControlUI*)p;
		Data * myData = data;
		//PRINTOUT LIVE DATA IN THE CONSOLE:
		data->PrintoutDataInConsole();
	}
	if (btn == CONNECTLIVEDATA) {

		PriceControlUI * myPriceControl = (PriceControlUI*)p;
		Data * myData = data;
		//ATTEMPT TO CONNECT TO TWS LIVE DATAFEED:
		data->ConnectLiveData();
	}
	if (btn == STARTLOOP) {

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
}

void Control::CallbkSmplTableWin(int rowPressed, int colPressed, long price, short windownumber)
{
	cout << "Callback received in Control" << " price: " << price << " windownumber: " << windownumber << endl;
}
