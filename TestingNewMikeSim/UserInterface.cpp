#include <sstream> //replaces cout
#include "UserInterface.h"
#include "MikeSimulator.h"
#include "WidgetTable.h"
//#include "MikeTimer.h"
#include "MikeEnums.h"
#include "Control.h"

#define MIKE_COMMENTSON true


//            _____         _                __                      ___                      
//   /\ /\    \_   \ _ __  | |_  ___  _ __  / _|  __ _   ___  ___   / __\  __ _  ___   ___  _ 
//  / / \ \    / /\/| '_ \ | __|/ _ \| '__|| |_  / _` | / __|/ _ \ /__\// / _` |/ __| / _ \(_)
//  \ \_/ / /\/ /_  | | | || |_|  __/| |   |  _|| (_| || (__|  __// \/  \| (_| |\__ \|  __/ _ 
//   \___/  \____/  |_| |_| \__|\___||_|   |_|   \__,_| \___|\___|\_____/ \__,_||___/ \___|(_)
//                                                                                            


UserInterfaceBase::UserInterfaceBase()
{

	using namespace std;
	m_pControl = NULL;
	
	//add remove elements below:
	m_window1->begin();

	////******************************************************************************************
	////creating WidgetTable:
	if (NULL != m_table) {
		delete m_table; m_table = NULL;
	}	//deleting old table supplied by fluid

					//name the column headers and button names in WidgetTable:
	//SetColButNames(col_names, button_names);
	//construct new WidgetTable:
	//int top_row_price = bid_price + 100,
	//	number_rows = 20,
	//	number_cols = 28,
	//	how_many_cols_are_buttons = 5;

	//m_pTable = new WidgetTable(5, 5, 940, 630, "Base Table", this, top_row_price, number_rows,
	//	number_cols, how_many_cols_are_buttons, col_names, button_names);


	m_window1->end();
	//******************************************************************************************



	/////////////////////////////////////////////

	//******************
	//SETTING CALLBACKS:
	//******************

	m_btn_extra->callback(m_extra_btn_cb, (void*) this);	//this changes size of Widgettable
	m_btn_printOrders->callback(m_printOrders_btn_cb, (void*) this);
	m_btn_checkFills->callback(m_checkFills_btn_cb, (void*) this);
	m_btn_printPos->callback(m_printPos_btn_cb, (void*) this);
	m_btn_resetOrdSize->callback(m_resetOrderSize_cb, (void*) this);
	m_btn_CancelAllOrders->callback(m_btn_CancelAllOrders_cb, (void*) this);
	m_btn_ClearPositions->callback(m_btn_ClearPostions, (void*) this);

	m_order_size->value(100);



	//	m_pTable->PopPriceCol();
	m_window1->hide();
	m_window1->redraw();
	m_window1->show();
}

void UserInterfaceBase::SetColButNames(std::vector <std::string> &col_names, std::vector <std::string> &button_names)
{
	using namespace std;
	cout << "UserInterface SetColButNames called" << endl;

	col_names.clear();

	col_names.push_back("CANCEL\nORDER");
	col_names.push_back("BUY\nLIMIT");
	col_names.push_back("BUY\nSTOP");
	col_names.push_back("SELL\nLIMIT");
	col_names.push_back("SELL\nSTOP");
	col_names.push_back("AVERAGE\nPRICE");
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
	col_names.push_back("ZERO P/L\nPOINT");


	button_names.clear();

	button_names.push_back("CXL");
	button_names.push_back("B LMT");
	button_names.push_back("B STP");
	button_names.push_back("S LMT");
	button_names.push_back("S STP");
}

void UserInterfaceBase::changename(std::string name)
{

	const char * newname = name.c_str();
	m_window1->label(newname);
	m_window1->redraw_label();
	m_window1->show();

}

