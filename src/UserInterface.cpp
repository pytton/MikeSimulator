//WidgetTable callback: void CallbkWidTable(int rowPressed, int colPressed, long price);
//THIS IS WHERE THE ORDER TYPE IS DETERMINED
//BASED ON WHICH COLUMN HAS BEEN PRESSED IN WIDGETTABLE



#include <sstream> //replaces cout
//#include <string>
//#include <vector>
#include "UserInterface.h"
//#include "Display.h"
#include "MikeSimulator.h"
#include "WidgetTable.h"
#include "MikeTimer.h"

#include "MikeEnums.h"

#include "Control.h"

//class Control;

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
	
	m_pTable = new WidgetTable(5, 5, 765, 655, "widgettable", this, top_row_price, number_rows,
		number_cols, how_many_cols_are_buttons, col_names, button_names);


	m_window1->end();
	//******************************************************************************************

	//******************
	//SETTING CALLBACKS:
	//******************
//	m_btn_next->callback(experimental_cb, (void*)this);
	m_btn_extra->callback(m_extra_btn_cb, (void*) this);	//this changes size of Widgettable
	m_btn_printOrders->callback(m_printOrders_btn_cb, (void*) this);
	m_btn_checkFills->callback(m_checkFills_btn_cb, (void*) this);
	m_btn_printPos->callback(m_printPos_btn_cb, (void*) this);




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

	//first - make sure that the TopRowPrice is set to 100 above current bid price:
	
	pTable->SetTopRowPrice(bidprice + 100);
	//draw the new widget table:
	//pTable->SetSize(pTable->GetRows(), pTable->GetCols(), pTable);	//this needs to be called to construct all the cells of WidgetTable																					
	//pUI->SetTable(pTable);
	pUI->m_window1->hide();
	pUI->m_window1->redraw();
	pUI->m_window1->show();

	//populate price column with prices:

	pUI->GetTable()->ClearColumn(6);	//clear the bid and ask columns
	pUI->GetTable()->ClearColumn(7);
	pUI->GetTable()->PopPriceCol();



	//modify slider in UserInterface:
	//update the slider minimum and maximum settings:
	//setting initial Slider max/min values to that of bid/ask - offset:



	//REFACTOR THIS: (MOVE IT TO CONTROL?)

	//int value, max, min;
	//value = (int)data->GetBidPrice();
	//min = (int)data->GetBidPrice() + ((pTable->GetRows()) / 2) - 3 /* 3 offset for safety*/;
	//max = (int)data->GetBidPrice() - ((pTable->GetRows()) / 2) + 3 /* 3 offset for safety*/;

	//m_pPriceControlUI->setSlider(value, max, min);








	//GetPriceControlUI()->Getm_slider1()->minimum((double)data->GetBidPrice() + ((pTable->GetRows()) / 2) - 3 /* 3 offset for safety*/);
	//GetPriceControlUI()->Getm_slider1()->maximum((double)data->GetBidPrice() - ((pTable->GetRows()) / 2) + 3 /* 3 offset for safety*/);
	//GetPriceControlUI()->Getm_slider1()->value((double)data->GetBidPrice());



	//*************************************************************************
	//this commented out after moving slider to seperate window - kept for reference
	//pUI->m_slider1->minimum((double)data->GetBidPrice() + ((pTable->GetRows()) / 2) - 3 /* 3 offset for safety*/);
	//pUI->m_slider1->maximum((double)data->GetBidPrice() - ((pTable->GetRows()) / 2) + 3 /* 3 offset for safety*/);
	//pUI->m_slider1->value((double)data->GetBidPrice());
	//*****************************************************************************



}


