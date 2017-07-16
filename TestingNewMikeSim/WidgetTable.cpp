#include "UserInterface.h"
#include "WidgetTable.h"
#include "MikeTimer.h"
#include "MikePositionsOrders.h"
#include "Control.h"

#include <sstream> //replaces cout
#include <string>
#include <set>
#include <memory> //for whared_ptr

//   #     #          #######                             ######                        #  
//   #  #  # # #####     #      ##   #####  #      ###### #     #   ##    ####  ###### ### 
//   #  #  # # #    #    #     #  #  #    # #      #      #     #  #  #  #      #       #  
//   #  #  # # #    #    #    #    # #####  #      #####  ######  #    #  ####  #####      
//   #  #  # # #    #    #    ###### #    # #      #      #     # ######      # #       #  
//   #  #  # # #    #    #    #    # #    # #      #      #     # #    # #    # #      ### 
//    ## ##  # #####     #    #    # #####  ###### ###### ######  #    #  ####  ######  #  
//                                                                                         


//                       _                   _                   
//    ___ ___  _ __  ___| |_ _ __ _   _  ___| |_ ___  _ __ ___ _ 
//   / __/ _ \| '_ \/ __| __| '__| | | |/ __| __/ _ \| '__/ __(_)
//  | (_| (_) | | | \__ \ |_| |  | |_| | (__| || (_) | |  \__ \_ 
//   \___\___/|_| |_|___/\__|_|   \__,_|\___|\__\___/|_|  |___(_)
//                                                               

WidTableBase::WidTableBase(int x, int y, int w, int h, const char * l) : Fl_Table_Row(x, y, w, h, l)
{
}

WidTableBase::WidTableBase(int x, int y, int w, int h, const char * l,
	int top_row_price,
	int number_rows,
	int number_cols,
	int how_many_cols_are_buttons,
	std::vector<std::string> col_names,
	std::vector<std::string> button_names) : Fl_Table_Row(x, y, w, h, l)
{
	
	TopRowPrice = top_row_price;
	ButtonColsNumber = how_many_cols_are_buttons;	//how many columns of buttons?
	this->col_names = col_names;	//this has to be set for SetSize and ColHeaderText functions

	//setup the WidTable parameters:
	col_header(1);  //does the table have a header?
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
//	setBidAskColumns();

}

WidTableBase::~WidTableBase()
{
	//erase and deallocate all Fl_Input objects:
	using namespace std;
	while (sharedFlInputPointers.size()>0) {
		Fl_Input * & test = sharedFlInputPointers.top();
		
		delete test;
		
		cout << "Deleting Fl_Input at address: " << test << endl;
		//test.print();
		sharedFlInputPointers.pop();
	}
	
	
	//while (testStack.size()>0) {
	//	Test & test = testStack.top();
	//	test.print();
	//	testStack.pop();
	//}
}

//             _ _ _                _          
//    ___ __ _| | | |__   __ _  ___| | _____ _ 
//   / __/ _` | | | '_ \ / _` |/ __| |/ / __(_)
//  | (_| (_| | | | |_) | (_| | (__|   <\__ \_ 
//   \___\__,_|_|_|_.__/ \__,_|\___|_|\_\___(_)
//                                             

//this callback is set inside the WidTableBase::SetSize function!!
//FLTK requires callback functions to be static. static cannot be virtual.
//below - we simply call a PURE virtual function in WidTableBase class.
//this makes WidTableBase call whatever virtual function was implemented
//in class derived from it
void WidTableBase::button_cb(Fl_Widget *w, void * p)
{
	WidTableBase * thisTable = (WidTableBase*)p;  //thisTable is the table in which the button was pressed
	thisTable->virtButtonCb(w, p);
}

//              _       _                  
//   _ __  _ __(_)_ __ | |_ ___ _ __ ___ _ 
//  | '_ \| '__| | '_ \| __/ _ \ '__/ __(_)
//  | |_) | |  | | | | | ||  __/ |  \__ \_ 
//  | .__/|_|  |_|_| |_|\__\___|_|  |___(_)
//  |_|                                    

