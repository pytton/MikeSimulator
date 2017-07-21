#include "UserInterface.h"
#include "WidgetTable.h"
#include "MikeTimer.h"
#include "MikePositionsOrders.h"
#include "Control.h"



//   #     #                              #######                              #  
//   #  #  # # #####   ####  ###### #####    #      ##   #####  #      ###### ### 
//   #  #  # # #    # #    # #        #      #     #  #  #    # #      #       #  
//   #  #  # # #    # #      #####    #      #    #    # #####  #      #####      
//   #  #  # # #    # #  ### #        #      #    ###### #    # #      #       #  
//   #  #  # # #    # #    # #        #      #    #    # #    # #      #      ### 
//    ## ##  # #####   ####  ######   #      #    #    # #####  ###### ######  #  
//                                                                                


WidgetTable::WidgetTable(
	int x, int y, int w, int h, const char *l,
	UserInterface * pUserInterface,
	int top_row_price,
	int number_rows,
	int number_cols,	/*how many columns in the table?*/
	int how_many_cols_are_buttons,	/*how many columns are buttons?*/
	std::vector <std::string> col_names,	/*names of col headers*/
	std::vector <std::string> button_names	//names of buttons
) : WidTableBase::WidTableBase( x,  y,  w,  h,  l,
	 top_row_price,
	 number_rows,
	 number_cols,
	 how_many_cols_are_buttons,
	 col_names,
	 button_names)
	
	
	
	/*WidTableBase(x, y, w, h, l)*/
{
	//moved below to WidTableBase constructor
	
	//TopRowPrice = top_row_price;
	//ButtonColsNumber = how_many_cols_are_buttons;	//how many columns of buttons?
	//this->col_names = col_names;	//this has to be set for SetSize and ColHeaderText functions

	//col_header(1);
	//col_resize(1);
	//col_header_height(40);
	//row_header(1);
	//row_resize(0);
	//row_header_width(40);
	//end();
	//SetCols(number_cols);
	//SetRows(number_rows);

	////this needs to be called to construct all the cells of WidgetTable
	//SetSize(GetRows(), GetCols(), this, button_names);

	//set the bid column and ask columns. virtual function:
	setBidAskColumns();

	ptr_to_UserInterface = pUserInterface;
}

WidgetTable::WidgetTable(
	int x, int y, int w, int h, const char *l,
	void * pCallbackPtr,
	int top_row_price,
	int number_rows,
	int number_cols,	/*how many columns in the table?*/
	int how_many_cols_are_buttons,	/*how many columns are buttons?*/
	std::vector <std::string> col_names,	/*names of col headers*/
	std::vector <std::string> button_names,	//names of buttons
	short tableCallbackType,//0-UserInterface, 1-Control
	short windownumber) : WidTableBase(x, y, w, h, l)
{
	//old way of setting callback - probably? still being used
	if (tableCallbackType == 0) {
		tabletype = tableCallbackType;//tabletype is used in the callback function to determine which callback to use
		ptr_to_UserInterface = static_cast<UserInterface*>   (pCallbackPtr);
		ptrControl = NULL;
		if (ptr_to_UserInterface == NULL) std::cout << "ERROR CREATING WIDGETTABLE!!!!!" << std::endl;
	}
	if (tableCallbackType == 1) {
		tabletype = tableCallbackType;
		this->windownumber = windownumber;
		ptr_to_UserInterface = NULL;
		ptrControl = static_cast<Control*>   (pCallbackPtr);
		if (ptrControl == NULL) std::cout << "ERROR CREATING WIDGETTABLE!!!!!" << std::endl;
	}

	TopRowPrice = top_row_price;
	ButtonColsNumber = how_many_cols_are_buttons;	//how many columns of buttons?
	this->col_names = col_names;	//this has to be set for SetSize and ColHeaderText functions

	col_header(1);
	col_resize(1);
	col_header_height(40);
	row_header(1);
	row_resize(0);
	row_header_width(40);
	end();
	SetCols(number_cols);
	SetRows(number_rows);

	//this needs to be called to construct all the cells of WidgetTable
	SetSize(GetRows(), GetCols(), this, button_names);

	//set the bid column and ask columns. virtual function:
	setBidAskColumns();

	//ptr_to_UserInterface = pUserInterface;
}

