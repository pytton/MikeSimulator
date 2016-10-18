#include "ManualInterface.h"
#include "WidgetTable.h"
//#include "Control.h"

ManualInterface::ManualInterface(
	Control * control, 
	double starting_bid_price,
	int numberOfColumns,
	int numberOfButtoncolumns
	) :
	UserInterface(
		control, 
		starting_bid_price
		//, 
		//numberOfColumns,
		//numberOfButtoncolumns
		)
{
	using namespace std;
	this->SetColButNames( col_names,  button_names);
	cout << "Manual Interface created" << endl;

	m_window1->label("Manual Interface");

	//below is copy/paste from UserInterface Constructor with small changes - experiment
//	int numberOfColumns = 15;
//	int numberOfButtoncolumns = 5;
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
void ManualInterface::SetColButNames(std::vector<std::string>& col_names, std::vector<std::string>& button_names)
{
	using namespace std;
	cout << "ManualInterface SetColeButNames called" << endl;

	col_names.clear();

	col_names.push_back("CANCEL\nORDER");
	col_names.push_back("BUY");
	col_names.push_back("BUY");
	col_names.push_back("SELL");
	col_names.push_back("SELL");
	col_names.push_back("PRICE");
	col_names.push_back("BID");
	col_names.push_back("ASK");
	col_names.push_back("ORDER\nSIZE");
	col_names.push_back("ORDER\nTYPE");
	col_names.push_back("ORDER\nPRICE");
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

//experimenting:
//void ManualInterface::printPositions(const std::vector <MikePosition> *openPositions,
//	const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice)
//{
//	std::cout << "Experimental printout from ManualInterface" << std::endl;
//}
//
//void ManualInterface::PrintAll(long totalOpenPos, long totalOpenPL, long totalClosedPL, long totalPL, long askPrice, long bidPrice, const std::vector<MikePosition>* openPositions, const std::vector<MikeOrdersAtPrice>* openOrdersAtPrice)
//{
//	std::cout << "Virtual function called! No printout!" << std::endl;
//}
