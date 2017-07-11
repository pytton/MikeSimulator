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




//TODO: Finish moving members/methods from WidgetTable to WidTableBase
//     ___ _____     __  _____  __           _____         _____  __    
//    / __\\_   \ /\ \ \ \_   \/ _\  /\  /\ /__   \ /\  /\ \_   \/ _\ _ 
//   / _\   / /\//  \/ /  / /\/\ \  / /_/ /   / /\// /_/ /  / /\/\ \ (_)
//  / /  /\/ /_ / /\  //\/ /_  _\ \/ __  /   / /  / __  //\/ /_  _\ \ _ 
//  \/   \____/ \_\ \/ \____/  \__/\/ /_/    \/   \/ /_/ \____/  \__/(_)
//                                                                      


//base class of all WidgetTables
//never use this class. derive from it to get what you need
class WidTableBase : public Fl_Table_Row
{
protected:
	WidTableBase(int x, int y, int w, int h, const char *l);


	//                _    _                        __            _    _                       
	//    __ _   ___ | |_ | |_   ___  _ __  ___    / / ___   ___ | |_ | |_   ___  _ __  ___  _ 
	//   / _` | / _ \| __|| __| / _ \| '__|/ __|  / / / __| / _ \| __|| __| / _ \| '__|/ __|(_)
	//  | (_| ||  __/| |_ | |_ |  __/| |   \__ \ / /  \__ \|  __/| |_ | |_ |  __/| |   \__ \ _ 
	//   \__, | \___| \__| \__| \___||_|   |___//_/   |___/ \___| \__| \__| \___||_|   |___/(_)
	//   |___/                                                                     
	//GETTERS:
	inline int GetRows() { return table_rows; }
	inline int GetCols() { return table_cols; }


	static void button_cb(Fl_Widget *w, void * p);	//callbacks in fltk have to be static
	virtual void virtButtonCb(Fl_Widget *w, void * p) = 0;

	//                               _                         
	//   _ __ ___    ___  _ __ ___  | |__    ___  _ __  ___  _ 
	//  | '_ ` _ \  / _ \| '_ ` _ \ | '_ \  / _ \| '__|/ __|(_)
	//  | | | | | ||  __/| | | | | || |_) ||  __/| |   \__ \ _ 
	//  |_| |_| |_| \___||_| |_| |_||_.__/  \___||_|   |___/(_)
	//  
	int table_rows, table_cols;
	int ButtonColsNumber;	//how many columns are buttons?
	int TopRowPrice;		//the price at the first row on top - used to determine which positions to display
	short tabletype;//HACK: decides what the callback function will call to: 0 - it will use UserInterface * ptr_to_UserInterface; 1 - it will use Control * ptrControl;
	std::vector <std::string> col_names;	//needed by void ColHeaderText(char * s, int C)

	//   _            _                         
	//  | |__    ___ | | _ __    ___  _ __  ___ 
	//  | '_ \  / _ \| || '_ \  / _ \| '__|/ __|
	//  | | | ||  __/| || |_) ||  __/| |   \__ \
	//  |_| |_| \___||_|| .__/  \___||_|   |___/
	//                  |_|                     
	//helper functions:
	inline void SetRows(int numRows) { table_rows = numRows; }
	inline void SetCols(int numCol) { table_cols = numCol; }
	Fl_Widget * GetElement(int nRow, int nCol);	//returns a pointer to the cell in the table at nRow nCol
												//supplied from example - dont know how this works
	void SetSize(int newrows, int newcols, WidTableBase * mytable, std::vector<std::string> button_names = { "" });
											
};


class MikeSimulator;
class UserInterface;
class MikePosition;
class MikeOrdersAtPrice;
class Control;
class WidTable1;



//WigetTable - table with cells drawed inside it
class WidgetTable : public WidTableBase
{	friend class UserInterface;
	friend class WidTable1;

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
	WidgetTable(
		int x, int y, int w, int h, const char * l,
		void * pControl,
		int top_row_price,
		int number_rows,
		int number_cols,
		int how_many_cols_are_buttons,
		std::vector<std::string> col_names,
		std::vector<std::string> button_names,
		short tableCallbackType,
		short windownumber);
	WidgetTable(int x, int y, int w, int h, const char *l);//not currently used
	WidgetTable();

	//TODO: Make a destructor which erases all the objects in the table	

	bool widgetTableNeedsClearAll = true;//this is to be set once Control::rePriceWidTable is called so that the printout does not get messed up. It tells WidgetTable to clear all the rows before printing in new data.

public:
//                _         _                   
//   _ __   _ __ (_) _ __  | |_  ___  _ __  ___ 
//  | '_ \ | '__|| || '_ \ | __|/ _ \| '__|/ __|
//  | |_) || |   | || | | || |_|  __/| |   \__ \
//  | .__/ |_|   |_||_| |_| \__|\___||_|   |___/
//  |_|                                         