//not currently used:
WidgetTable::WidgetTable(int x, int y, int w, int h, const char *l) : WidTableBase(x, y, w, h, l)
{
	col_header(1);
	col_resize(1);
	col_header_height(40);
	row_header(1);
	row_resize(0);
	row_header_width(40);
	end();
	SetCols(10);
	SetRows(10);

	std::vector <std::string> col_names;	/*names of col headers*/
	std::vector <std::string> button_names;	//names of buttons

	SetSize(GetRows(), GetCols(), this, /*col_names,*/ button_names);		//this needs to be called to construct all the cells of WidgetTable
}

WidgetTable::WidgetTable() : WidTableBase(5, 5, 500, 400, "Empty")
{
	void * pCallbackPtr = NULL;
	int top_row_price = 250;
	int number_rows = 10;
	int number_cols = 5;	/*how many columns in the table?*/
	int how_many_cols_are_buttons = 2;	/*how many columns are buttons?*/
	std::vector <std::string> col_names = { "" };	/*names of col headers*/
	std::vector <std::string> button_names = { "" };	//names of buttons
	short tableCallbackType = 3; //0-UserInterface, 1-Control
	short windownumber = 3;
	//ptr_to_UserInterface = pUserInterface;
	if (tableCallbackType == 0) {
		tabletype = tableCallbackType;//tabletype is used in the callback function to determine which callback to use
		ptr_to_UserInterface = static_cast<UserInterface*>   (pCallbackPtr);
		ptrControl = NULL;
		if (ptr_to_UserInterface == NULL) std::cout << "ERROR CREATING WIDGETTABLE!!!!!" << std::endl;
	}
	if (tableCallbackType == 1) {
		tabletype = tableCallbackType;
		this->windownumber = windownumber;
		ptr_to_UserInterface = NULL;
		ptrControl = static_cast<Control*>   (pCallbackPtr);
		if (ptrControl == NULL) std::cout << "ERROR CREATING WIDGETTABLE!!!!!" << std::endl;
	}

	TopRowPrice = top_row_price;
	ButtonColsNumber = how_many_cols_are_buttons;	//how many columns of buttons?
	this->col_names = col_names;	//this has to be set for SetSize and ColHeaderText functions

	col_header(1);
	col_resize(1);
	col_header_height(40);
	row_header(1);
	row_resize(0);
	row_header_width(40);
	end();
	SetCols(number_cols);
	SetRows(number_rows);

	SetSize(GetRows(), GetCols(), this, button_names);		//this needs to be called to construct all the cells of WidgetTable
															//set the bid column and ask columns. virtual function:
	setBidAskColumns();
}

//             _ _ _                _          
//    ___ __ _| | | |__   __ _  ___| | _____ _ 
//   / __/ _` | | | '_ \ / _` |/ __| |/ / __(_)
//  | (_| (_| | | | |_) | (_| | (__|   <\__ \_ 
//   \___\__,_|_|_|_.__/ \__,_|\___|_|\_\___(_)
//                                             

void WidgetTable::virtButtonCb(Fl_Widget * w, void * p)
{
	My_fl_button * myButton = (My_fl_button*)w;  //myButton is the button that was pressed
	WidgetTable * thisTable = (WidgetTable*)p;  //thisTable is the table in which the button was pressed

												//HACK: check that there are no null pointers:
	if (tabletype != 0 && tabletype != 1) return;
	if (thisTable->ptr_to_UserInterface == NULL && tabletype == 0) return;
	if (thisTable->GetControl() == NULL && tabletype == 1) return;

	//send the information to Control:
	//What price level was pressed?:
	int rowPressed = myButton->y_pos;		//this is the row in which the button was pressed
	int colPressed = myButton->getXpos();
	long price = thisTable->PriceOfRow(rowPressed);

	std::cout << "\nColumn pressed in WidTable: " << colPressed << std::endl << "Row button pressed: " << rowPressed << std::endl;

	if (thisTable->tabletype == 0) { thisTable->ptr_to_UserInterface->CallbkWidTable(rowPressed, colPressed, price); }
	if (thisTable->tabletype == 1) {
		thisTable->GetControl()->CallbkSmplTableWin(rowPressed, colPressed, price, thisTable->windownumber);
	}
}

//              _       _                  
//   _ __  _ __(_)_ __ | |_ ___ _ __ ___ _ 
//  | '_ \| '__| | '_ \| __/ _ \ '__/ __(_)
//  | |_) | |  | | | | | ||  __/ |  \__ \_ 
//  | .__/|_|  |_|_| |_|\__\___|_|  |___(_)
//  |_|                                    

