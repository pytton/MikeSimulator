#ifndef _WidgetTable_H_INCLUDED_
#define _WidgetTable_H_INCLUDED_

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <set>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Text_Display.H>


class MikeSimulator;
class UserInterface;
class MikePosition;
class MikeOrdersAtPrice;
class Control;

//WigetTable - table with cells drawed inside it
class WidgetTable : public Fl_Table_Row		
{
protected:
	void draw_cell(TableContext context, int R = 0, int C = 0, int X = 0, int Y = 0, int W = 0, int H = 0);	//supplied from example - dont know how this works
	
public:
	//constructor:
	WidgetTable(
		int x, int y, int w, int h, const char *l,
		UserInterface * pUserInterface,
		int top_row_price,
		int number_rows,

		int number_cols /*= 15*/,	/*how many columns in the table?*/
		int how_many_cols_are_buttons = 5 ,	/*how many columns are buttons?*/
		std::vector <std::string> col_names = { "" },	/*names of col headers*/
		std::vector <std::string> button_names = { "" }	//names of buttons
		
		);
	WidgetTable(int x, int y, int w, int h, const char * l, void * pControl, int top_row_price, int number_rows, int number_cols, int how_many_cols_are_buttons, std::vector<std::string> col_names, std::vector<std::string> button_names, short tabletype, short windownumber);
	WidgetTable(int x, int y, int w, int h, const char *l);//not currently used

	//TODO: Make a destructor which erases all the objects in the table	

	Fl_Widget * GetElement(int nRow, int nCol);	//returns a pointer to the cell in the table at nRow nCol
public:
	void WidgetTable::PopPriceCol(/*WidgetTable * myTable*/); //populates the Price column with prices based on current TopRowPrice
	void ClearColumn(int column);	//clears provided column of all text that might have been left behind by the previous draw - for use with Control::rePriceWidTable
	void ClearRow(int row);	//as above, but for clearing a row
	
	int RowOfPrice(long price);	//given price - returns the row in which that price is displayed in WidgetTable
	long PriceOfRow(int row);	//given the row - returns what price is currently printed in that row


	//PRINTERS:
	//print string in row/col. row 0 is first row
	void printInTable(int row, int col, std::string text);	//row = 0 is first row!
	//print the bid and ask prices if such columns exist:
	virtual void printBidAsk(long bid, long ask) {}	//empty now. do I need this?
	virtual void printPositions(const std::vector <MikePosition> *openPositions) {}
	virtual void printPositions(const std::vector <MikePosition> *openPositions,
		const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice);


	//GETTERS:
	inline int GetRows(){return table_rows;}
	inline int GetCols(){return table_cols;}
	inline int GetTopRowPrice() { return TopRowPrice; }
	inline int GetBottomRowPrice() { return (GetTopRowPrice() - GetRows() + 1); }
	inline void SetTopRowPrice(int value) { TopRowPrice = value; }
	inline std::vector <std::string> * GetColNames() { return &col_names; }
	virtual inline short GetBidCol(){ return bidColumn; }
	virtual inline short GetAskCol(){ return askColumn; }

	//SETTERS:
	virtual void SetColumnnWidth(short width) { columnWidth = width; }

private:
	//members:
	int table_rows, table_cols;
	int ButtonColsNumber;	//how many columns are buttons?
	int TopRowPrice;		//the price at the first row on top - used to determine which positions to display
	UserInterface * ptr_to_UserInterface;	//stores a pointer to window in which table is constructed. null at first. has to be set from outside.
	Control * ptrControl;
	short tabletype;//HACK: decides what the callback function will call to: 0 - it will use UserInterface * ptr_to_UserInterface; 1 - it will use Control * ptrControl;
	std::vector <std::string> col_names;	//needed by void ColHeaderText(char * s, int C)
private:
	//for printing out bid/ask in the right column:
	virtual void setBidAskColumns();
	
	//below indexes for use by WidgetTable::printPositions. they need to be reset once Control::rePriceWidTable is called so that they remain valid:
	std::set <long> usedprices;//this set contains prices that have been used in the previous printout. in this iteration of printPositions, I will use the function ClearRow to erase this row before printing new values.
	std::set <long> notusedprices;//contains prices that have been erased at first but not filled with new values - which means they do not need to be erased again next time. this set will be used to remove values from usedprices so that we do not erase empty rows everytime
public:
	bool widgetTableNeedsClearAll = true;//this is to be set once Control::rePriceWidTable is called so that the printout does not get messed up. It tells WidgetTable to clear all the rows before printing in new data.
private:
	//helper functions:
	UserInterface * GetUserInterface() { return	ptr_to_UserInterface; }	//stores a pointer to window in which table is constructed. null at first. has to be set from outside.
	Control * GetControl() { return ptrControl; }
	void SetSize(int newrows, int newcols, WidgetTable * mytable, /*std::vector <std::string> col_names = { "" },*/ std::vector<std::string> button_names = { "" });	//fills the table with cells:
	virtual void ColHeaderText(char * s, int C);	//defines text of column headers

	inline void SetRows(int numRows){table_rows = numRows;}
	inline void SetCols(int numCol){table_cols = numCol;}

	//callbacks:
	static void button_cb(Fl_Widget *w, void * p);	//callbacks in fltk have to be static

	//below describes which column number shows what kind of data?
	//eg. bidcolumn = 6 and askColumn = 7 mean that the bid is
	//printed in column 6 and ask is printed in column 7:
	short
		priceCol = 5,
		bidColumn = 6,
		askColumn = 7,
		openPosCol = 12,
		openPLCol = 13,
		closedPLCol = 14,
		totalPLCol = 15,
		buyLimitOrderCol = 8,
		buyStopOrderCol = 9,
		sellLimitOrderCol = 10,
		sellStopOrderCol = 11,
		columnWidth = 55,
		windownumber = 0;//for callbacks sent to Control - to tell which window its coming from. must be set in constructor
	friend class UserInterface;

};

//class SimpleTable : public WidgetTable
//{
//
//};



class My_fl_button : public  Fl_Button  //with location of button in Fl_Table
{
public:
	//below determines where in the Fl_Table the button is located
	//needs to be set inside WidgetTable::SetSize function
//private:
protected:
	int x_pos;	//column of button -> 0 is the first
public:
	int y_pos;	//row of button -> 0 is the first

				//constructor:
	My_fl_button(int x, int y, int w, int h, const char *l);	//x_pos y_pos set to 0 by default
	inline int getXpos() { return x_pos; }
	inline int getYpos() { return y_pos; }
	
	inline void setYpos(int y) { y_pos = y; }
	inline void setXpos(int x) { x_pos = x; }

};


#endif //_WidgetTable_H_INCLUDED_