void UserInterfaceBase::rePriceWidTable(long bidprice)
//UNDER CONSTRUCTION
//Updates prices displayed in WidgetTable to between 100 above and below
//current bid price in Data class
//Updates slider in UserInterface to current Bid price
{
	UserInterfaceBase* pUI = this;
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

//void UserInterfaceBase::callbkUserInterface(BtnPressed)
//{
//	std::cout << "UserInterfaceBase::callbkUserInterface callback" << std::endl;
//}

//this is internal callback:
void UserInterfaceBase::m_resetOrderSize_cb(Fl_Widget * w, void * p)
{
	UserInterfaceBase * myUserInt = (UserInterfaceBase*)p;
	myUserInt->m_order_size->value(100);
}

//below static callbacks link to outside of this class using virtual function callbkUserInterface:
void UserInterfaceBase::m_printOrders_btn_cb(Fl_Widget * w, void * p)
{
	UserInterfaceBase * myUserInt = (UserInterfaceBase*)p;
//	if (myUserInt->m_pControl == NULL) { std::cout << "void pointer!" << std::endl; return; }
	myUserInt->callbkUserInterface(BtnPressed::PRINTORDERSBTN);
}
void UserInterfaceBase::m_checkFills_btn_cb(Fl_Widget * w, void * p)
{
	UserInterfaceBase * myUserInt = (UserInterfaceBase*)p;
//	if (myUserInt->m_pControl == NULL) { std::cout << "void pointer!" << std::endl; return; }
	myUserInt->callbkUserInterface(BtnPressed::CHECKFILLS);
}
void UserInterfaceBase::m_printPos_btn_cb(Fl_Widget * w, void * p)
{
	UserInterfaceBase * myUserInt = (UserInterfaceBase*)p;
//	if (myUserInt->m_pControl == NULL) { std::cout << "void pointer!" << std::endl; return; }
	myUserInt->callbkUserInterface(BtnPressed::PRINTPOS);
}
void UserInterfaceBase::m_btn_CancelAllOrders_cb(Fl_Widget * w, void * p)
{
	UserInterfaceBase * myUserInt = (UserInterfaceBase*)p;
//	if (myUserInt->m_pControl == NULL) { std::cout << "void pointer!" << std::endl; return; }
	myUserInt->callbkUserInterface(BtnPressed::CANCELALLORDERS);
}
void UserInterfaceBase::m_btn_ClearPostions(Fl_Widget * w, void * p)
{
	UserInterfaceBase * myUserInt = (UserInterfaceBase*)p;
//	if (myUserInt->m_pControl == NULL) { std::cout << "void pointer!" << std::endl; return; }
	myUserInt->callbkUserInterface(BtnPressed::CLEARALLPOSITIONS);
}
void UserInterfaceBase::m_extra_btn_cb(Fl_Widget *w, void * p)
{
	UserInterfaceBase * myUserInt = (UserInterfaceBase*)p;
//	if (myUserInt->m_pControl == NULL) { std::cout << "void pointer!" << std::endl; return; }
	myUserInt->callbkUserInterface(BtnPressed::EXTRABTN);
}

//   __    __  _      _               _    _____         _      _       
//  / / /\ \ \(_)  __| |  __ _   ___ | |_ /__   \  __ _ | |__  | |  ___ 
//  \ \/  \/ /| | / _` | / _` | / _ \| __|  / /\/ / _` || '_ \ | | / _ \
//   \  /\  / | || (_| || (_| ||  __/| |_  / /   | (_| || |_) || ||  __/
//    \/  \/  |_| \__,_| \__, | \___| \__| \/     \__,_||_.__/ |_| \___|
//                       |___/                                          
//     ___         _  _  _                   _                          
//    / __\  __ _ | || || |__    __ _   ___ | | __ _                    
//   / /    / _` || || || '_ \  / _` | / __|| |/ /(_)                   
//  / /___ | (_| || || || |_) || (_| || (__ |   <  _                    
//  \____/  \__,_||_||_||_.__/  \__,_| \___||_|\_\(_)                   
//                                                                      

//WidgetTable callback:
//THIS IS WHERE THE ORDER TYPE IS DETERMINED
//BASED ON WHICH COLUMN HAS BEEN PRESSED IN WIDGETTABLE
void UserInterfaceBase::callbkWidTable(int rowPressed, int colPressed, long price)
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
	if (MIKE_COMMENTSON) cout << "\nUserInterfaceBase::callbkWidTable called. Order type: " << tempOrderType << endl;

	if (!checkForValidOrderType) {
		std::cout << "Unhandled type of button pressed!!!" << std::endl;
		return;
	}

	//get the value of the order from Fl_Input which is part of UserInterfaceBase
	int orderSize = (int)m_order_size->value();

	//send callback to virtual function implemented in derived classes:
	sendWidTableCallback(rowPressed, colPressed, price, tempOrderType, orderSize);
}

