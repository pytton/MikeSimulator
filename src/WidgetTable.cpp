#include <sstream> //replaces cout
#include <string>
#include "UserInterface.h"
//#include "Display.h"
//#include "MikeSimulator.h"
#include "WidgetTable.h"

#define PRICECOLUMN 5 //in which column should the price be printed? Used by PopPriceCol


//WIDGETTABLE:
//CONSTRUCTOR:

WidgetTable::WidgetTable(
	int x, int y, int w, int h, const char *l,
	UserInterface * pUserInterface,
	int top_row_price,
	int number_rows,

	int number_cols,	/*how many columns in the table?*/
	int how_many_cols_are_buttons,	/*how many columns are buttons?*/
	std::vector <std::string> col_names,	/*names of col headers*/
	std::vector <std::string> button_names	//names of buttons
	) : Fl_Table_Row(x, y, w, h, l)
{
	ptr_to_UserInterface = pUserInterface;
	TopRowPrice = top_row_price;
	ButtonColsNumber = how_many_cols_are_buttons;	//how many columns of buttons?
	this->col_names = col_names;	//this has to be set for SetSize and ColHeaderText functions

	//	table_rows, table_cols = 20;
	col_header(1);
	col_resize(1);
	col_header_height(40);
	row_header(1);
	row_resize(0);
	row_header_width(40);
	end();

	//using namespace std;
	//string buf;
	//cin >> buf;
	//button_names[2] = buf;

	SetCols(number_cols);
	SetRows(number_rows);
	SetSize(GetRows(), GetCols(), this, /*col_names,*/ button_names);		//this needs to be called to construct all the cells of WidgetTable
	//Sleep(1000);
	//PopPriceCol(this);	//fill the price column with prices
}


//CALLBACKS:
void WidgetTable::button_cb(Fl_Widget *w, void * p)
{
	//this callback is set inside the WidgetTable::SetSize function!!
	My_fl_button * myButton = (My_fl_button*)w;		//myButton is the button that was pressed
	WidgetTable * thisTable = (WidgetTable*)p;		//thisTable is the table in which the button was pressed
//	UserInterface * myUI = thisTable->GetUserInterface();	//myUI is the UserInterface in which the table is created



	//send the information to Control:
	//What price level was pressed?:
	int rowPressed = myButton->y_pos;		//this is the row in which the button was pressed
	long price = thisTable->PriceOfRow(rowPressed);
	int colPressed = myButton->x_pos;
	
	thisTable->ptr_to_UserInterface->CallbkWidTable(rowPressed, colPressed, price);
	
	
//	thisTable->ptr_to_UserInterface->GetControl()->ManualOrder(OrderType, price);
	//send the information to Control
	//below - print out the price corresponding to the row in which the button was pressed:

//std::cout << "\nRow pressed: " << rowPressed << std::endl;
//std::cout << "\nCorresponding price: " << thisTable->PriceOfRow(rowPressed) << std::endl;
//	std::cout << '\n' << sizeof(long) << " " << sizeof(long long) << " " << sizeof(double);


	//OLD CODE:
	////	fprintf(stderr, "BUTTON: %s\n", (const char*)w->label());
	//	
	//	WidgetTable * myTable = static_cast<WidgetTable*>(p);		//WidgetTable * myTable = (WidgetTable*)(p);
	//	UserInterface * myUserInterface = static_cast<UserInterface*>(myTable->ptr_to_UserInterface);		//UserInterface * myUserInterface = (UserInterface*)(myTable->ptr_to_UserInterface);
	//	int  myRow = 8, myColumn = 8;
	//	Fl_Widget * myWidget = myTable->GetElement(myRow, myColumn);
	//	Fl_Input * myCell = dynamic_cast<Fl_Input*>(myWidget);
	//
	//	myWidget = myTable->GetElement(myRow, myColumn);
	//
	//	My_fl_button * myFlButton = (My_fl_button*)w;
	//	//printout the x y positions of the button pressed:
	//	std::cout << std::endl << myFlButton->x_pos << std::endl;
	//	std::cout << myFlButton->y_pos << std::endl;
	//
	//	myCell = dynamic_cast<Fl_Input*>(myWidget);
	//
	//	myCell->value("try");
	//	myUserInterface->textDisplayString << "button pressed" << std::endl;
	//	myUserInterface->textBuffer->text((myUserInterface->textDisplayString).str().c_str());
	//
	//	myTable->printInTable(6, 6, "text"/*, myTable*/);

}

