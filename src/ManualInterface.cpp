#include "ManualInterface.h"
#include "WidgetTable.h"
//#include "Control.h"

ManualInterface::ManualInterface(Control * control, double starting_bid_price ) : 
	UserInterface(control, starting_bid_price)
{
	using namespace std;
	this->SetColButNames( col_names,  button_names);
	cout << "Manual Interface created" << endl;

	m_window1->label("Manual Interface");

	//below is copy/paste from UserInterface Constructor with small changes - experiment
	int numberOfColumns = 15;
	int numberOfButtoncolumns = 5;
	m_window1->begin();

	//******************************************************************************************
	//creating WidgetTable:
	delete m_pTable;	//deleting old table supplied by fluid

	//name the column headers and button names in WidgetTable:
	SetColButNames(col_names, button_names);
	//construct new WidgetTable:
	int top_row_price = bid_price + 100, number_rows = 200, 
		number_cols = numberOfColumns,
		how_many_cols_are_buttons = numberOfButtoncolumns;
	m_pTable = new WidgetTable(65, 0, 900, 495, "widgettable", this, top_row_price, number_rows,
		number_cols, how_many_cols_are_buttons, col_names, button_names);


	m_window1->end();
	//******************************************************************************************

	m_window1->hide();
	m_window1->redraw();
	m_window1->show();


}


ManualInterface::~ManualInterface()
{
}

//UNCOMMENT AND CHANGE IF NEEDED:
//void ManualInterface::SetColButNames(std::vector<std::string>& col_names, std::vector<std::string>& button_names)
//{
//	using namespace std;
//	cout << "ManualInterface SetColeButNames called" << endl;
//
//	col_names.clear();
//
//	col_names.push_back("MANUALINTERFACE");
//	//col_names.push_back("MANUALINTERFACE");
//	//col_names.push_back("MANUALINTERFACE");
//	//col_names.push_back("MANUALINTERFACE");
//	//col_names.push_back("MANUALINTERFACE");
//
//	button_names.clear();
//
//	button_names.push_back("tryout");
//
//}