//main printing function. row = 0, col = 0 are the first row/col of table. you need to know how many cols are buttons
//if 3 cols are buttons (cols 0 and 1 and 2) then you should not print in cols 2 and below
//function returns without printing if attempt made to print outside the table
void WidTableBase::printInTable(int row, int col, std::string text)//row = 0 is first row!
{
	WidTableBase * myTable = this;

	//first, make sure row and col are not bigger than the size of the table:
	//if they are - function returns without printing

	if (row >= myTable->GetRows()) {
		std::cout << "\nPrint attempt in row outside of WidgetTable";
		row = myTable->GetRows() - 1;
		return;
	}
	if (col >= myTable->GetCols()) {
		std::cout << "\nPrint attempt in col outside of WidgetTable";
		/*myCol*/col = myTable->GetCols() - 1;
		return;
	}
	if (row < 0) {
		std::cout << "\nPrint attempt in row outside of WidgetTable";
		row = 0;
		return;
	}
	if (col < myTable->ButtonColsNumber) {
		std::cout << "\nPrint attempt in col outside of WidgetTable";
		col = myTable->ButtonColsNumber;	//make sure we are not printing in rows meant for buttons!
		return;
	}
	//find the cell:
	Fl_Widget * myWidget = (Fl_Widget*)(myTable->GetElement(row, col));
	Fl_Input * myCell = (Fl_Input*)(myWidget);
	//print into the cell:
	myCell->textsize(12);	//sets the size of the font

	std::stringstream buffer;
	buffer << text;
	myCell->value(buffer.str().c_str());
}

//clears a single col
void WidTableBase::ClearColumn(int column)
{
	using namespace std;
	if (column <0) { cout << "col error in WidTableBase::ClearColumn" << endl; return; }
	if (column >= GetCols()) { cout << "col error in WidTableBase::ClearColumn" << endl; return; }
	int howManyRows = GetRows();
	for (int i = 0; i < howManyRows; ++i)
	{
		Fl_Input * myCell = (Fl_Input*)GetElement(i, column);

		myCell->value("");
	}
}

//clears a single row. returns if row is out of bounds
void WidTableBase::ClearRow(int row)
{
	using namespace std;

	if (row < 0) { cout << "row error in WidTableBase::ClearRow" << endl; return; }
	//TODO: make sure below works:
	if (row >= GetRows()) { cout << "row error in WidTableBase::ClearRow" << endl; return; }

	int startCol = ButtonColsNumber;
	if (startCol < 0) cout << "\nError in WidgetTable::ClearRow!" << endl;
	int endCol = GetCols();

	const char * pChar = "";
	if (pChar != NULL)
	{
		for (unsigned int i = startCol; i < endCol; ++i)
		{
			Fl_Input * myCell = dynamic_cast<Fl_Input*> (GetElement(row, i));
			if (myCell == NULL) { cout << "\nError in ClearTable!" << endl; break; }
			myCell->value(pChar);// this changes the private x_pos value of My_fl_button
		}
	}
}

//   _          _                       
//  | |__   ___| |_ __   ___ _ __ ___ _ 
//  | '_ \ / _ \ | '_ \ / _ \ '__/ __(_)
//  | | | |  __/ | |_) |  __/ |  \__ \_ 
//  |_| |_|\___|_| .__/ \___|_|  |___(_)
//               |_|                    

//used to get a pointer to an element of WidgetTable with X Y coordinates nRow nCol
//nRow = 0 -> points to FIRST row; nCol = 0 -> points to col number 1!
//remember the first columns are for buttons, not Fl_Input!
//watch for off by one errors
Fl_Widget * WidTableBase::GetElement(int nRow, int nCol)
{
	int numCol = this->cols();
	int nIndex = nRow * numCol + nCol;
	return this->child(nIndex);
}

int WidTableBase::RowOfPrice(long price)
{
	int rowToReturn = GetTopRowPrice() - price;
	return rowToReturn;
}   //given price - returns the row in which that price is displayed in WidgetTable

long WidTableBase::PriceOfRow(int row)
{
	long price = TopRowPrice - row;

	return price;
}	 //given the row - returns what price is currently printed in that row