//HELPLERS:
void WidgetTable::printInTable(int row, int col, std::string text)//row = 0 is first row!
{
	WidgetTable * myTable = this;

	//	WidgetTable * myTable = myWidgetPointer;

	//first, make sure row and col are not bigger than the size of the table:
	//if they are - it will be printed at the edgeusing this line:
	//row = myTable->GetRows() - 1; etc...


	if (row >= myTable->GetRows()) {
		std::cout << "\nPrint attempt in row outside of WidgetTable";
		row = myTable->GetRows() - 1;
	}
	if (col >= myTable->GetCols()) {
		std::cout << "\nPrint attempt in col outside of WidgetTable";
		/*myCol*/col = myTable->GetCols() - 1;
	}
	if (row < 0) {
		std::cout << "\nPrint attempt in row outside of WidgetTable";
		row = 0;
	}
	if (col < myTable->ButtonColsNumber) {
		std::cout << "\nPrint attempt in col outside of WidgetTable";
		col = myTable->ButtonColsNumber;	//make sure we are not printing in rows meant for buttons!
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
Fl_Widget * WidgetTable::GetElement(int nRow, int nCol)
{//used to get a pointer to an element of WidgetTable with X Y coordinates nRow nCol
 //nRow = 0 -> points to FIRST row; nCol = 0 -> points to col number 1!
 //remember the first columns are for buttons, not Fl_Input!
 //watch for off by one errors
	int numCol = this->cols();
	int nIndex = nRow * numCol + nCol;
	return this->child(nIndex);
}
int WidgetTable::RowOfPrice(long price)
{
	int rowToReturn = TopRowPrice - price;
	return rowToReturn;
}   //given price - returns the row in which that price is displayed in WidgetTable
long WidgetTable::PriceOfRow(int row)
{
	long price = TopRowPrice - row;

	return price;
}	 //given the row - returns what price is currently printed in that row
void WidgetTable::PopPriceCol(/*WidgetTable * myTable*/) //populates the Price column with prices based on current TopRowPrice
{

	int PriceCol = PRICECOLUMN;	//indicates in which column prices are to be printed - 
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

void WidgetTable::ClearColumn(int column)
{
	int howManyRows = GetRows();
	for (int i = 0; i < howManyRows; ++i)
	{
		Fl_Input * myCell = (Fl_Input*)GetElement(i, column);

		myCell->value("");
	}
}

void WidgetTable::ClearRow(int row)
{
	int startCol = ButtonColsNumber - 1; //first column is zero. ButtonColsNumber gives number of Cols that are buttons
	int endCol = GetCols();

	for (int i = startCol; i < endCol; ++i)
	{
		Fl_Input * myCell = (Fl_Input*)GetElement(row, i);

		myCell->value("");
	}
}

//below fills the table with objects:
//TODO: make sure old Fl_Input and My_fl_button objects are destroyed
//when this is called more than once
void WidgetTable::SetSize(int newrows, int newcols, WidgetTable * mytable, /*std::vector<std::string> col_names,*/ std::vector<std::string> button_names)
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
					Fl_Input *in = new Fl_Input(X, Y, W, H);
					//in->value(s);
					in->textsize(10);	//sets the size of the font					
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

					//old way of assigning labels - before being provided with button_names vector
					//if (c == 0) butt->label("CXL");
					//if (c == 1) butt->label("B LMT");
					//if (c == 2) butt->label("B STP");
					//if (c == 3) butt->label("S LMT");
					//if (c == 4) butt->label("S STP");
					butt->x_pos = c;	//set the col
					butt->y_pos = r;	//set the row
				}

			}
		}
	}
	end();
	//below doesnt work:
	//	mytable->PopPriceCol(this);
	//	PopPriceCol();	//populate price column with prices

}

//used to construct WidgetTable - I didn't write this, only modified it for my needs
void WidgetTable::draw_cell(TableContext context,
	int R, int C, int X, int Y, int W, int H)
{
	switch (context)
	{
	case CONTEXT_STARTPAGE:
		fl_font(FL_HELVETICA, 9);		// font used by all headers
		col_width_all(55);				// sets the width of the columns
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
		}
		fl_pop_clip();
		return;

	case CONTEXT_COL_HEADER:
		fl_push_clip(X, Y, W, H);
		{	//set the width of a single column:
			//this doesnt work :(	
			//if (C == 1)
			//{
			//	col_width(C, 30);
			//	init_sizes();
			//	Fl::redraw();
			//}

			//experimenting:
			//			std::cout << "draw cell called" << std::endl;

			fl_font(FL_HELVETICA, 11);
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
void WidgetTable::ColHeaderText(char * s, int C)	//defines text of column headers
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

//constructor for My_fl_button. These are buttons used inside WidgetTable which know what their position is
My_fl_button::My_fl_button(int x, int y, int w, int h, const char *l = 0)
	: Fl_Button(x, y, w, h, l), x_pos(0), y_pos(0)
{
	x_pos = 0;
	y_pos = 0;
	//x_pos and y_pos are being set inside WidgetTable::SetSize function
}
