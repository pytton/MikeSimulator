#ifndef _WidgetTable_H_INCLUDED_
#define _WidgetTable_H_INCLUDED_

#include "WidTableBase.h"

class MikeSimulator;
class UserInterface;
class MikePosition;
class MikeOrdersAtPrice;
class Control;
class WidTable1;

namespace Mike {
	class WidTableBase;
	class My_fl_button;
}

//   #     #                              #######                              #  
//   #  #  # # #####   ####  ###### #####    #      ##   #####  #      ###### ### 
//   #  #  # # #    # #    # #        #      #     #  #  #    # #      #       #  
//   #  #  # # #    # #      #####    #      #    #    # #####  #      #####      
//   #  #  # # #    # #  ### #        #      #    ###### #    # #      #       #  
//   #  #  # # #    # #    # #        #      #    #    # #    # #      #      ### 
//    ## ##  # #####   ####  ######   #      #    #    # #####  ###### ######  #  
// 

//WigetTable - table with cells drawed inside it
class WidgetTable : public Mike::WidTableBase
{
	friend class UserInterfaceBase;
	friend class UserInterface;
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

	//print the bid and ask prices if such columns exist:
	virtual void printBidAsk(long bid, long ask) {}	//empty now. do I need this?
	virtual void printPositions(const std::vector <MikePosition> *openPositions) {}
	virtual void printPositions(const std::vector <MikePosition> *openPositions,
		const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice);

	//                _    _                        __            _    _                       
	//    __ _   ___ | |_ | |_   ___  _ __  ___    / / ___   ___ | |_ | |_   ___  _ __  ___  _ 
	//   / _` | / _ \| __|| __| / _ \| '__|/ __|  / / / __| / _ \| __|| __| / _ \| '__|/ __|(_)
	//  | (_| ||  __/| |_ | |_ |  __/| |   \__ \ / /  \__ \|  __/| |_ | |_ |  __/| |   \__ \ _ 
	//   \__, | \___| \__| \__| \___||_|   |___//_/   |___/ \___| \__| \__| \___||_|   |___/(_)
	//   |___/                                                                     
	//GETTERS:
	virtual inline short GetBidCol(){ return bidColumn; }
	virtual inline short GetAskCol(){ return askColumn; }

protected:
	//                _  _  _                   _            
	//    ___   __ _ | || || |__    __ _   ___ | | __ ___  _ 
	//   / __| / _` || || || '_ \  / _` | / __|| |/ // __|(_)
	//  | (__ | (_| || || || |_) || (_| || (__ |   < \__ \ _ 
	//   \___| \__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)

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
	
	//below describes which column number shows what kind of data?
	//eg. bidcolumn = 6 and askColumn = 7 mean that the bid is
	//printed in column 6 and ask is printed in column 7:
	short
		priceCol = 5,
		bidColumn = 6,
		askColumn = 7,
		buyLimitOrderCol = 8,
		buyStopOrderCol = 9,
		sellLimitOrderCol = 10,
		sellStopOrderCol = 11,
		openPosCol = 12,
		openPLCol = 13,
		closedPLCol = 14,
		totalPLCol = 15,
		avgPriceCol = 5,
		windownumber = 0;//for callbacks sent to Control - to tell which window its coming from. must be set in constructor

	void PopPriceCol(/*WidgetTable * myTable*/); //populates the Price column with prices based on current TopRowPrice

};

//class WidTable1 : public WidgetTable {
//public:
//
//
//	WidTable1(int x, int y, int w, int h, const char *l);
//	WidTable1() :WidgetTable() { std::cout << "Empty WidTable1 created" << std::endl; }
//
//private:
//	//CALLBACK:
//	virtual void virtButtonCb(Fl_Widget *w, void * p);
//
//};




#endif //_WidgetTable_H_INCLUDED_