	//print string in row/col. row 0 is first row
	virtual void printInTable(int row, int col, std::string text);	//row = 0 is first row!
	//print the bid and ask prices if such columns exist:
	virtual void printBidAsk(long bid, long ask) {}	//empty now. do I need this?
	virtual void printPositions(const std::vector <MikePosition> *openPositions) {}
	virtual void printPositions(const std::vector <MikePosition> *openPositions,
		const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice);
	void ClearColumn(int column);	//clears provided column of all text that might have been left behind by the previous draw - for use with Control::rePriceWidTable
	void ClearRow(int row);	//as above, but for clearing a row


	//                _    _                        __            _    _                       
	//    __ _   ___ | |_ | |_   ___  _ __  ___    / / ___   ___ | |_ | |_   ___  _ __  ___  _ 
	//   / _` | / _ \| __|| __| / _ \| '__|/ __|  / / / __| / _ \| __|| __| / _ \| '__|/ __|(_)
	//  | (_| ||  __/| |_ | |_ |  __/| |   \__ \ / /  \__ \|  __/| |_ | |_ |  __/| |   \__ \ _ 
	//   \__, | \___| \__| \__| \___||_|   |___//_/   |___/ \___| \__| \__| \___||_|   |___/(_)
	//   |___/                                                                     
	//GETTERS:

	inline int GetTopRowPrice() { return TopRowPrice; }
	inline int GetBottomRowPrice() { return (GetTopRowPrice() - GetRows() + 1); }
	inline void SetTopRowPrice(int value) { TopRowPrice = value; }
	inline std::vector <std::string> * GetColNames() { return &col_names; }
	virtual inline short GetBidCol(){ return bidColumn; }
	virtual inline short GetAskCol(){ return askColumn; }
	int RowOfPrice(long price);  //given price - returns the row in which that price is displayed in WidgetTable
	long PriceOfRow(int row);  //given the row - returns what price is currently printed in that row
	//SETTERS:
	virtual void SetColumnnWidth(short width) { columnWidth = width; }

protected:
	//                _  _  _                   _            
	//    ___   __ _ | || || |__    __ _   ___ | | __ ___  _ 
	//   / __| / _` || || || '_ \  / _` | / __|| |/ // __|(_)
	//  | (__ | (_| || || || |_) || (_| || (__ |   < \__ \ _ 
	//   \___| \__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)

	//static void button_cb(Fl_Widget *w, void * p);	//callbacks in fltk have to be static
	virtual void virtButtonCb(Fl_Widget *w, void * p);
	//                               _                         
	//   _ __ ___    ___  _ __ ___  | |__    ___  _ __  ___  _ 
	//  | '_ ` _ \  / _ \| '_ ` _ \ | '_ \  / _ \| '__|/ __|(_)
	//  | | | | | ||  __/| | | | | || |_) ||  __/| |   \__ \ _ 
	//  |_| |_| |_| \___||_| |_| |_||_.__/  \___||_|   |___/(_)
	//                                                         

	UserInterface * ptr_to_UserInterface;	//stores a pointer to window in which table is constructed. null at first. has to be set from outside.
	Control * ptrControl;
	//setting the column numbers where bid/ask will be printed:
	virtual void setBidAskColumns();
	
protected:
	//   _            _                         
	//  | |__    ___ | | _ __    ___  _ __  ___ 
	//  | '_ \  / _ \| || '_ \  / _ \| '__|/ __|
	//  | | | ||  __/| || |_) ||  __/| |   \__ \
	//  |_| |_| \___||_|| .__/  \___||_|   |___/
	//                  |_|                     
	//helper functions:

	//stores a pointer to window in which table is constructed. null at first. has to be set from outside:
	UserInterface * GetUserInterface() { return	ptr_to_UserInterface; }	
	Control * GetControl() { return ptrControl; }
	
	//below indexes for use by WidgetTable::printPositions. they need to be reset once Control::rePriceWidTable is called so that they remain valid:
	std::set <long> usedprices;//this set contains prices that have been used in the previous printout. in this iteration of printPositions, I will use the function ClearRow to erase this row before printing new values.
	std::set <long> notusedprices;//contains prices that have been erased at first but not filled with new values - which means they do not need to be erased again next time. this set will be used to remove values from usedprices so that we do not erase empty rows everytime
	
	//defines text of column headers:
	virtual void ColHeaderText(char * s, int C);	



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

	void PopPriceCol(/*WidgetTable * myTable*/); //populates the Price column with prices based on current TopRowPrice

	//supplied from example - dont know how this works
	void draw_cell(TableContext context, int R = 0, int C = 0, int X = 0, int Y = 0, int W = 0, int H = 0);	
	//fills the table with cells:
//	void SetSize(int newrows, int newcols, WidgetTable * mytable, std::vector<std::string> button_names = { "" });
};

class WidTable1 : public WidgetTable {
public:


	WidTable1(int x, int y, int w, int h, const char *l);
	WidTable1() :WidgetTable() { std::cout << "Empty WidTable1 created" << std::endl; }

private:
	//CALLBACK:
	virtual void virtButtonCb(Fl_Widget *w, void * p);

};


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