void UserInterfaceBase::PrintBidAsk(long bid, long ask)
{
	//first, check if bid price is within the range now displayed by WidgetTable:

	if (bid < GetTable()->GetTopRowPrice() && bid > GetTable()->GetTopRowPrice() - GetTable()->GetRows())
	{
		//erase everything in the BID column (so that previous bid does not show):
		GetTable()->ClearColumn(GetTable()->GetBidCol());
		//print "BID" in at the correct price:
		int row = GetTable()->RowOfPrice(bid);
		int col = GetTable()->GetBidCol();
		GetTable()->printInTable(row, col, "BID", FL_BLUE);
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
		GetTable()->printInTable(row, col, "ASK", FL_RED);
	}
	else { std::cout << "\n ASK OUTSIDE OF WIDGETTABLE" << std::endl; }
}

void UserInterfaceBase::PrintAll(
	long totalOpenPos,
	long totalOpenPL,
	long totalClosedPL,
	long totalPL,
	long askPrice,
	long bidPrice,
	const std::vector <MikePosition> *openPositions,
	const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice,
	double averagePrice
)
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

	snprintf(buffer, 20, "%f", averagePrice);
	m_AvgPosPrice->value(buffer);

	m_curr_ask->value(askPrice);
	m_curr_bid->value(bidPrice);

	//pring positions and orders in Table:
	WidgetTable * table = GetTable();
	table->printPositions(openPositions, openOrdersAtPrice);

	//print average price in Table:
	table->ClearColumn(table->avgPriceCol);
	if (averagePrice) {
		snprintf(buffer, 20, "%.0f", averagePrice);
		int rowToPrintIn = 0;
		rowToPrintIn = table->RowOfPrice((long)averagePrice);
		Fl_Color color = FL_WHITE;
		Fl_Color textColor = FL_YELLOW;
		if (totalOpenPos >= 0) color = FL_DARK_BLUE;
		else color = FL_RED;
		table->printInTable(rowToPrintIn, table->avgPriceCol, buffer, color, textColor);
	}
}


//                         _____         _                __                      
//   /\ /\  ___   ___  _ __\_   \ _ __  | |_  ___  _ __  / _|  __ _   ___  ___  _ 
//  / / \ \/ __| / _ \| '__|/ /\/| '_ \ | __|/ _ \| '__|| |_  / _` | / __|/ _ \(_)
//  \ \_/ /\__ \|  __/| |/\/ /_  | | | || |_|  __/| |   |  _|| (_| || (__|  __/ _ 
//   \___/ |___/ \___||_|\____/  |_| |_| \__|\___||_|   |_|   \__,_| \___|\___|(_)
//                                                                                
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

	if (NULL != m_table) delete m_table;	//deleting old table supplied by fluid
//	delete m_table;	//deleting old table supplied by fluid

					//name the column headers and button names in WidgetTable:
	SetColButNames(col_names, button_names);
	//construct new WidgetTable:
	int top_row_price = bid_price + 100,
		number_rows = 200,
		number_cols = numberOfColumns,
		how_many_cols_are_buttons = numberOfButtoncolumns;

	m_pTable = new WidgetTable(5, 5, 940, 630, "widgettable", this, top_row_price, number_rows,
		number_cols, how_many_cols_are_buttons, col_names, button_names);


	m_window1->end();
	//******************************************************************************************

	m_window1->hide();
	m_window1->redraw();
	m_window1->show();

}

