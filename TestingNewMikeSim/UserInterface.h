#ifndef _UserInterface_H_INCLUDED_
#define _UserInterface_H_INCLUDED_




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

#include "FLUID/FluidInterface.h"

class WidgetTable;
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

enum class BtnPressed;
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

public:
	//                           _                       _                  
	//    ___  ___   _ __   ___ | |_  _ __  _   _   ___ | |_  ___   _ __  _ 
	//   / __|/ _ \ | '_ \ / __|| __|| '__|| | | | / __|| __|/ _ \ | '__|(_)
	//  | (__| (_) || | | |\__ \| |_ | |   | |_| || (__ | |_| (_) || |    _ 
	//   \___|\___/ |_| |_||___/ \__||_|    \__,_| \___| \__|\___/ |_|   (_)
	//                                                                      
	UserInterface(Control * control,
		double starting_bid_price = 700,
		int numberOfColumns = 19,
		int numberOfButtoncolumns = 5);

	//                _    _                       __           _    _                      
	//    __ _   ___ | |_ | |_  ___  _ __  ___    / /___   ___ | |_ | |_  ___  _ __  ___  _ 
	//   / _` | / _ \| __|| __|/ _ \| '__|/ __|  / // __| / _ \| __|| __|/ _ \| '__|/ __|(_)
	//  | (_| ||  __/| |_ | |_|  __/| |   \__ \ / / \__ \|  __/| |_ | |_|  __/| |   \__ \ _ 
	//   \__, | \___| \__| \__|\___||_|   |___//_/  |___/ \___| \__| \__|\___||_|   |___/(_)
	//   |___/                                                                              
	Control * GetControl() { return m_pControl; }
	inline WidgetTable *GetTable(){return m_pTable;}

	//                _         _                      
	//   _ __   _ __ (_) _ __  | |_  ___  _ __  ___  _ 
	//  | '_ \ | '__|| || '_ \ | __|/ _ \| '__|/ __|(_)
	//  | |_) || |   | || | | || |_|  __/| |   \__ \ _ 
	//  | .__/ |_|   |_||_| |_| \__|\___||_|   |___/(_)
	//  |_|                                            
	virtual void PrintBidAsk(long bid, long ask);
	virtual void PrintAll(
		long totalOpenPos,
		long totalOpenPL,
		long totalClosedPL,
		long totalPL,
		long askPrice,
		long bidPrice,
		const std::vector <MikePosition> *openPositions,
		const std::vector <MikeOrdersAtPrice> *openOrdersAtPrice,
		double averagePrice);

protected:
	//                               _                         
	//   _ __ ___    ___  _ __ ___  | |__    ___  _ __  ___  _ 
	//  | '_ ` _ \  / _ \| '_ ` _ \ | '_ \  / _ \| '__|/ __|(_)
	//  | | | | | ||  __/| | | | | || |_) ||  __/| |   \__ \ _ 
	//  |_| |_| |_| \___||_| |_| |_||_.__/  \___||_|   |___/(_)
	//                                                         
	WidgetTable *m_pTable;		//this replaces regular Fl_Table with my custom one	
	Control * m_pControl;
	Fl_Button* m_myExtraBtn;
	int bid_price;

	//these two store the names of columns and buttons:
	std::vector <std::string> col_names;
	std::vector <std::string> button_names;

	//               _  _  _                   _            
	//    ___  __ _ | || || |__    __ _   ___ | | __ ___  _ 
	//   / __|/ _` || || || '_ \  / _` | / __|| |/ // __|(_)
	//  | (__| (_| || || || |_) || (_| || (__ |   < \__ \ _ 
	//   \___|\__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)
	//                                                      

public:
	//WidgetTable callback:
	//THIS IS WHERE THE ORDER TYPE IS DETERMINED
	//BASED ON WHICH COLUMN HAS BEEN PRESSED IN WIDGETTABLE
	virtual void CallbkWidTable(int rowPressed, int colPressed, long price);
