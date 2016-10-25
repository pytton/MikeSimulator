#include "Control.h"

#include <iostream>

#include "UserInterface.h"
#include "MikeSimulator.h"
#include "Data.h"
#include "WidgetTable.h"
#include "MikeEnums.h"

#include "PriceControlUI.h"
#include "ManualInterface.h"
#include "MikePositionsOrders.h"

using namespace std;

//Control::Control(MikeSimulator * p)
//{
//	ptr_to_mikesimulator = p;
////	userInterface = new UserInterface(this, ptr_to_mikesimulator);
//}

Control::Control(MikeSimulator * p, int starting_bid)
{
	ptr_to_mikesimulator = p;
	std::cout << "Control constructed. Starting bid: " << starting_bid << std::endl;

	userInterface = new ManualInterface(this, /*p,*/ starting_bid);
//	userInterface = new UserInterface(this, /*p,*/ starting_bid);
	
	data = new Data(this, starting_bid);
	m_pPriceControlUI = new PriceControlUI(this, starting_bid);
	
	
	manualPositions = new MikePositionOrders("Manual", 1000000);
	rePriceWidTable(userInterface);
}

void Control::MainLoop()
{
	//TODO: work on 1 and 2 first

	//1 check prices	-- this is done by manual up/down now

	//2 check fills

	manualPositions->checkFills(data->GetBidPrice(), data->GetAskPrice());
	manualPositions->updateOpenOrdersByPrice();
	//manualPositions->printoutActivePositions(data->GetBidPrice(), data->GetAskPrice());
	//2a check/print current position, profit/loss, etc
	//3 make decisions	-- now just manual orders
	//4 display results/decisions

	
		printCurrentAll();
	
	
	
	//add other functions as needed
	//5 send orders		-- for algos - nothing now
	userInterface->PrintBidAsk(data->GetBidPrice(), data->GetAskPrice());

	//printCurrentAll();

}

void Control::printCurrentAll()
{
	Data * myData = data;
	UserInterface * myInterface = userInterface;
	MikePositionOrders * myPositionOrders = manualPositions;

//	const std::vector<MikePosition> *constPositions = myPositionOrders->GetMikePositions();

//	const std::vector<MikeOrdersAtPrice> *ordersAtPrice = myPositionOrders->GetOpOrdersbyPrice();

	long 
		totalOpenPos,
		totalOpenPL,
		totalClosedPL,
		totalPL,
		askPrice,
		bidPrice;

	//askPrice = myData->GetAskPrice();
	//bidPrice = myData->GetBidPrice();
	//totalOpenPos = myPositionOrders->TotalOpenPos();
	//totalOpenPL = myPositionOrders->AllOpenPL(bidPrice, askPrice);
	//totalClosedPL = myPositionOrders->AllClosedPL(bidPrice, askPrice);
	//totalPL = myPositionOrders->AllTotalPL(bidPrice, askPrice);



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



//CALLBACKS 

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

void Control::CallbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed)
{
	using namespace std;

	//send order to OrderBook
	//finish this so that the amount of order is passed through
	manualPositions->newOrder(OrderTypePressed, price,100);
	manualPositions->checkFills(data->GetBidPrice(), data->GetAskPrice());
	printCurrentAll();
	

}
//PRICECONTROLUI
void Control::CallbkPriceControlUI(PriceControlUI * p, BtnPressed btn, Fl_Widget * widgetPressed, int parameter1, int parameter2, double parameter3)
{
	if (btn == UPBTN)
	{
		//REFACTOR THIS:

		//cout << "enum type callback called" << endl;
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
		
		printCurrentAll();

	}

}

//Helpler functions for other classes:


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

