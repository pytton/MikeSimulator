//                            _____         _                 __                    
//   /\ /\  ___   ___  _ __   \_   \ _ __  | |_   ___  _ __  / _|  __ _   ___   ___ 
//  / / \ \/ __| / _ \| '__|   / /\/| '_ \ | __| / _ \| '__|| |_  / _` | / __| / _ \
//  \ \_/ /\__ \|  __/| |   /\/ /_  | | | || |_ |  __/| |   |  _|| (_| || (__ |  __/
//   \___/ |___/ \___||_|   \____/  |_| |_| \__| \___||_|   |_|   \__,_| \___| \___|
//                                                                                  
#include <sstream> //replaces cout
#include "UserInterface.h"
#include "MikeSimulator.h"
#include "WidgetTable.h"
//#include "MikeTimer.h"
#include "MikeEnums.h"
#include "Control.h"

//USERINTERFACE:

UserInterface::UserInterface(
	Control * control, 	 
	double starting_bid_price/*700*/,
	int numberOfColumns/*15*/,
	int numberOfButtoncolumns/*5*/)	//constructor

{
	using namespace std;
	m_pControl = control;
	bid_price = starting_bid_price;
	//add remove elements below:
	m_window1->begin();

	//******************************************************************************************
	//creating WidgetTable:
	delete m_table;	//deleting old table supplied by fluid
	
	//name the column headers and button names in WidgetTable:
	SetColButNames(col_names, button_names);
	//construct new WidgetTable:
	int top_row_price = bid_price +100, 
		number_rows = 200, 
		number_cols = numberOfColumns,
		how_many_cols_are_buttons = numberOfButtoncolumns;
	
	m_pTable = new WidgetTable(5, 5, 940, 630, "widgettable", this, top_row_price, number_rows,
		number_cols, how_many_cols_are_buttons, col_names, button_names);


	m_window1->end();
	//******************************************************************************************

	//******************
	//SETTING CALLBACKS:
	//******************

	m_btn_extra->callback(m_extra_btn_cb, (void*) this);	//this changes size of Widgettable
	m_btn_printOrders->callback(m_printOrders_btn_cb, (void*) this);
	m_btn_checkFills->callback(m_checkFills_btn_cb, (void*) this);
	m_btn_printPos->callback(m_printPos_btn_cb, (void*) this);
	m_btn_resetOrdSize->callback(m_resetOrderSize_cb, (void*) this);

	m_order_size->value(100);



//	m_pTable->PopPriceCol();
	m_window1->hide();
	m_window1->redraw();
	m_window1->show();

}
void UserInterface::SetColButNames(std::vector <std::string> &col_names, std::vector <std::string> &button_names)
{
	using namespace std;
	cout << "UserInterface SetColButNames called" << endl;

	col_names.clear();

	col_names.push_back("CANCEL\nORDER");
	col_names.push_back("BUY");
	col_names.push_back("BUY");
	col_names.push_back("SELL");
	col_names.push_back("SELL");
	col_names.push_back("PRICE");
	col_names.push_back("BID");
	col_names.push_back("ASK");
	col_names.push_back("B LMT\nSIZE");
	col_names.push_back("B STP\nSIZE");
	col_names.push_back("S LMT\nSIZE");
	col_names.push_back("S STP\nSIZE");
	col_names.push_back("OPEN\nPOSITION");
	col_names.push_back("OPEN\nP/L");
	col_names.push_back("CLOSED\nP/L");
	col_names.push_back("TOTAL\nP/L");

	button_names.clear();

	button_names.push_back("CXL");
	button_names.push_back("B LMT");
	button_names.push_back("B STP");
	button_names.push_back("S LMT");
	button_names.push_back("S STP");
}
void UserInterface::show()
{
	m_window1->show();
//	m_window2->show();
}

void UserInterface::rePriceWidTable(long bidprice)
//UNDER CONSTRUCTION
//Updates prices displayed in WidgetTable to between 100 above and below
//current bid price in Data class
//Updates slider in UserInterface to current Bid price
{
	UserInterface* pUI = this;
	WidgetTable * pTable = pUI->GetTable();

	//make sure that the TopRowPrice is set to 100 above current bid price:	
	pTable->SetTopRowPrice(bidprice + 100);

	//redraw the new widget table:								
	pUI->m_window1->hide();
	pUI->m_window1->redraw();
	pUI->m_window1->show();

	//populate price column with prices:
	//clear the bid and ask columns
	pUI->GetTable()->ClearColumn(pTable->GetBidCol());	
	pUI->GetTable()->ClearColumn(pTable->GetAskCol());
	//print price
	pUI->GetTable()->PopPriceCol();
}


//CALLBACKS:
//                _  _  _                   _            
//    ___   __ _ | || || |__    __ _   ___ | | __ ___  _ 
//   / __| / _` || || || '_ \  / _` | / __|| |/ // __|(_)
//  | (__ | (_| || || || |_) || (_| || (__ |   < \__ \ _ 
//   \___| \__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)
//                                                       