//static callbacks go to this virtual callback:
void UserInterface::sendWidTableCallback(int rowPressed, int colPressed, long price, MikeOrderType tempOrderType, int orderSize)
{
	using namespace std;
	if (MIKE_COMMENTSON) { cout << "UserInterface::sendWidTableCallback called." << endl; }
	if (GetControl() == NULL) { cout << "Void Pointer in UserInterface::callbkWidTable" << endl; return; }
	GetControl()->callbkWidTable(rowPressed, colPressed, price, tempOrderType, orderSize);
}


void UserInterface::callbkUserInterface(BtnPressed button)
{
	std::cout << "UserInterface callback" << std::endl;
	if (m_pControl == NULL) { std::cout << "void pointer!" << std::endl; return; }
	m_pControl->CallbkUserInt(this, button);
}


//                         _____         _                __                      __  _         _              _ 
//   /\ /\  ___   ___  _ __\_   \ _ __  | |_  ___  _ __  / _|  __ _   ___  ___   / / (_) _ __  | | __ ___   __| |
//  / / \ \/ __| / _ \| '__|/ /\/| '_ \ | __|/ _ \| '__|| |_  / _` | / __|/ _ \ / /  | || '_ \ | |/ // _ \ / _` |
//  \ \_/ /\__ \|  __/| |/\/ /_  | | | || |_|  __/| |   |  _|| (_| || (__|  __// /___| || | | ||   <|  __/| (_| |
//   \___/ |___/ \___||_|\____/  |_| |_| \__|\___||_|   |_|   \__,_| \___|\___|\____/|_||_| |_||_|\_\\___| \__,_|
//                                                                                                               


Mike::UserInterfaceLinked::UserInterfaceLinked(): UserInterfaceBase()
{

}

void Mike::UserInterfaceLinked::sendWidTableCallback(int rowPressed, int colPressed, long price, MikeOrderType tempOrderType, int orderSize)
{
	std::cout << "UserInterfaceLinked::sendWidTableCallback Callback" << std::endl;
}

void Mike::UserInterfaceLinked::callbkUserInterface(BtnPressed)
{
	std::cout << "Callback" << std::endl;
}


//   __ _                 _     _____      _     _      __    __ _           _               
//  / _(_)_ __ ___  _ __ | | __/__   \__ _| |__ | | ___/ / /\ \ (_)_ __   __| | _____      __
//  \ \| | '_ ` _ \| '_ \| |/ _ \/ /\/ _` | '_ \| |/ _ \ \/  \/ / | '_ \ / _` |/ _ \ \ /\ / /
//  _\ \ | | | | | | |_) | |  __/ / | (_| | |_) | |  __/\  /\  /| | | | | (_| | (_) \ V  V / 
//  \__/_|_| |_| |_| .__/|_|\___\/   \__,_|_.__/|_|\___| \/  \/ |_|_| |_|\__,_|\___/ \_/\_/  
//                 |_|                                                                       

//#include "SimpleTableWindow.h"
#include "WidgetTable.h"
#include "Control.h"

