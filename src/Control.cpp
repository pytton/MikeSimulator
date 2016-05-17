#include "Control.h"
#include <iostream>
#include "MikeSimulator.h"
#include "Data.h"
#include "Display.h"
#include "WidgetTable.h"

using namespace std;

Control::Control(MikeSimulator * p)
{
	ptr_to_mikesimulator = p;
//	userInterface = new UserInterface(this, ptr_to_mikesimulator);
}

Control::Control(MikeSimulator * p, int starting_bid)
{
	ptr_to_mikesimulator = p;
	std::cout << "Control constructed. Starting bid: " << starting_bid << std::endl;
	userInterface = new UserInterface(this, /*p,*/ starting_bid);
	data = new Data(this, starting_bid);
}

void Control::MainLoop()
{
	//TODO: work on 1 and 2 first

	//1 check prices	-- this is done by manual up/down now

	//2 check fills
	//2a check/print current position, profit/loss, etc
	//3 make decisions	-- now just manual orders
	//4 display results/decisions
	printCurrentAll();
	//add other functions as needed
	//5 send orders		-- for algos - nothing now



}

void Control::printCurrentAll()
{
	Data * myData = data;
	//Display * myDisplay = ptr_to_mikesimulator->GetDisplay();

	long bid_price = myData->GetBidPrice();
	long ask_price = myData->GetAskPrice();


	//print current bid/ask prices inside UserInterface window1:
	userInterface->m_curr_bid->value((double)bid_price);
	userInterface->m_curr_ask->value((double)ask_price);

	//experimenting:
	using namespace std;


	int TopRowPrice = userInterface->GetTable()->GetTopRowPrice();
	//printing BID and ASK in WidgetTable:
	userInterface->GetTable()->printInTable(TopRowPrice - bid_price, 6, "BID");
	userInterface->GetTable()->printInTable(TopRowPrice - myData->GetPrevBidPrice(), 6, "");
	userInterface->GetTable()->printInTable(TopRowPrice - ask_price, 7, "ASK");
	userInterface->GetTable()->printInTable(TopRowPrice - myData->GetPrevAskPrice(), 7, "");

	//ROW POSITION:
	//determine row which holds the price corresponding to current bid:
	int scrollposition = userInterface->GetTable()->GetTopRowPrice() - myData->GetBidPrice();
	//scroll the table to current bid with a 15 row offset:
	userInterface->GetTable()->row_position(scrollposition - 15);
}

void Control::ManualOrder(int type, long price) 
{
	using namespace std;

	cout << "\n Manual Order Entered!\n";
	cout << "Price: " << price << "\n Order Type: " << type;

	//enter new order into Data:
//	ptr_to_mikesimulator->GetData()->GetMikeOrder()->NewOrder(type, price);
	//printout the new order in WidgetTable:
//	ptr_to_mikesimulator->GetData()->GetMikeOrder()->PrintOrder();

}