//CALLBACKS:
//void UserInterface::m_slider1_cb(Fl_Widget *w, void * p)
//{	// void *p should be 'this' of UserInterface - it should be set up in
//	//UserInterface constructor
//	//UserInterface * myUserInt = (UserInterface*)p;
//
//	//myUserInt->m_pControl->CallbkUserInt(myUserInt, SLIDER1);
//}
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
//void UserInterface::m_up_btn_cb(Fl_Widget *w, void * p)
//{
////	UserInterface * myUserInt = (UserInterface*)p;
////
//////	myUserInt->m_pControl->m_up_btn_cb(myUserInt);
////
////	myUserInt->m_pControl->CallbkUserInt(myUserInt, UPBTN);
//	//REFACTORING COMPLETE!!
//}
//void UserInterface::m_down_btn_cb(Fl_Widget *w, void * p)
//{
//	UserInterface * myUserInt = (UserInterface*)p;
//
//	//myUserInt->m_pControl->m_down_btn_cb(myUserInt);
//	myUserInt->m_pControl->CallbkUserInt(myUserInt, DOWNBTN);
//	//REFACTORING COMPLETE!!
//}
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
	{case 0:
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

	if (checkForValidOrderType)
	{
		GetControl()->CallbkWidTable(rowPressed, colPressed, price, tempOrderType);
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
	else {
		std::cout << "\n ASK OUTSIDE OF WIDGETTABLE" << std::endl;
	}



}

//void UserInterface::PrintAll(long totalOpenPos, long totalOpenPL, long totalClosedPL, long totalPL, long askPrice, long bidPrice, const std::vector<MikePosition>* openPositions)
//{
//	std::cout << "Postition at ask price: " << openPositions->at(askPrice).open_amount << std::endl;
//
//}

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

//	cout << "\nTotalOpenPos: " << totalOpenPos << " Others: " << totalOpenPL << " " <<
//		totalClosedPL << " " << totalPL << " " << askPrice << " " << bidPrice << endl;
	


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


	
//	GetTable()->printPositions(openPositions);
	GetTable()->printPositions(openPositions, openOrdersAtPrice);


	//for (int i = (askPrice - 3); i < (askPrice + 3); i++) {

	//	std::cout << "Postition at price: " << i << " is: " << 
	//		openPositions->at(i).open_amount << std::endl;

	//}

//	timer.print();


	//snprintf(buffer, 20, "%d", bidPrice);
	//m_TotOpenPos->value(buffer);
	//m_pTable->printInTable(10, 8, buffer);
	//snprintf(buffer, 20, "%d", totalPL);
	//m_pTable->printInTable(10, 9, buffer);
	//for (int i = 0; i < 100; i++)
	//{
	//	snprintf(buffer, 20, "%d", (totalPL +i) );
	//	m_pTable->printInTable(10 + i, 9, buffer);
	//}

}



//old callback kept for reference:
//void UserInterface::experimental_cb(Fl_Widget *w, void * p)
//{
//	using namespace std;
//	cout << "experimental called!" << endl;
//	UserInterface * myInterface = (UserInterface*)p;
//	WidgetTable * myTable = myInterface->GetTable();
//	
//	//	WidgetTable * myTable =(WidgetTable*) p;
//
//	std::string trythis = "mess";
//	int row = 25;
//	int col = 7;
//
//	myTable->printInTable(row, col, trythis/*, myTable*/);
//	myInterface->GetControl()->printCurrentAll();
//}









//BELOW IS OLD CODE KEPT FOR FUTURE REFERENCE:


//void UserInterface::rePriceWidTable(Fl_Widget *w, void*p)	
////THIS FUNCTION HAS BEEN MOVED FROM USERINTERFACE TO CONTROL
////UNDER CONSTRUCTION
////Updates prices displayed in WidgetTable to between 100 above and below
////current bid price in Data class
////Updates slider in UserInterface to current Bid price
//{
//	MikeSimulator * mikesimulator = (MikeSimulator*)p;
//
//	UserInterface* pUI = mikesimulator->GetDisplay()->GetUInterface();
//
//	WidgetTable * pTable = pUI->GetTable();
//
//	//BELOW CODE SET NEW SIZE OF WIDGETTABLE:
//
//	//pTable->clear();
//
//	//first - make sure that the TopRowPrice is set to 100 above current bid price:
//	//Data * myData = mikesimulator->GetData();
//	pTable->SetTopRowPrice(mikesimulator->GetData()->GetBidPrice() + 100);
//	//draw the new widget table:
//	//pTable->SetSize(pTable->GetRows(), pTable->GetCols(), pTable);	//this needs to be called to construct all the cells of WidgetTable																					
//																		//pUI->SetTable(pTable);
//	pUI->m_window1->hide();
//	pUI->m_window1->redraw();
//	pUI->m_window1->show();
//
//	//populate price column with prices:
//	mikesimulator->GetDisplay()->GetUInterface()->GetTable()->PopPriceCol(/*mikesimulator->GetDisplay()->GetWindow()->GetTable()*/);
//	//modify slider in UserInterface:
//	//update the slider minimum and maximum settings:
//	//setting initial Slider max/min values to that of bid/ask - offset:
//	pUI->m_slider1->minimum((double)mikesimulator->GetData()->GetBidPrice() + ((pTable->GetRows()) / 2) - 3 /* 3 offset for safety*/);
//	pUI->m_slider1->maximum((double)mikesimulator->GetData()->GetBidPrice() - ((pTable->GetRows()) / 2) + 3 /* 3 offset for safety*/);
//	pUI->m_slider1->value((double)mikesimulator->GetData()->GetBidPrice());
//}
//void UserInterface::rePriceWidTable2(Fl_Widget *w, void*p)	//UNDER CONSTRUCTION
//															//Updates prices displayed in WidgetTable to between 100 above and below
//															//current bid price in Data class
//															//Updates slider in UserInterface to current Bid price
//{
//
//	////this version takes the 'this' pointer instead of MikeSimulator as the void *p parameter
//	////MikeSimulator * mikesimulator = (MikeSimulator*)p;
//	//UserInterface* pUI = (UserInterface*)p;
//
//
//	//WidgetTable * pTable = pUI->GetTable();
//
//	////BELOW CODE SET NEW SIZE OF WIDGETTABLE:
//
//	////pTable->clear();
//
//	////first - make sure that the TopRowPrice is set to 100 above current bid price:
//	////Data * myData = mikesimulator->GetData();
//	//pTable->SetTopRowPrice(pUI->bid_price + 100);
//	////draw the new widget table:
//	////pTable->SetSize(pTable->GetRows(), pTable->GetCols(), pTable);		//this needs to be called to construct all the cells of WidgetTable																					
//	////pUI->SetTable(pTable);
//	//pUI->m_window1->hide();
//	//pUI->m_window1->redraw();
//	//pUI->m_window1->show();
//
//	////populate price column with prices:
//	//pUI->GetTable()->PopPriceCol(/*mikesimulator->GetDisplay()->GetWindow()->GetTable()*/);
//	////modify slider in UserInterface:
//	////update the slider minimum and maximum settings:
//	////setting initial Slider max/min values to that of bid/ask - offset:
//	//pUI->m_slider1->minimum((double)mikesimulator->GetData()->GetBidPrice() + ((pTable->GetRows()) / 2) - 3 /* 3 offset for safety*/);
//	//pUI->m_slider1->maximum((double)mikesimulator->GetData()->GetBidPrice() - ((pTable->GetRows()) / 2) + 3 /* 3 offset for safety*/);
//	//pUI->m_slider1->value((double)mikesimulator->GetData()->GetBidPrice());
//}



//void WidgetTable::draw_cell(TableContext context,
//	int R, int C, int X, int Y, int W, int H)
//{
//	switch (context)
//	{
//	case CONTEXT_STARTPAGE:
//		fl_font(FL_HELVETICA, 12);		// font used by all headers
//		col_width_all(50);				// sets the width of the columns
//		break;
//
//	case CONTEXT_RC_RESIZE:
//	{
//		int X, Y, W, H;
//		int index = 0;
//		for (int r = 0; r<rows(); r++)
//		{
//			for (int c = 0; c<cols(); c++)
//			{
//				if (index >= children()) break;
//				find_cell(CONTEXT_TABLE, r, c, X, Y, W, H);
//				child(index++)->resize(X, Y, W, H);
//			}
//		}
//		init_sizes();			// tell group children resized
//		return;
//	}
//
//	case CONTEXT_ROW_HEADER:
//		fl_push_clip(X, Y, W, H);
//		{
//			static char s[40];
//			sprintf(s, "Row %d", R);
//			fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
//			fl_color(FL_BLACK);
//			fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
//		}
//		fl_pop_clip();
//		return;
//
//	case CONTEXT_COL_HEADER:
//		fl_push_clip(X, Y, W, H);
//		{
//			static char s[40];
//			//below decide what is printed in column headers:
//			ColHeaderText(s, C);	//this function performs commented out code below
//
//			//if (C == 0)
//			//{
//			//	sprintf(s, "BUY");
//			//}
//			//else
//			//{
//			//	sprintf(s, "Col %d", C);
//			//}
//
//			fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, col_header_color());
//			fl_color(FL_BLACK);
//			fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
//		}
//		fl_pop_clip();
//		return;
//
//	case CONTEXT_CELL:
//		return;		// fltk handles drawing the widgets
//
//	default:
//		return;
//	}
//}