//
//SimpleTableWindow::SimpleTableWindow(Control * ptrControl, short windownumber)
//{
//	mwindow1->begin();
//	delete mTable;
//
//	int top_row_price = 250,
//		number_rows = 20,
//		number_cols = 5,
//		how_many_cols_are_buttons = 2,
//		tableCallbackType = 1;//need to tell WidgetTable that callbacks will be sent to Control, not UserInterface
//
//	std::vector <std::string>  col_names = { "Description", "Value" };
//	std::vector <std::string>  button_names = { "EMPTY", "SECOND" };
//
//	widTable = new WidgetTable(5, 5, 940, 630, "widgettable", ptrControl, top_row_price, number_rows,
//		number_cols, how_many_cols_are_buttons, col_names, button_names, tableCallbackType, windownumber);
//
//	mwindow1->end();
//	mwindow1->label("experimental");
//
//	widTable->SetColumnnWidth(90);
//
//	widTable->redraw();
//	mwindow1->show();
//}
//
//
//SimpleTableWindow::~SimpleTableWindow()
//{
//}
//
//void SimpleTableWindow::rePriceWidTable(long priceattoprow)
////UNDER CONSTRUCTION
////Updates prices displayed in WidgetTable to between 100 above and below
////current bid price in Data class
////Updates slider in UserInterface to current Bid price
//{
//	WidgetTable * pTable = widTable;
//
//	pTable->SetTopRowPrice(priceattoprow);
//	//draw the new widget table:
//	this->mwindow1->hide();
//	this->mwindow1->redraw();
//	this->mwindow1->show();
//
//
//
//	//populate price column with prices:
//
//	//pUI->GetTable()->ClearColumn(6);	//clear the bid and ask columns
//	//pUI->GetTable()->ClearColumn(7);
//	//pUI->GetTable()->PopPriceCol();
//}
//

//     ___             ___         _                                _        _____ 
//    / _ \___  ___   /___\_ __ __| | /\/\   __ _ _ __  _   _  __ _| |/\ /\  \_   \
//   / /_)/ _ \/ __| //  // '__/ _` |/    \ / _` | '_ \| | | |/ _` | / / \ \  / /\/
//  / ___/ (_) \__ \/ \_//| | | (_| / /\/\ \ (_| | | | | |_| | (_| | \ \_/ /\/ /_  
//  \/    \___/|___/\___/ |_|  \__,_\/    \/\__,_|_| |_|\__,_|\__,_|_|\___/\____/  
//                                                                                 

//Mike::PosOrdManualUI::PosOrdManualUI(void * control,
//	double starting_bid_price,
//	int numberOfColumns,
//	int numberOfButtoncolumns)
//{
//	mWindow1->begin();
//	delete mTable;
//
//	int top_row_price = 250,
//		number_rows = 20,
//		number_cols = 5,
//		how_many_cols_are_buttons = 2,
//		tableCallbackType = 1;//need to tell WidgetTable that callbacks will be sent to Control, not UserInterface
//
//	std::vector <std::string>  col_names = { "Description", "Value" };
//	std::vector <std::string>  button_names = { "something", "like" };
//
//	mTable = new WidTable1();
//
////	mTable = new WidgetTable(5, 5, 940, 630, "widgettable", this, top_row_price, number_rows,
////		number_cols, how_many_cols_are_buttons, col_names, button_names);
//
////	mTable = new WidgetTable(0, 0, 960, 1010, "", NULL , top_row_price, number_rows,
////		number_cols, how_many_cols_are_buttons, col_names, button_names, tableCallbackType, 2);
//
////	mTable->SetColumnnWidth(90);
//
//	mTable->redraw();
//	mWindow1->end();
//	mWindow1->label("experimental");
//
//	mWindow1->show();
//}
////
////PosOrdManualUI::~PosOrdManualUI()
////{
////}

using namespace std;

Mike::ControlInterface::ControlInterface()
{
	//set callbacks:
	m_btnShowPositions1->callback(m_btnShowPositions1_cb, (void*) this);
	//show the window:
	m_window1->show();
}

void Mike::ControlInterface::m_btnShowPositions1_cb(Fl_Widget * w, void * p)
{
	//FLTK callback have to be static
	//so call a virtual callback:
	ControlInterface * myInterface = (ControlInterface*)p;
	myInterface->maincallback(w, p);
}

void Mike::ControlInterface::maincallback(Fl_Widget * w, void * p)
{
	if (callbackDestination == NULL) {
		cout << "Callback destination not set!" << endl;
		return;
	}

	int callbackParameter = 0;
	if (w->label() == "Positions1") callbackParameter = 1;

	callbackDestination->callbkControlInterface(callbackParameter);
}