void UserInterface::m_printOrders_btn_cb(Fl_Widget * w, void * p)
{
	UserInterface * myUserInt = (UserInterface*)p;
	myUserInt->m_pControl->CallbkUserInt(myUserInt, PRINTORDERSBTN);

}
void UserInterface::m_checkFills_btn_cb(Fl_Widget * w, void * p)
{
	UserInterface * myUserInt = (UserInterface*)p;
	myUserInt->m_pControl->CallbkUserInt(myUserInt, CHECKFILLS);
}
void UserInterface::m_printPos_btn_cb(Fl_Widget * w, void * p)
{
	UserInterface * myUserInt = (UserInterface*)p;
	myUserInt->m_pControl->CallbkUserInt(myUserInt, PRINTPOS);
}
void UserInterface::m_resetOrderSize_cb(Fl_Widget * w, void * p)
{
	UserInterface * myUserInt = (UserInterface*)p;
	myUserInt->m_order_size->value(100);
}

void UserInterface::m_extra_btn_cb(Fl_Widget *w, void * p)
{
	UserInterface * myUserInt = (UserInterface*)p;
	myUserInt->m_pControl->CallbkUserInt(myUserInt, EXTRABTN);
}

//WidgetTable callback:
//THIS IS WHERE THE ORDER TYPE IS DETERMINED
//BASED ON WHICH COLUMN HAS BEEN PRESSED IN WIDGETTABLE
void UserInterface::CallbkWidTable(int rowPressed, int colPressed, long price)
{
	//FIRST DETERMINE WHAT THE BUTTON PRESSED IN WIDGETTABLE WILL DO:
	//Currently:
	//col 0 = cxl, 1 = buylmt, 2 = buystp, 3 = selllmt, 4 =  sellstp
	MikeOrderType tempOrderType;
	bool checkForValidOrderType = 1;
	switch (colPressed)
	{
	case 0:
		tempOrderType = CXLORDER;
		break;
	case 1:
		tempOrderType = BUYLMT;
		break;
	case 2:
		tempOrderType = BUYSTP;
		break;
	case 3:
		tempOrderType = SELLLMT;
		break;
	case 4:
		tempOrderType = SELLSTP;
		break;

	default:
		checkForValidOrderType = 0;
	}

	using namespace std;
	cout << "\ndebugging UserInterface::CallbkWidTable. Order type: " << tempOrderType << endl;

	if (checkForValidOrderType)
	{
		int orderSize = (int)m_order_size->value();//get the value of the order from Fl_Input which is part of UserInterface
		GetControl()->CallbkWidTable(rowPressed, colPressed, price, tempOrderType, orderSize);
	}
	else std::cout << "Unhandled type of button pressed!!!" << std::endl;

}

void UserInterface::PrintBidAsk(long bid, long ask)
{
	//first, check if bid price is within the range now displayed by WidgetTable:

	if (bid < GetTable()->GetTopRowPrice() && bid > GetTable()->GetTopRowPrice()- GetTable()->GetRows())
	{
		//erase everything in the BID column (so that previous bid does not show):
		GetTable()->ClearColumn(GetTable()->GetBidCol());
		//print "BID" in at the correct price:
		int row = GetTable()->RowOfPrice(bid);
		int col = GetTable()->GetBidCol();
		GetTable()->printInTable(row, col, "BID");
	}
	else {
		std::cout << "\n BID OUTSIDE OF WIDGETTABLE" << std::endl;
	}
	//do the same for ask:
	if (ask < GetTable()->GetTopRowPrice() && ask > GetTable()->GetTopRowPrice() - GetTable()->GetRows())
	{
		//erase everything in the ASK column (so that previous bid does not show):
		GetTable()->ClearColumn(GetTable()->GetAskCol());
		//print "ASK" in at the correct price:
		int row = GetTable()->RowOfPrice(ask);
		int col = GetTable()->GetAskCol();
		GetTable()->printInTable(row, col, "ASK");
	}
	else {std::cout << "\n ASK OUTSIDE OF WIDGETTABLE" << std::endl;}
}


void UserInterface::PrintAll(
	long totalOpenPos, 
	long totalOpenPL, 
	long totalClosedPL, 
	long totalPL, 
	long askPrice, 
	long bidPrice,
	const std::vector <MikePosition> *openPositions,
	const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice)
{
	using namespace std;
	Timer timer;
	timer.reset();
	char  buffer[21];

	snprintf(buffer, 20, "%d", totalOpenPos);
	m_TotOpenPos->value(buffer);

	snprintf(buffer, 20, "%d", totalOpenPL);
	m_TotOpenPL->value(buffer);

	snprintf(buffer, 20, "%d", totalClosedPL);
	m_TotClosedPL->value(buffer);

	snprintf(buffer, 20, "%d", totalPL);
	m_TotPL->value(buffer);

	snprintf(buffer, 20, "%d", askPrice);


	m_curr_ask->value(askPrice);
	m_curr_bid->value(bidPrice);

	GetTable()->printPositions(openPositions, openOrdersAtPrice);
}