//OLD CODE - JUST TO SHOW LEARNING PROCESS
//void UserInterface::printInTable(int row, int col, std::string text, UserInterface *p)//this causes trouble
//{
//	
//	UserInterface * myInterface = p;
//
//	WidgetTable * myWidgetTable = myInterface->table;
//
//	Fl_Widget * myWidget =  myWidgetTable->GetElement(row, col);
//
//	Fl_Input * myCell = dynamic_cast<Fl_Input*>(myWidget);
//
//	std::stringstream buffer;
//
//	buffer << "try";
////	myCell->value(buffer.str().c_str());
//
//	//myCell->value("try");
//
//	//Fl_Widget * myWidget = mytable->GetElement(row, col);
//	
//	
//	/*Fl_Input * myTargetCell = 
//	mytable->GetElement(row, col);*/
//	
//	
//	//Fl_Input  * targetCell = (Fl_Input*)(table->GetElement(row, col));
//	//std::stringstream buffer;
//	//buffer << text;
//
//	//targetCell->value(buffer.str().c_str());
//	//targetCell->value("400");
//}

//OLD CODE
//void WidgetTable::printInTable(int row, int col, std::string text, UserInterface * myIntPointer)//this causes trouble
//{
//
//	UserInterface * myInterface = myIntPointer;
//
//
//	WidgetTable * myTable = myIntPointer->table;
//
//	//Fl_Widget * myWidget = myTable->GetElement(row, col);
//
//	Fl_Widget * myWidget = static_cast<Fl_Widget*> (myTable->GetVoidElement(row, col));
//
//	//Fl_Input * myCell = static_cast<Fl_Input*>(myWidget);
//
//	Fl_Input * myCell = (Fl_Input*)(myWidget);
//
//	//My_fl_button * myCell = static_cast<My_fl_button*>(myWidget);
//
//	std::stringstream buffer;
//
//	buffer << "try";
//	//myCell->value(buffer.str().c_str());
//
//	//myCell->value("try");
//
//	//Fl_Widget * myWidget = mytable->GetElement(row, col);
//
//
//	/*Fl_Input * myTargetCell =
//	mytable->GetElement(row, col);*/
//
//
//	//Fl_Input  * targetCell = (Fl_Input*)(table->GetElement(row, col));
//	//std::stringstream buffer;
//	//buffer << text;
//
//	//targetCell->value(buffer.str().c_str());
//	//targetCell->value("400");
//
//}

//Fl_Text_Buffer * UserInterface::textBuffer;
//Fl_Text_Display * UserInterface::text;

//void UserInterface::setptr()		//OLD CODE?? DO I STILL NEED THIS?
//{
//	table->ptr_to_UserInterface = this;
//}

//void UserInterface::cb_btn_start_callback(Fl_Widget* btn, void* userdata)
//{
//	UserInterface* window = (UserInterface*)userdata;
//	window->m_window1->label("start"); //set window title
//	window->m_is_animated = true;
//	Fl::add_timeout(/*TIMER_TIMEOUT*/ UserInterface::TIMER_TIMEOUT, timer_event, window);
//}

//void UserInterface::cb_btn_stop_callback(Fl_Widget* btn, void* userdata)
//{
//	UserInterface* window = (UserInterface*)userdata;
//	window->m_is_animated = false;
//	window->m_window1->label("stop");
//}

