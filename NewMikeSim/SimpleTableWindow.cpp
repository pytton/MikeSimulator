#include "SimpleTableWindow.h"
#include "WidgetTable.h"
#include "Control.h"


SimpleTableWindow::SimpleTableWindow(Control * ptrControl, short windownumber)
{
	mwindow1->begin();
	delete mTable;

	int top_row_price = 250,
		number_rows = 20,
		number_cols = 5,
		how_many_cols_are_buttons = 2,
		tableCallbackType = 1;//need to tell WidgetTable that callbacks will be sent to Control, not UserInterface

	std::vector <std::string>  col_names = { "Description", "Value" };
	std::vector <std::string>  button_names = { "EMPTY", "SECOND" };

	widTable = new WidgetTable(5, 5, 940, 630, "widgettable", ptrControl, top_row_price, number_rows,
		number_cols, how_many_cols_are_buttons, col_names, button_names, tableCallbackType, windownumber);

	
	mwindow1->end();
	mwindow1->label("experimental");

	widTable->SetColumnnWidth(90);
	
	////std::vector <std::string> * pColNames = widTable->GetColNames();

	////pColNames->clear();
	////pColNames->push_back("Test1");



	widTable->redraw();
	mwindow1->show();
	//widTable->printInTable(0, 0, "testing new");

}


SimpleTableWindow::~SimpleTableWindow()
{
}

void SimpleTableWindow::rePriceWidTable(long priceattoprow)
//UNDER CONSTRUCTION
//Updates prices displayed in WidgetTable to between 100 above and below
//current bid price in Data class
//Updates slider in UserInterface to current Bid price
{	WidgetTable * pTable = widTable;

	pTable->SetTopRowPrice(priceattoprow);
	//draw the new widget table:
	this->mwindow1->hide();
	this->mwindow1->redraw();
	this->mwindow1->show();



	//populate price column with prices:

	//pUI->GetTable()->ClearColumn(6);	//clear the bid and ask columns
	//pUI->GetTable()->ClearColumn(7);
	//pUI->GetTable()->PopPriceCol();
}