void WidgetTable::printPositions(const std::vector <MikePosition> *openPositions,
	const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice)
{
	using namespace std;

	Timer timer;
	timer.reset();	//time this function

					//print elements of openPositions vector into rows of WidgetTable that are currently displayed

	int TopDisplayedPrice = GetTopRowPrice();		//this is the highest price currently displayed in WidgetTable
	int BottomDisplayedPrice = GetBottomRowPrice();	//this is the lowest as above

													//	cout << "toprowprice: " << GetTopRowPrice()<< endl;
													//	cout << "bottomrowprice: " << GetBottomRowPrice()<< endl;

													//HACK: moved to inside of function to be able to reset it. create a way to only print to rows which containg any data - for speed.
													//	static set <long> usedprices;//this set contains prices that have been used in the previous printout. in this iteration of printPositions, I will use the function ClearRow to erase this row before printing new values.
													//	static set <long> notusedprices;//contains prices that have been erased at first but not filled with new values - which means they do not need to be erased again next time. this set will be used to remove values from usedprices so that we do not erase empty rows everytime

													//check if Control::rePriceWidTable has been called - if it has, erase all rows before printing anything in them:
	if (widgetTableNeedsClearAll) {
		for (int displayPrice = BottomDisplayedPrice; displayPrice <= TopDisplayedPrice; displayPrice++) {
			ClearRow(RowOfPrice(displayPrice));
			widgetTableNeedsClearAll = false;
			usedprices.clear();
			notusedprices.clear();
		}
	}
	//first, erase all values from rows that have been printed into last time:
	if (usedprices.size() > 0)
	{
		for (long price : usedprices)
		{
			ClearRow(RowOfPrice(price));
		}
	}

	try
	{
		//populate the cells in WidgetTable with values:
		for (int displayPrice = BottomDisplayedPrice; displayPrice <= TopDisplayedPrice; displayPrice++)
		{
			try { openPositions->at(displayPrice).open_amount; }
			catch (...) {
				std::cout << "Out of range error in: \nvoid WidgetTable::printPositions(const std::vector <MikePosition> *openPositions,	const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice)" << std::endl;
				break;
			}

			//FLTK requires that I pass what I want to print into the cells as a char *:
			char buffer[50];

			//HACK: below now works. trouble with it before
			//check if that position is active. if not, add this price to the notusedprices set
			if (openPositions->at(displayPrice).isActive) {
				//	cout << "\n position at price: " << displayPrice << " is active. printing." << endl;

				//add this price to usedprices set - to make sure to ClearRow next time before printing new values
				usedprices.insert(displayPrice);

				//find the cell displaying OPEN POSITION at displayprice:
				Fl_Input * openPosCell = (Fl_Input*)GetElement(RowOfPrice(displayPrice), openPosCol);

				//print the open postion for displayPrice from openPositions vector to this cell:	
				snprintf(buffer, 40, "%d", (openPositions->at(displayPrice).open_amount));
				if (openPositions->at(displayPrice).open_amount != 0) {
					openPosCell->textsize(14);
					openPosCell->value(buffer);
				}
				else
					openPosCell->value("");

				//same for OPEN PL at displayprice:
				Fl_Input * openPLCell = (Fl_Input*)GetElement(RowOfPrice(displayPrice), openPLCol);
				snprintf(buffer, 40, "%d", (openPositions->at(displayPrice).open_pl));
				openPLCell->value(buffer);

				//same for CLOSED PL at displayprice:
				Fl_Input * closedPLCell = (Fl_Input*)GetElement(RowOfPrice(displayPrice), closedPLCol);
				snprintf(buffer, 40, "%d", (openPositions->at(displayPrice).closed_pl));
				closedPLCell->value(buffer);

				//same for TOTAL PL at displayprice:
				Fl_Input * totalPLcell = (Fl_Input*)GetElement(RowOfPrice(displayPrice), totalPLCol);
				snprintf(buffer, 40, "%d", (openPositions->at(displayPrice).total_pl));
				totalPLcell->value(buffer);

			}
			else {
				notusedprices.insert(displayPrice);//mark this price for deletion at this pass. if there are active orders at this price, it will be removed from the set below when printing out orders and this price will not be removed from usedprices set when cleaning up at the end of this function. if there are no active orders at this price, then at the end of this function this displayPrice will get removed from the prices which need to be cleared out before printing.
			}



		printorders:
			//Print the open orders for this price:
			//Buy Limit Orders:
			if (openOrdersAtPrice->at(displayPrice).buyLimitAmount) {//print only prices with active orders
				Fl_Input * buyLMTOrder = (Fl_Input*)GetElement(RowOfPrice(displayPrice), buyLimitOrderCol);
				snprintf(buffer, 40, "%d", (openOrdersAtPrice->at(displayPrice).buyLimitAmount));
				buyLMTOrder->value(buffer);
				notusedprices.erase(displayPrice);
				usedprices.insert(displayPrice);
			}
			//Buy Stop Orders:
			if (openOrdersAtPrice->at(displayPrice).buyStopAmount) {//print only prices with active orders
				Fl_Input * buySTPOrder = (Fl_Input*)GetElement(RowOfPrice(displayPrice), buyStopOrderCol);
				snprintf(buffer, 40, "%d", (openOrdersAtPrice->at(displayPrice).buyStopAmount));
				buySTPOrder->value(buffer);
				notusedprices.erase(displayPrice);
				usedprices.insert(displayPrice);
			}

			//Sell Limit Orders:
			if (openOrdersAtPrice->at(displayPrice).sellLimitAmount) {
				Fl_Input * sellLMTOrder = (Fl_Input*)GetElement(RowOfPrice(displayPrice), sellLimitOrderCol);
				snprintf(buffer, 40, "%d", (openOrdersAtPrice->at(displayPrice).sellLimitAmount));
				sellLMTOrder->value(buffer);
				notusedprices.erase(displayPrice);
				usedprices.insert(displayPrice);
			}
			//Sell Stop Orders:
			if (openOrdersAtPrice->at(displayPrice).sellStopAmount) {
				Fl_Input * sellSTPOrder = (Fl_Input*)GetElement(RowOfPrice(displayPrice), sellStopOrderCol);
				snprintf(buffer, 40, "%d", (openOrdersAtPrice->at(displayPrice).sellStopAmount));
				sellSTPOrder->value(buffer);
				notusedprices.erase(displayPrice);
				usedprices.insert(displayPrice);
			}
		}
	}
	catch (...)
	{
		cout << "Error in WidgetTable::printPositions function!" << endl;
		return;
	}

	//clean things up. go through all prices stored in notusedprices and remove those prices from usedprices:
	try
	{

		if (notusedprices.size() > 0)
		{
			for (long price : notusedprices) usedprices.erase(price);
		}

		notusedprices.clear();

	}
	catch (...)
	{
		cout << "Error in WidgetTable::printPositions function!" << endl;
		return;
	}
}

