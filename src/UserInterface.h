#ifndef _UserInterface_H_INCLUDED_
#define _UserInterface_H_INCLUDED_


#include "FLUID/FluidInterface.h"


#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Text_Display.H>

//#include "MikeEnums.h"
//#include "MikePositionsOrders.h"

class WidgetTable;	//forward declaration
//class Display;
class MikeSimulator;
class Control;
class MikePosition;
class MikeOrdersAtPrice;

class WidgetTable;
class Data;
class Control;
class MikeSimulator;
class PriceControlUI;
class UserInterface;
class MikePosition;
class MikeOrder;
class MikePositionOrders;
class Fl_Widget;

enum BtnPressed;
enum MikeOrderType;




class UserInterface : public FluidInterface
{	//elements of FluidInterface:
	
	//Fl_Double_Window *m_window1;
	//Fl_Value_Input *m_curr_ask;
	//Fl_Value_Input *m_top_limit;
	//Fl_Value_Input *m_top_profit;
	//Fl_Table *m_table;
	//Fl_Value_Input *m_curr_bid;
	//Fl_Value_Input *m_bottom_limit;
	//Fl_Value_Input *m_bottom_profit;
	//Fl_Button *m_btn_extra;
	//Fl_Output *m_TotOpenPos;
	//Fl_Output *m_TotOpenPL;
	//Fl_Output *m_TotClosedPL;
	//Fl_Output *m_TotPL;
	//Fl_Button *m_btn_printOrders;
	//Fl_Button *m_btn_checkFills;
	//Fl_Button *m_btn_printPos;
	//Fl_Double_Window *m_window2;
	//Fl_Text_Display *text_display;

public:
	//constructors/destructor:
	UserInterface(Control * control,
		double starting_bid_price = 700,
		int numberOfColumns = 16,
		int numberOfButtoncolumns = 5);

	//GETTERS / SETTERS:
	Control * GetControl() { return m_pControl; }
	inline WidgetTable *GetTable(){return m_pTable;}

	//helper functions
	void show();
	void rePriceWidTable(long bidprice);

	//WidgetTable callback:
	//THIS IS WHERE THE ORDER TYPE IS DETERMINED
	//BASED ON WHICH COLUMN HAS BEEN PRESSED IN WIDGETTABLE
	virtual void CallbkWidTable(int rowPressed, int colPressed, long price);
//	virtual void CallbkWidTable(int rowPressed, int colPressed, long price, int orderSize);
	virtual void PrintBidAsk(long bid, long ask);
	virtual void PrintAll(
		long totalOpenPos,
		long totalOpenPL,
		long totalClosedPL,
		long totalPL,
		long askPrice,
		long bidPrice,
		const std::vector <MikePosition> *openPositions,
		const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice);


protected:
	//members:
	WidgetTable *m_pTable;		//this replaces regular Fl_Table with my custom one	
	Control * m_pControl;
	Fl_Button* m_myExtraBtn;
	std::stringstream textDisplayString;
	int bid_price;

	//these two store the names of columns and buttons:
	std::vector <std::string> col_names;// = { "" };
	std::vector <std::string> button_names;// = { "" };

	//CALLBACKS

	static void m_extra_btn_cb(Fl_Widget * w, void * p);
	static void m_printOrders_btn_cb(Fl_Widget *w, void * p);
	static void m_checkFills_btn_cb(Fl_Widget *w, void * p);
	static void m_printPos_btn_cb(Fl_Widget *w, void * p);
	static void m_resetOrderSize_cb(Fl_Widget *w, void * p);

	//	static void m_down_btn_cb(Fl_Widget *w, void * p);
	//	static void m_up_btn_cb(Fl_Widget *w, void * p);
	//	static void m_slider1_cb(Fl_Widget *w, void * p);

	//helpers:
	//sets the names of column headers and buttons inside WidgetTable:
	/*virtual*/ void SetColButNames(std::vector <std::string> &col_names, std::vector <std::string> &button_names);
	
	
	//OLD CALLBACK FOR REFERENCE:
//	static void experimental_cb(Fl_Widget *w, void * p);	//THIS NEEDS WORK!

//	friend class ManualInterface;
//	friend class Control;
};





#endif //_UserInterface_H_INCLUDED_