protected:
	static void m_extra_btn_cb(Fl_Widget * w, void * p);
	static void m_printOrders_btn_cb(Fl_Widget *w, void * p);
	static void m_checkFills_btn_cb(Fl_Widget *w, void * p);
	static void m_printPos_btn_cb(Fl_Widget *w, void * p);
	static void m_resetOrderSize_cb(Fl_Widget *w, void * p);
	static void m_btn_CancelAllOrders_cb(Fl_Widget *w, void * p);
	

	//   _            _                            
	//  | |__    ___ | | _ __    ___  _ __  ___  _ 
	//  | '_ \  / _ \| || '_ \  / _ \| '__|/ __|(_)
	//  | | | ||  __/| || |_) ||  __/| |   \__ \ _ 
	//  |_| |_| \___||_|| .__/  \___||_|   |___/(_)
	//                  |_|                        

	//sets the names of column headers and buttons inside WidgetTable:
	virtual void SetColButNames(std::vector <std::string> &col_names, std::vector <std::string> &button_names);
public:
	void rePriceWidTable(long bidprice);
	
	//                                  _                          _           
	//    ___ __  __ _ __    ___  _ __ (_) _ __ ___    ___  _ __  | |_  ___  _ 
	//   / _ \\ \/ /| '_ \  / _ \| '__|| || '_ ` _ \  / _ \| '_ \ | __|/ __|(_)
	//  |  __/ >  < | |_) ||  __/| |   | || | | | | ||  __/| | | || |_ \__ \ _ 
	//   \___|/_/\_\| .__/  \___||_|   |_||_| |_| |_| \___||_| |_| \__||___/(_)
	//              |_|                                                        
public:
	//changes the name displayed on top of the window of UserInterface:
	void changename(std::string name);
};

//   __ _                 _     _____      _     _      __    __ _           _               
//  / _(_)_ __ ___  _ __ | | __/__   \__ _| |__ | | ___/ / /\ \ (_)_ __   __| | _____      __
//  \ \| | '_ ` _ \| '_ \| |/ _ \/ /\/ _` | '_ \| |/ _ \ \/  \/ / | '_ \ / _` |/ _ \ \ /\ / /
//  _\ \ | | | | | | |_) | |  __/ / | (_| | |_) | |  __/\  /\  /| | | | | (_| | (_) \ V  V / 
//  \__/_|_| |_| |_| .__/|_|\___\/   \__,_|_.__/|_|\___| \/  \/ |_|_| |_|\__,_|\___/ \_/\_/  
//                 |_|                                                                       



#include "FLUID\FluidSimpleTableWindow.h"
#include <string>
class FluidSimpleTableWindow;
class WidgetTable;
class Control;


class SimpleTableWindow : FluidSimpleTableWindow
{
public:
	SimpleTableWindow();
	SimpleTableWindow(Control * ptrControl, short windownumber);
	~SimpleTableWindow();

	void rePriceWidTable(long bidprice);

	WidgetTable * widTable;

	short thiswindownumber; //for use by class creating SimpleTableWindow - if more than one instance of SimpleTableWindow is used. for callbacks which have to be static in FLTK

};

//     ___             ___         _                                _        _____ 
//    / _ \___  ___   /___\_ __ __| | /\/\   __ _ _ __  _   _  __ _| |/\ /\  \_   \
//   / /_)/ _ \/ __| //  // '__/ _` |/    \ / _` | '_ \| | | |/ _` | / / \ \  / /\/
//  / ___/ (_) \__ \/ \_//| | | (_| / /\/\ \ (_| | | | | |_| | (_| | \ \_/ /\/ /_  
//  \/    \___/|___/\___/ |_|  \__,_\/    \/\__,_|_| |_|\__,_|\__,_|_|\___/\____/  
//                                                                                 


#include "FLUID/FluidPosOrdManualUI.h"
namespace Mike {

	class PosOrdManualUI :  FluidPosOrdManualUI
	{
	public:
		PosOrdManualUI(void * control,
			double starting_bid_price = 700,
			int numberOfColumns = 16,
			int numberOfButtoncolumns = 5);
		//~PosOrdManualUI();

	private:


	};
}//namespace Mike

#endif //_UserInterface_H_INCLUDED_