//below fills the table with objects:
//TODO: make sure old Fl_Input and My_fl_button objects are destroyed
//when this is called more than once
void WidTableBase::SetSize(int newrows, int newcols, WidTableBase * mytable, /*std::vector<std::string> col_names,*/ std::vector<std::string> button_names)
{
	//this is code that was taken from an example found online.
	//not sure 100% how all of this works but modified it to
	//do what I want it to do.
	using namespace std;
	rows(newrows);
	cols(newcols);
	mytable->SetRows(newrows);
	mytable->SetCols(newcols);

	//find out for how many button and column names have been provided:
	int amount_button_names = button_names.size();
	int amount_col_names = col_names.size();
	cout << endl << "button names amount: " << amount_button_names << endl;
	cout << endl << "column names amount: " << amount_col_names << endl;

	//testing - print out all the button names:

	for (int i = 0; i < amount_button_names; ++i)
	{
		cout << button_names[i] << endl;
	}

	begin();		// start adding widgets to group
	{
		for (int r = 0; r<newrows; r++)
		{
			for (int c = 0; c<newcols; c++)
			{
				int X, Y, W, H;
				find_cell(CONTEXT_TABLE, r, c, X, Y, W, H);
				char s[40];
				//below decides what is put into table:
				//r is row and c is col
				if (c >= mytable->ButtonColsNumber/*c != 0 && c != 1 && c != 2 && c != 3*/) //this used to be ( c & 1) -bitwise comparison				
				{
					// Create the input widgets
					//sprintf(s, "%d/%d", r, c);
					//HACK: experimenting with shared_ptr - revert to old if issues arise:

					//old commented out way:
					Fl_Input *in = new Fl_Input(X, Y, W, H);
					
					//new way using shared_ptr:
					//std::shared_ptr<Fl_Input> in = std::make_shared<Fl_Input>(X, Y, W, H);

					sharedFlInputPointers.push(in);

					//std::shared_ptr<Fl_Input> in ( new Fl_Input(X, Y, W, H));

					//std::shared_ptr<int> foo2(new int(10));
					//	std::shared_ptr<int> foo = std::make_shared<int>(10);

					in->textsize(9);//sets the size of the font					
				}
				else
				{
					// Create the light buttons

					//naming buttons using supplied button_names vector:
					string buf;
					if (!(c >= button_names.size()) && button_names.size() >0)
					{
						buf = button_names[c];
					}
					else { buf = "Default"; }
					snprintf(s, 39, buf.c_str());

					//use this tested way if the above way gives trouble:
					//stringstream tempText;
					//if (button_names.size() >= c){tempText << button_names[c]; }
					//else { tempText << "noName"; }
					//snprintf(s, 39, tempText.str().c_str());
					//
					//original way of naming buttons:
					//sprintf(s, "%d/%d ", r, c);

					//create the button:
					My_fl_button *butt = new My_fl_button(X, Y, W, H, strdup(s));
					//Fl_Light_Button *butt = new Fl_Light_Button(X, Y, W, H, strdup(s));
					butt->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
					butt->callback(button_cb, (void*)mytable);
					//butt->value(((r + c * 2) & 4) ? 1 : 0);	//this sets the light on or off for Fl_Light_Button

					butt->setXpos(c);	//set the col
					butt->y_pos = r;	//set the row
				}

			}
		}
	}
	end();
}

//used to construct WidgetTable - I didn't write this, only modified it for my needs
void WidTableBase::draw_cell(TableContext context,
	int R, int C, int X, int Y, int W, int H)
{
	switch (context)
	{
	case CONTEXT_STARTPAGE:
		fl_font(FL_HELVETICA, 9);		// font used by all headers
		col_width_all(columnWidth);				//HACK: sets the width of the columns
		row_height_all(18);
		break;

	case CONTEXT_RC_RESIZE:
	{
		int X, Y, W, H;
		int index = 0;
		for (int r = 0; r<rows(); r++)
		{
			for (int c = 0; c<cols(); c++)
			{
				if (index >= children()) break;
				find_cell(CONTEXT_TABLE, r, c, X, Y, W, H);
				child(index++)->resize(X, Y, W, H);
			}
		}
		init_sizes();			// tell group children resized
		return;
	}

	case CONTEXT_ROW_HEADER:
		fl_push_clip(X, Y, W, H);
		{
			static char s[40];
			sprintf(s, "%d", TopRowPrice - R);
			fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
			fl_color(FL_BLACK);
			fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
			fl_font(FL_HELVETICA, 9);
		}
		fl_pop_clip();
		return;

	case CONTEXT_COL_HEADER:
		fl_push_clip(X, Y, W, H);
		{	fl_font(FL_HELVETICA, 9);
		static char s[40];
		//below decide what is printed in column headers:
		ColHeaderText(s, C);	//this function performs commented out code below

								//if (C == 0)
								//{
								//	sprintf(s, "BUY");
								//}
								//else
								//{
								//	sprintf(s, "Col %d", C);
								//}

		fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, col_header_color());
		fl_color(FL_BLACK);
		fl_draw(s, X, Y, W, H, /*FL_ALIGN_CENTER,*/ FL_ALIGN_WRAP);	//modified to use wrap
		}

		fl_pop_clip();
		return;

	case CONTEXT_CELL:
		return;		// fltk handles drawing the widgets

	default:
		return;
	}
}