//void UserInterface::timer_event(void* userdata)
//{
//	UserInterface* window = (UserInterface*)userdata;
//	
//	if (window->m_is_animated)
//	{
//		++window->m_count;
//		std::stringstream buffer;
//		buffer << window->m_count;
//		//buffer.str(); // .str() convert what's in buffer to string
//		//buffer.str().c_str(); // .c_str() converts std::string to char*
//		window->m_window1->label(buffer.str().c_str() );
//		Fl::add_timeout(/*TIMER_TIMEOUT*/1.0, timer_event, window);
//	}
//}

//void UserInterface::m_down_btn_cb(Fl_Widget *w, void * p)
//{
//	//UserInterface * myUserInt = (UserInterface*)p;
//
//
//	//REFACTOR THIS:
//
//	UserInterface * myUserInt = (UserInterface*)p;
//	Data * myData = myUserInt->ptr_to_mikesimulator->GetData();
//	Control * myControl = myUserInt->ptr_to_mikesimulator->GetControl();
//
//	//change bid ask prices:
//	myData->SetPrevAskPrice(myData->GetAskPrice());
//	myData->SetPrevBidPrice(myData->GetBidPrice());
//	myData->SetAskPrice(myData->GetAskPrice() - 1);
////	myData->ask_price--;
//	myData->SetBidPrice(myData->GetBidPrice() - 1);
////	myData->bid_price--;
//	//update slider value:
//	myUserInt->m_slider1->value((double)myData->GetBidPrice());
//	//do something:
//	myControl->MainLoop();
//}

//void UserInterface::m_up_btn_cb(Fl_Widget *w, void * p)
//{
//	UserInterface * myUserInt = (UserInterface*)p;
//	Data * myData = myUserInt->ptr_to_mikesimulator->GetData();
//	Control * myControl = myUserInt->ptr_to_mikesimulator->GetControl();
//
//	//change bid ask prices:
//	if (myUserInt)
//	{
//		myData->SetPrevAskPrice(myData->GetAskPrice());
//		myData->SetPrevBidPrice(myData->GetBidPrice());
//		myData->SetAskPrice(myData->GetAskPrice() + 1);
//		myData->SetBidPrice(myData->GetBidPrice() + 1);
//		std::cout << "price change" << std::endl;
//
//	}
//	else
//	{
//		std::cout << "Missing a pointer" << std::endl;
//	}
//	
//
//
//	//update slider value:
//	myUserInt->m_slider1->value((double)myData->GetBidPrice());
//	//do something:
//	myControl->MainLoop();
//}

//void UserInterface::m_slider1_cb(Fl_Widget *w, void * p)
//{
//	Fl_Value_Slider * mySlider = (Fl_Value_Slider*)w;
//	UserInterface * myUserInt = (UserInterface*)p;
//	Data * myData = myUserInt->ptr_to_mikesimulator->GetData();
//	Control * myControl = myUserInt->ptr_to_mikesimulator->GetControl();
//	double sliderVal = mySlider->value();
//
//	//change bid ask prices:
//	myData->SetPrevAskPrice(myData->GetAskPrice());
//	myData->SetPrevBidPrice(myData->GetBidPrice());
//	long differenceBidAsk;	//preserve bid ask spread
//	differenceBidAsk = myData->GetAskPrice() - myData->GetBidPrice();
//	myData->SetAskPrice((long)sliderVal + differenceBidAsk);
//	myData->SetBidPrice((long)sliderVal);
//	//do something:
//	myControl->MainLoop();
//}

