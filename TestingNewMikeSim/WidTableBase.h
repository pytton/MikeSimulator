#ifndef _WidTableBase_H_INCLUDED_
#define _WidTableBase_H_INCLUDED_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Text_Display.H>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <set>
#include <stack>


//   #     #          #######                             ######                        #  
//   #  #  # # #####     #      ##   #####  #      ###### #     #   ##    ####  ###### ### 
//   #  #  # # #    #    #     #  #  #    # #      #      #     #  #  #  #      #       #  
//   #  #  # # #    #    #    #    # #####  #      #####  ######  #    #  ####  #####      
//   #  #  # # #    #    #    ###### #    # #      #      #     # ######      # #       #  
//   #  #  # # #    #    #    #    # #    # #      #      #     # #    # #    # #      ### 
//    ## ##  # #####     #    #    # #####  ###### ###### ######  #    #  ####  ######  #  
//                                                                                         

//base class of all WidgetTables
//never use this class. derive from it to get what you need
class WidTableBase : public Fl_Table_Row
{
protected:
	WidTableBase(int x, int y, int w, int h, const char *l);
	WidTableBase(
		int x, int y, int w, int h, const char *l,
		int top_row_price,
		int number_rows = 25,
		int number_cols = 15,	/*how many columns in the table?*/
		int how_many_cols_are_buttons = 5,	/*how many columns are buttons?*/
		std::vector <std::string> col_names = { "" },	/*names of col headers*/
		std::vector <std::string> button_names = { "" }	//names of buttons		
	);
	~WidTableBase();
	//                _    _                        __            _    _                       
	//    __ _   ___ | |_ | |_   ___  _ __  ___    / / ___   ___ | |_ | |_   ___  _ __  ___  _ 
	//   / _` | / _ \| __|| __| / _ \| '__|/ __|  / / / __| / _ \| __|| __| / _ \| '__|/ __|(_)
	//  | (_| ||  __/| |_ | |_ |  __/| |   \__ \ / /  \__ \|  __/| |_ | |_ |  __/| |   \__ \ _ 
	//   \__, | \___| \__| \__| \___||_|   |___//_/   |___/ \___| \__| \__| \___||_|   |___/(_)
	//   |___/                                                                     
	//GETTERS:
public:
	inline int GetRows() { return table_rows; }
	inline int GetCols() { return table_cols; }
	inline int GetTopRowPrice() { return TopRowPrice; }
	inline int GetBottomRowPrice() { return (GetTopRowPrice() - GetRows() + 1); }
	inline void SetTopRowPrice(int value) { TopRowPrice = value; }
	inline std::vector <std::string> * GetColNames() { return &col_names; }

	//given price - returns the row in which that price is displayed in WidgetTable:
	int RowOfPrice(long price);
	//given the row - returns what price is currently printed in that row:
	long PriceOfRow(int row);

	//SETTERS:
	virtual void SetColumnnWidth(short width) { columnWidth = width; }

	//                _  _  _                   _            
	//    ___   __ _ | || || |__    __ _   ___ | | __ ___  _ 
	//   / __| / _` || || || '_ \  / _` | / __|| |/ // __|(_)
	//  | (__ | (_| || || || |_) || (_| || (__ |   < \__ \ _ 
	//   \___| \__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)

protected:
	static void button_cb(Fl_Widget *w, void * p);	//callbacks in fltk have to be static
	virtual void virtButtonCb(Fl_Widget *w, void * p) = 0;

	//                _         _                   
	//   _ __   _ __ (_) _ __  | |_  ___  _ __  ___ 
	//  | '_ \ | '__|| || '_ \ | __|/ _ \| '__|/ __|
	//  | |_) || |   | || | | || |_|  __/| |   \__ \
	//  | .__/ |_|   |_||_| |_| \__|\___||_|   |___/
//  |_|                                         

	virtual void printInTable(int row, int col, std::string text);	//row = 0 is first row!
	void ClearColumn(int column);	//clears provided column of all text that might have been left behind by the previous draw - for use with Control::rePriceWidTable
	void ClearRow(int row);	//as above, but for clearing a row

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

//defines text of column headers:
	virtual void ColHeaderText(char * s, int C);
	inline void SetRows(int numRows) { table_rows = numRows; }
	inline void SetCols(int numCol) { table_cols = numCol; }
	//returns a pointer to the cell in the table at nRow nCol:
	Fl_Widget * GetElement(int nRow, int nCol);


	//supplied from example - dont know how this works:
	void draw_cell(TableContext context, int R = 0, int C = 0, int X = 0, int Y = 0, int W = 0, int H = 0);
	//fills the table with cells:
	void SetSize(int newrows, int newcols, WidTableBase * mytable, std::vector<std::string> button_names = { "" });

	short columnWidth = 55;

private:
	//trying to resolve issue with using shared_ptr in SetSize function.
	// the line Fl_Input *in = new Fl_Input(X, Y, W, H); created objects possibly not 
	//detroyed when WidTableBase is destroyed. Replacing the line with a shared_ptr
	//crashes program - probably because shared_ptr is destroyed before being used by
	//FLTK. Idea: create a stack within WidTableBase and add all pointers to it.
	//When WidTableBase is destroyed this stack gets destroyed and hopefully releases all
	//unusued shared_ptr's

	std::stack<Fl_Input*> sharedFlInputPointers;

};  //class WidTableBase


	//   #     #                                                                              #  
	//   ##   ## #   #         ###### #              #####  #    # ##### #####  ####  #    # ### 
	//   # # # #  # #          #      #              #    # #    #   #     #   #    # ##   #  #  
	//   #  #  #   #           #####  #              #####  #    #   #     #   #    # # #  #     
	//   #     #   #           #      #              #    # #    #   #     #   #    # #  # #  #  
	//   #     #   #           #      #              #    # #    #   #     #   #    # #   ## ### 
	//   #     #   #           #      ######         #####   ####    #     #    ####  #    #  #  
	//                 #######               #######                                             

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



#endif //_WidTableBase_H_INCLUDED_