//defines text of column headers
void WidTableBase::ColHeaderText(char * s, int C)
{
	//this function is called by 'draw_cell' - which is part of FLTK
	//I cannot alter the way draw_cell is called to pass parameters
	//that is why this function REQUIRES that the following things be set
	//inside the WidgetTable class before it is called:
	//
	//std::vector <std::string> col_names
	//int table_cols
	//
	//it pulls that data from WidgetTable!!!!!!

	static bool errorcheck = 0;


	using namespace std;
	//first, check that we have col_names:
	//cout << endl;
	if (col_names.size() > 0)
	{
		//	cout << "Working on this function - finish it!" << endl;

		if (C< col_names.size()) sprintf(s, (col_names[C]).c_str());
		else
		{
			sprintf(s, "Col %d", C);

			if (!errorcheck)
			{
				cout << "Names not provided for all columns! Using default." << endl;
				errorcheck = 1;
			}
		}

	}
	else
	{	//old code kept as a fallback - in case col_names
		//vector is empty
		switch (C)
		{
		case 0:
			sprintf(s, "CANCEL\nORDER");
			break;
		case 1:
			sprintf(s, "BUY");
			break;
		case 2:
			sprintf(s, "BUY");
			break;
		case 3:
			sprintf(s, "SELL");
			break;
		case 4:
			sprintf(s, "SELL");
			break;
		case 5:
			sprintf(s, "PRICE");
			break;
		case 6:
			sprintf(s, "BID");
			break;
		case 7:
			sprintf(s, "ASK");
			break;
		case 8:
			sprintf(s, "ORDER\nSIZE");
			break;
		case 9:
			sprintf(s, "ORDER\nTYPE");
			break;
		case 10:
			sprintf(s, "ORDER\nPRICE");
			break;
		case 11:
			sprintf(s, "OPEN\nPOSITION");
			break;
		case 12:
			sprintf(s, "OPEN\nP/L");
			break;
		case 13:
			sprintf(s, "CLOSED\nP/L");
			break;
		case 14:
			sprintf(s, "TOTAL\nP/L");
			break;
		default:
			sprintf(s, "Col %d", C);
		}
	}
}



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

WidTable1::WidTable1(int x, int y, int w, int h, const char * l) : WidgetTable(x, y, w, h, l)
{
}

void WidTable1::virtButtonCb(Fl_Widget * w, void * p)
{
	using namespace std;
	cout << "WidTable1 callback called" << endl;
}


//   #     #                                                                              #  
//   ##   ## #   #         ###### #              #####  #    # ##### #####  ####  #    # ### 
//   # # # #  # #          #      #              #    # #    #   #     #   #    # ##   #  #  
//   #  #  #   #           #####  #              #####  #    #   #     #   #    # # #  #     
//   #     #   #           #      #              #    # #    #   #     #   #    # #  # #  #  
//   #     #   #           #      #              #    # #    #   #     #   #    # #   ## ### 
//   #     #   #           #      ######         #####   ####    #     #    ####  #    #  #  
//                 #######               #######                                             

//constructor for My_fl_button. These are buttons used inside WidgetTable which know what their position is
My_fl_button::My_fl_button(int x, int y, int w, int h, const char *l = 0)
	: Fl_Button(x, y, w, h, l), x_pos(0), y_pos(0)
{
	x_pos = 0;
	y_pos = 0;
	//x_pos and y_pos are being set inside WidgetTable::SetSize function
}