void WidgetTable::PopPriceCol(/*WidgetTable * myTable*/) //populates the Price column with prices based on current TopRowPrice
{

	int PriceCol = this->priceCol;	//indicates in which column prices are to be printed - 
									//change this as neccessary if design changes made to WidgetTable
	int PriceToPrint;
	//print prices in rows from 0 to last

	for (int row = 0; row < table_rows; row++)
	{
		PriceToPrint = TopRowPrice - row;

		Fl_Input * myCell = (Fl_Input*)GetElement(row, PriceCol);
		char ch[40];

		std::stringstream buffer;
		buffer << PriceToPrint;
		myCell->value(buffer.str().c_str());
		//myCell->label(buffer.str().c_str());

		//sprintf(ch, "%d", PriceToPrint);
		//myCell->value(ch);
		//myCell->label(ch);
		//myCell->redraw();
	}

}

void WidgetTable::setBidAskColumns()
{

	bidColumn = 6;
	askColumn = 7;
}


//   #     #          #######                               #    #  
//   #  #  # # #####     #      ##   #####  #      ######  ##   ### 
//   #  #  # # #    #    #     #  #  #    # #      #      # #    #  
//   #  #  # # #    #    #    #    # #####  #      #####    #       
//   #  #  # # #    #    #    ###### #    # #      #        #    #  
//   #  #  # # #    #    #    #    # #    # #      #        #   ### 
//    ## ##  # #####     #    #    # #####  ###### ###### #####  #  
//                                                                  

//WidTable1::WidTable1(int x, int y, int w, int h, const char * l) : WidgetTable(x, y, w, h, l)
//{
//}
//
//void WidTable1::virtButtonCb(Fl_Widget * w, void * p)
//{
//	using namespace std;
//	cout << "WidTable1 callback called" << endl;
//}