//CALLBACKS FROM USERINTERFACE HANDLED HERE:
//btn chooses what to do, UserInterface *p
//provides the data, parameters optional
void Control::CallbkUserInt(UserInterface * p, BtnPressed btn,
	int parameter1,	int parameter2,	double parameter3)
{
	if (btn == UPBTN)
	{
		cout << "enum type callback called" << endl;
		UserInterface * myUserInt = (UserInterface*)p;
		Data * myData = data;
		//change bid ask prices:
		myData->SetPrevAskPrice(myData->GetAskPrice());
		myData->SetPrevBidPrice(myData->GetBidPrice());
		myData->SetAskPrice(myData->GetAskPrice() + 1);
		myData->SetBidPrice(myData->GetBidPrice() + 1);
		//update slider value:
		myUserInt->Getm_slider1()->value((double)myData->GetBidPrice());
		//do something:
		//MainLoop() crashes due to bad pointers - has to be fixed
		this->MainLoop();

	}
	if (btn == DOWNBTN) {
		//REFACTORING COMPLETE!
		cout << "refactored  m_down_btn_cb called" << endl;
		UserInterface * myUserInt = (UserInterface*)p;
		Data * myData = data;
		//change bid ask prices:
		myData->SetPrevAskPrice(myData->GetAskPrice());
		myData->SetPrevBidPrice(myData->GetBidPrice());
		myData->SetAskPrice(myData->GetAskPrice() - 1);
		myData->SetBidPrice(myData->GetBidPrice() - 1);
		//update slider value:
		myUserInt->Getm_slider1()->value((double)myData->GetBidPrice());
		//do something:
		this->MainLoop();
	}
	if (btn == SLIDER1)
	{
		UserInterface * myUserInt = (UserInterface*)p;
		Fl_Value_Slider * mySlider = myUserInt->Getm_slider1();
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
	if (btn == EXTRABTN)
	{
		cout << "Extra button pressed - implement this!!!!" << endl;
		rePriceWidTable();
	}
}

void Control::CallbkWidTable(){
	std::cout << "\ncbkOne called" << std::endl;
	
	//below copied from WidgeTable - has to be refactored:
	/*
	//this callback is set inside the WidgetTable::SetSize function!!
	My_fl_button * myButton = (My_fl_button*)w;		//myButton is the button that was pressed
	WidgetTable * thisTable = (WidgetTable*)p;		//thisTable is the table in which the button was pressed
	UserInterface * myUI = thisTable->GetUserInterface();	//myUI is the UserInterface in which the table is created
	MikeSimulator * mySimulator = myUI->GetMikeSim();

	mySimulator->GetControl()->CallbkWidTable();
	//send the information to Control:
	//What price level was pressed?:
	int rowPressed = myButton->y_pos;		//this is the row in which the button was pressed
	long price = thisTable->PriceOfRow(rowPressed);
	int OrderType = myButton->x_pos;
	mySimulator->GetControl()->ManualOrder(OrderType, price);
	*/
}

//Helpler functions for other classes:

void Control::rePriceWidTable()
//UNDER CONSTRUCTION
//Updates prices displayed in WidgetTable to between 100 above and below
//current bid price in Data class
//Updates slider in UserInterface to current Bid price
{
	UserInterface* pUI = userInterface;

	WidgetTable * pTable = pUI->GetTable();

	//BELOW CODE SET NEW SIZE OF WIDGETTABLE:

	//pTable->clear();
	//this commented out because not sure if old table gets destroyed and worried
	//about memory leak.
	//leaving this commented out leaves old BID/ASK still printed - could fix this

	//first - make sure that the TopRowPrice is set to 100 above current bid price:
	//Data * myData = mikesimulator->GetData();
	pTable->SetTopRowPrice(data->GetBidPrice() + 100);
	//draw the new widget table:
	//pTable->SetSize(pTable->GetRows(), pTable->GetCols(), pTable);	//this needs to be called to construct all the cells of WidgetTable																					
	//pUI->SetTable(pTable);
	pUI->m_window1->hide();
	pUI->m_window1->redraw();
	pUI->m_window1->show();

	//populate price column with prices:
	pUI->GetTable()->PopPriceCol(/*mikesimulator->GetDisplay()->GetWindow()->GetTable()*/);
	//modify slider in UserInterface:
	//update the slider minimum and maximum settings:
	//setting initial Slider max/min values to that of bid/ask - offset:
	pUI->m_slider1->minimum((double)data->GetBidPrice() + ((pTable->GetRows()) / 2) - 3 /* 3 offset for safety*/);
	pUI->m_slider1->maximum((double)data->GetBidPrice() - ((pTable->GetRows()) / 2) + 3 /* 3 offset for safety*/);
	pUI->m_slider1->value((double)data->GetBidPrice());
}





//std::stringstream buffer;
//buffer << bid_price;
//std::cout << buffer.str();
//buffer.str("newstring");
//std::cout << buffer.str();
//std::cout << "\nPrintCurrent All";
//buffer.str("");
//buffer << bid_price;

//	cout << "\nget prices/check fills/make decisions/send orders/print results" << endl;
//	cout << " " << myDisplay->GetUInterface()->m_slider1->value();
//	string myString;
//	myString = "BID";
//myString + bid_price;
//myString.append();
//	const char * ch = myString.c_str();
//	cout << ch[233];	//HACK	- this should not have worked :D