////WIDGETTABLE:
////CONSTRUCTOR:
//WidgetTable::WidgetTable(UserInterface * pUserInterface, int x, int y, int w, int h, const char *l = 0) : Fl_Table_Row(x, y, w, h, l)
//{
//
//	ptr_to_UserInterface = pUserInterface;
//
//	ButtonColsNumber = 5;	//how many columns of buttons?
//	TopRowPrice = 800;
//	table_rows, table_cols = 20;
//
//	col_header(1);
//	col_resize(1);
//	col_header_height(40);
//
//	row_header(1);
//	row_resize(0);
//	row_header_width(40);
//	end();
//
//
//	//col_header(1);
//	//col_resize(0);
//	//col_header_height(20);
//	//row_header(1);
//	//row_resize(0);
//	//row_header_width(30);
//	//end();
//
//
//}
////below fills the table with objects:
//void WidgetTable::SetSize(int newrows, int newcols, WidgetTable * mytable)
//{
//	rows(newrows);
//	cols(newcols);
//	mytable->SetRows(newrows);
//	mytable->SetCols(newcols);
//
//	begin();		// start adding widgets to group
//	{
//		for (int r = 0; r<newrows; r++)
//		{
//			for (int c = 0; c<newcols; c++)
//			{
//				int X, Y, W, H;
//				find_cell(CONTEXT_TABLE, r, c, X, Y, W, H);
//				char s[40];
//				//below decides what is put into table:
//				//r is row and c is col
//				if (c >= mytable->ButtonColsNumber/*c != 0 && c != 1 && c != 2 && c != 3*/) //this used to be ( c & 1) -bitwise comparison				
//				{
//					// Create the input widgets
//					//sprintf(s, "%d/%d", r, c);
//					Fl_Input *in = new Fl_Input(X, Y, W, H);
//					//in->value(s);
//					in->textsize(10);	//sets the size of the font					
//				}
//				else
//				{
//					// Create the light buttons
//					sprintf(s, "%d/%d ", r, c);
//					My_fl_button *butt = new My_fl_button(X, Y, W, H, strdup(s));
//					//Fl_Light_Button *butt = new Fl_Light_Button(X, Y, W, H, strdup(s));
//					butt->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
//					butt->callback(button_cb, (void*)mytable);
//					//butt->value(((r + c * 2) & 4) ? 1 : 0);	//this sets the light on or off for Fl_Light_Button
//					if (c == 0) butt->label("CXL");
//					if (c == 1) butt->label("B LMT");
//					if (c == 2) butt->label("B STP");
//					if (c == 3) butt->label("S LMT");
//					if (c == 4) butt->label("S STP");
//					butt->x_pos = c;	//set the col
//					butt->y_pos = r;	//set the row
//				}
//
//			}
//		}
//	}
//	end();
////below doesnt work:
////	mytable->PopPriceCol(this);
////	PopPriceCol();	//populate price column with prices
//
//}
//void WidgetTable::draw_cell(TableContext context,
//	int R, int C, int X, int Y, int W, int H)
//{
//	switch (context)
//	{
//	case CONTEXT_STARTPAGE:
//		fl_font(FL_HELVETICA, 9);		// font used by all headers
//		col_width_all(55);				// sets the width of the columns
//		row_height_all(18);
//		break;
//
//	case CONTEXT_RC_RESIZE:
//	{
//		int X, Y, W, H;
//		int index = 0;
//		for (int r = 0; r<rows(); r++)
//		{
//			for (int c = 0; c<cols(); c++)
//			{
//				if (index >= children()) break;
//				find_cell(CONTEXT_TABLE, r, c, X, Y, W, H);
//				child(index++)->resize(X, Y, W, H);
//			}
//		}
//		init_sizes();			// tell group children resized
//		return;
//	}
//
//	case CONTEXT_ROW_HEADER:
//		fl_push_clip(X, Y, W, H);
//		{
//			static char s[40];
//			sprintf(s, "%d", TopRowPrice - R);
//			fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
//			fl_color(FL_BLACK);
//			fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
//		}
//		fl_pop_clip();
//		return;
//
//	case CONTEXT_COL_HEADER:
//		fl_push_clip(X, Y, W, H);
//		{	//set the width of a single column:
//			//this doesnt work :(	
//			//if (C == 1)
//			//{
//			//	col_width(C, 30);
//			//	init_sizes();
//			//	Fl::redraw();
//			//}
//
//			fl_font(FL_HELVETICA, 11);
//			static char s[40];
//			//below decide what is printed in column headers:
//			ColHeaderText(s, C);	//this function performs commented out code below
//
//									//if (C == 0)
//									//{
//									//	sprintf(s, "BUY");
//									//}
//									//else
//									//{
//									//	sprintf(s, "Col %d", C);
//									//}
//
//			fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, col_header_color());
//			fl_color(FL_BLACK);
//			fl_draw(s, X, Y, W, H, /*FL_ALIGN_CENTER,*/ FL_ALIGN_WRAP);	//modified to use wrap
//		}
//
//		fl_pop_clip();
//		return;
//
//	case CONTEXT_CELL:
//		return;		// fltk handles drawing the widgets
//
//	default:
//		return;
//	}
//}
//void WidgetTable::ColHeaderText(char * s, int C)	//defines text of column headers
//{
//	switch (C)
//	{
//	case 0:
//		sprintf(s, "CANCEL\nORDER");
//		break;
//	case 1:
//		sprintf(s, "BUY");
//		break;
//	case 2:
//		sprintf(s, "BUY");
//		break;
//	case 3:
//		sprintf(s, "SELL");
//		break;
//	case 4:
//		sprintf(s, "SELL");
//		break;
//	case 5:
//		sprintf(s, "PRICE");
//		break;
//	case 6:
//		sprintf(s, "BID");
//		break;
//	case 7:
//		sprintf(s, "ASK");
//		break;
//	case 8:
//		sprintf(s, "ORDER\nSIZE");
//		break;
//	case 9:
//		sprintf(s, "ORDER\nTYPE");
//		break;
//	case 10:
//		sprintf(s, "ORDER\nPRICE");
//		break;
//	case 11:
//		sprintf(s, "OPEN\nPOSITION");
//		break;
//	case 12:
//		sprintf(s, "OPEN\nP/L");
//		break;
//	case 13:
//		sprintf(s, "CLOSED\nP/L");
//		break;
//	case 14:
//		sprintf(s, "TOTAL\nP/L");
//		break;
//	default:
//		sprintf(s, "Col %d", C);
//	}
//	//if (C == 0)
//	//{
//	//	sprintf(s, "BUY");
//	//}
//	//else
//	//{
//	//	sprintf(s, "my %d", C);
//	//}
//}
//My_fl_button::My_fl_button(int x, int y, int w, int h, const char *l = 0)
//	: Fl_Button(x, y, w, h, l), x_pos(0), y_pos(0)
//{
//	x_pos = 0;
//	y_pos = 0;
//}
////CALLBACKS:
//void WidgetTable::button_cb(Fl_Widget *w, void * p)
//{
//	//this callback is set inside the WidgetTable::SetSize function!!
//	My_fl_button * myButton = (My_fl_button*)w;		//myButton is the button that was pressed
//	WidgetTable * thisTable = (WidgetTable*)p;		//thisTable is the table in which the button was pressed
//	UserInterface * myUI = thisTable->GetUserInterface();	//myUI is the UserInterface in which the table is created
//	MikeSimulator * mySimulator = myUI->GetMikeSim();
//
//	//send the information to Control:
//	//What price level was pressed?:
//	int rowPressed = myButton->y_pos;		//this is the row in which the button was pressed
//	long price = thisTable->PriceOfRow(rowPressed);
//	int OrderType = myButton->x_pos;
//	mySimulator->GetControl()->ManualOrder(OrderType, price);	//send the information to Control
//	//below - print out the price corresponding to the row in which the button was pressed:
//
//	
//	//std::cout << "\nRow pressed: " << rowPressed << std::endl;
//	//std::cout << "\nCorresponding price: " << thisTable->PriceOfRow(rowPressed) << std::endl;
//
//
////	std::cout << '\n' << sizeof(long) << " " << sizeof(long long) << " " << sizeof(double);
//
//
//	//OLD CODE:
//	////	fprintf(stderr, "BUTTON: %s\n", (const char*)w->label());
//	//	
//	//	WidgetTable * myTable = static_cast<WidgetTable*>(p);		//WidgetTable * myTable = (WidgetTable*)(p);
//	//	UserInterface * myUserInterface = static_cast<UserInterface*>(myTable->ptr_to_UserInterface);		//UserInterface * myUserInterface = (UserInterface*)(myTable->ptr_to_UserInterface);
//	//	int  myRow = 8, myColumn = 8;
//	//	Fl_Widget * myWidget = myTable->GetElement(myRow, myColumn);
//	//	Fl_Input * myCell = dynamic_cast<Fl_Input*>(myWidget);
//	//
//	//	myWidget = myTable->GetElement(myRow, myColumn);
//	//
//	//	My_fl_button * myFlButton = (My_fl_button*)w;
//	//	//printout the x y positions of the button pressed:
//	//	std::cout << std::endl << myFlButton->x_pos << std::endl;
//	//	std::cout << myFlButton->y_pos << std::endl;
//	//
//	//	myCell = dynamic_cast<Fl_Input*>(myWidget);
//	//
//	//	myCell->value("try");
//	//	myUserInterface->textDisplayString << "button pressed" << std::endl;
//	//	myUserInterface->textBuffer->text((myUserInterface->textDisplayString).str().c_str());
//	//
//	//	myTable->printInTable(6, 6, "text"/*, myTable*/);
//
//}
////HELPLERS:
//void WidgetTable::printInTable(int row, int col, std::string text)//row = 0 is first row!
//{
//	WidgetTable * myTable = this;
//
//	//	WidgetTable * myTable = myWidgetPointer;
//
//	//first, make sure row and col are not bigger than the size of the table:
//
//	//std::cout << myWidgetPointer->rows() << std::endl
//	//	<< myWidgetPointer->table_rows << std::endl 
//	//	<< row;
//
//	if (row >= myTable->GetRows()) {
//		std::cout << "\nPrint attempt in row outside of WidgetTable";
//		row = myTable->GetRows() - 1;
//	}
//	if (col >= myTable->GetCols()) {
//		std::cout << "\nPrint attempt in col outside of WidgetTable";
//		/*myCol*/col = myTable->GetCols() - 1;
//	}
//	if (row < 0) {
//		std::cout << "\nPrint attempt in row outside of WidgetTable";
//		row = 0;
//	}
//	if (col < myTable->ButtonColsNumber) {
//		std::cout << "\nPrint attempt in col outside of WidgetTable";
//		col = myTable->ButtonColsNumber;
//	}
//	//find the cell:
//	Fl_Widget * myWidget = (Fl_Widget*)(myTable->GetElement(row, col));
//	Fl_Input * myCell = (Fl_Input*)(myWidget);
//	//print into the cell:
//	myCell->textsize(12);	//sets the size of the font
//	std::stringstream buffer;
//	buffer << text;
//	myCell->value(buffer.str().c_str());
//}
//Fl_Widget * WidgetTable::GetElement(int nRow, int nCol)	
//{//used to get a pointer to an element of WidgetTable with X Y coordinates nRow nCol
////nRow = 0 -> points to FIRST row; nCol = 0 -> points to col number 1!
////watch for off by one errors
//	int numCol = this->cols();
//	int nIndex = nRow * numCol + nCol;
//	return this->child(nIndex);
//}
//int WidgetTable::RowOfPrice(long price)
//{
//	int rowToReturn = TopRowPrice - price;
//	return rowToReturn;
//}   //given price - returns the row in which that price is displayed in WidgetTable
//long WidgetTable::PriceOfRow(int row)
//{
//	long price = TopRowPrice - row;
//
//	return price;
//}	 //given the row - returns what price is currently printed in that row
//MikeSimulator * WidgetTable::GetMikeSim()
//{
//	return ptr_to_UserInterface->GetMikeSim();
//}
//void WidgetTable::PopPriceCol(/*WidgetTable * myTable*/) //populates the Price column with prices based on current TopRowPrice
//{
//
//		int PriceCol = 5;	//change this as neccessary if design changes made to WidgetTable
//		int PriceToPrint;
//		//print prices in rows from 0 to last
//
//		for (int row = 0; row < table_rows; row++)
//		{
//			PriceToPrint = TopRowPrice - row;
//			Fl_Input * myCell = (Fl_Input*)GetElement(row, PriceCol);
//			char ch[40];
//			sprintf(ch, "%d", PriceToPrint);
//			myCell->value(ch);
//		}
//	
//}
//
//void WidgetTable::PopPriceCol(WidgetTable * myTable) //populates the Price column with prices based on current TopRowPrice
//{
//
//	int PriceCol = 5;	//change this as neccessary if design changes made to WidgetTable
//	int PriceToPrint;
//	//print prices in rows from 0 to last
//
//	for (int row = 0; row < table_rows; row++)
//	{
//		PriceToPrint = TopRowPrice - row;
//		Fl_Input * myCell = (Fl_Input*)GetElement(row, PriceCol);
//		char ch[40];
//		sprintf(ch, "%d", PriceToPrint);
//		myCell->value(ch);
//	}
//
//}