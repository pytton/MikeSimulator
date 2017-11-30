#ifndef _UserInterface_H_INCLUDED_
#define _UserInterface_H_INCLUDED_

#include "FluidInterface.h"
#include "MikeEnums.h"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>



namespace Mike {
	class WidTableBase;

	class WidgetTable;
	class MikeSimulator;
	class Control;
	class MikePosition;
	class MikeOrdersAtPrice;
}


namespace Mike {

	enum class BtnPressed;
	enum MikeOrderType;

	class UserInterfaceBase : public FluidInterface
	{
		friend class WidgetTable;
		friend class Mike::Control;
		//	friend class UserInterface;
		//	friend class ManualInterface;

	protected:
		//                           _                       _                  
		//    ___  ___   _ __   ___ | |_  _ __  _   _   ___ | |_  ___   _ __  _ 
		//   / __|/ _ \ | '_ \ / __|| __|| '__|| | | | / __|| __|/ _ \ | '__|(_)
		//  | (__| (_) || | | |\__ \| |_ | |   | |_| || (__ | |_| (_) || |    _ 
		//   \___|\___/ |_| |_||___/ \__||_|    \__,_| \___| \__|\___/ |_|   (_)
		// 

		UserInterfaceBase();


		//                _    _                       __           _    _                      
		//    __ _   ___ | |_ | |_  ___  _ __  ___    / /___   ___ | |_ | |_  ___  _ __  ___  _ 
		//   / _` | / _ \| __|| __|/ _ \| '__|/ __|  / // __| / _ \| __|| __|/ _ \| '__|/ __|(_)
		//  | (_| ||  __/| |_ | |_|  __/| |   \__ \ / / \__ \|  __/| |_ | |_|  __/| |   \__ \ _ 
		//   \__, | \___| \__| \__|\___||_|   |___//_/  |___/ \___| \__| \__|\___||_|   |___/(_)
		//   |___/                                                                              
		virtual Control * GetControl() { return m_pControl; }
		inline WidgetTable *GetTable() { return m_pTable; }
		//                _         _                      
		//   _ __   _ __ (_) _ __  | |_  ___  _ __  ___  _ 
		//  | '_ \ | '__|| || '_ \ | __|/ _ \| '__|/ __|(_)
		//  | |_) || |   | || | | || |_|  __/| |   \__ \ _ 
		//  | .__/ |_|   |_||_| |_| \__|\___||_|   |___/(_)
		//  |_|   
	public:
		//changes the name displayed on top of the window of UserInterface:
		void changename(::std::string name);
		virtual void PrintBidAsk(long bid, long ask);
		virtual void PrintAll(
			long totalOpenPos,
			long totalOpenPL,
			long totalClosedPL,
			long totalPL,
			long askPrice,
			long bidPrice,
			const ::std::vector <MikePosition> *openPositions,
			const ::std::vector <MikeOrdersAtPrice> *openOrdersAtPrice,
			double averagePrice);
		//                               _                         
		//   _ __ ___    ___  _ __ ___  | |__    ___  _ __  ___  _ 
		//  | '_ ` _ \  / _ \| '_ ` _ \ | '_ \  / _ \| '__|/ __|(_)
		//  | | | | | ||  __/| | | | | || |_) ||  __/| |   \__ \ _ 
		//  |_| |_| |_| \___||_| |_| |_||_.__/  \___||_|   |___/(_)
		//                                                         
	protected:
		WidgetTable *m_pTable;		//this replaces regular Fl_Table with my custom one	
		Control * m_pControl;
		Fl_Button* m_myExtraBtn;
		int bid_price = 20400;  //used to determine top row price in WidgetTable
		//these two store the names of columns and buttons:
		::std::vector <::std::string> col_names;
		::std::vector <::std::string> button_names;

		//               _  _  _                   _            
		//    ___  __ _ | || || |__    __ _   ___ | | __ ___  _ 
		//   / __|/ _` || || || '_ \  / _` | / __|| |/ // __|(_)
		//  | (__| (_| || || || |_) || (_| || (__ |   < \__ \ _ 
		//   \___|\__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)
		//   

		//this sends the data from callbkWidTable to wherever it is needed:
		//Nowhere in UserInterfaceBase
		//To Control class in UserInterface
		//or somewhere else in derived classes:
		virtual void sendWidTableCallback(int rowPressed, int colPressed, long price, MikeOrderType tempOrderType, int orderSize) = 0;  // { std::cout << "UserInterfaceBase callback" << std::endl; }
		//empty in Base. implement in derived classes
		virtual void callbkUserInterface(BtnPressed) = 0;

		//WidgetTable callback:
	   //THIS IS WHERE THE ORDER TYPE IS DETERMINED
	   //BASED ON WHICH COLUMN HAS BEEN PRESSED IN WIDGETTABLE
		virtual void callbkWidTable(int rowPressed, int colPressed, long price);

		//internal callback sets order size to 100
		static void m_resetOrderSize_cb(Fl_Widget *w, void * p);

		//below callbacks link to outside of this class using virtual function callbkUserInterface:
		static void m_extra_btn_cb(Fl_Widget * w, void * p);
		static void m_printOrders_btn_cb(Fl_Widget *w, void * p);
		static void m_checkFills_btn_cb(Fl_Widget *w, void * p);
		static void m_printPos_btn_cb(Fl_Widget *w, void * p);
		static void m_btn_CancelAllOrders_cb(Fl_Widget *w, void * p);
		static void m_btn_ClearPostions(Fl_Widget *w, void * p);

		//   _            _                            
		//  | |__    ___ | | _ __    ___  _ __  ___  _ 
		//  | '_ \  / _ \| || '_ \  / _ \| '__|/ __|(_)
		//  | | | ||  __/| || |_) ||  __/| |   \__ \ _ 
		//  |_| |_| \___||_|| .__/  \___||_|   |___/(_)
		//                  |_|                        

		//sets the names of column headers and buttons inside WidgetTable:
		virtual void SetColButNames(::std::vector <::std::string> &col_names, ::std::vector <::std::string> &button_names);
	public:
		void rePriceWidTable(long bidprice);

	};


	//                         _____         _                __                   
	//   /\ /\  ___   ___  _ __\_   \ _ __  | |_  ___  _ __  / _|  __ _   ___  ___ 
	//  / / \ \/ __| / _ \| '__|/ /\/| '_ \ | __|/ _ \| '__|| |_  / _` | / __|/ _ \
	//  \ \_/ /\__ \|  __/| |/\/ /_  | | | || |_|  __/| |   |  _|| (_| || (__|  __/
	//   \___/ |___/ \___||_|\____/  |_| |_| \__|\___||_|   |_|   \__,_| \___|\___|
	//                                                                             


	class UserInterface : public UserInterfaceBase
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
		//Fl_Value_Input *m_order_size;
		//Fl_Button *m_btn_resetOrdSize;
		//Fl_Button *m_btn_CancelAllOrders;
		//Fl_Output *m_AvgPosPrice;
		//Fl_Button *m_btn_ClearPositions;

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
		//               _  _  _                   _            
		//    ___  __ _ | || || |__    __ _   ___ | | __ ___  _ 
		//   / __|/ _` || || || '_ \  / _` | / __|| |/ // __|(_)
		//  | (__| (_| || || || |_) || (_| || (__ |   < \__ \ _ 
		//   \___|\__,_||_||_||_.__/  \__,_| \___||_|\_\|___/(_)
		//                                                      
	protected:
		//this sends the data from UserInterfaceBase::callbkWidTable to wherever it is needed. To Control class in UserInterface or somewhere else in derived classes:
		virtual void sendWidTableCallback(int rowPressed, int colPressed, long price, MikeOrderType tempOrderType, int orderSize);
		//static button callbacks defined in UserInterfaceBase call this function to determine what to do with pressing buttons
		virtual void callbkUserInterface(BtnPressed);
	};

}//namespace Mike

//////////////////////////////////////////////////


//                         _____         _                __                      __  _         _              _ 
//   /\ /\  ___   ___  _ __\_   \ _ __  | |_  ___  _ __  / _|  __ _   ___  ___   / / (_) _ __  | | __ ___   __| |
//  / / \ \/ __| / _ \| '__|/ /\/| '_ \ | __|/ _ \| '__|| |_  / _` | / __|/ _ \ / /  | || '_ \ | |/ // _ \ / _` |
//  \ \_/ /\__ \|  __/| |/\/ /_  | | | || |_|  __/| |   |  _|| (_| || (__|  __// /___| || | | ||   <|  __/| (_| |
//   \___/ |___/ \___||_|\____/  |_| |_| \__|\___||_|   |_|   \__,_| \___|\___|\____/|_||_| |_||_|\_\\___| \__,_|
//                                                                                                               

namespace Mike {
	class IntegratorPosUI;
}


namespace Mike {

	//special class designed for IntegratorPosUI with virtual function
	//UserInterfaceLinked::sendWidTableCallback implemented so that it sneds
	//orders directly to MikePositionOrders without using Control class
	class UserInterfaceLinked : public UserInterfaceBase {
		friend class IntegratorPosUI;
	public:
		UserInterfaceLinked(IntegratorPosUI * ptr);
		UserInterfaceLinked();
		
	private:

		//destination of callbacks:
		IntegratorPosUI * callbackDest = NULL;

//		virtual void callbkUserInterface(BtnPressed);

		virtual void sendWidTableCallback(int rowPressed, int colPressed, long price, MikeOrderType tempOrderType, int orderSize);  // { std::cout << "Callback" << std::endl; }
		virtual void callbkUserInterface(BtnPressed);  // { std::cout << "Callback" << std::endl; }
	};
}//namespace Mike




//
////   __ _                 _     _____      _     _      __    __ _           _               
////  / _(_)_ __ ___  _ __ | | __/__   \__ _| |__ | | ___/ / /\ \ (_)_ __   __| | _____      __
////  \ \| | '_ ` _ \| '_ \| |/ _ \/ /\/ _` | '_ \| |/ _ \ \/  \/ / | '_ \ / _` |/ _ \ \ /\ / /
////  _\ \ | | | | | | |_) | |  __/ / | (_| | |_) | |  __/\  /\  /| | | | | (_| | (_) \ V  V / 
////  \__/_|_| |_| |_| .__/|_|\___\/   \__,_|_.__/|_|\___| \/  \/ |_|_| |_|\__,_|\___/ \_/\_/  
////                 |_|                                                                       
//
//
//
//#include "FLUID\FluidSimpleTableWindow.h"
//#include <string>
//class FluidSimpleTableWindow;
//class WidgetTable;
//class Control;
//
//
//class SimpleTableWindow : FluidSimpleTableWindow
//{
//public:
//	SimpleTableWindow();
//	SimpleTableWindow(Control * ptrControl, short windownumber);
//	~SimpleTableWindow();
//
//	void rePriceWidTable(long bidprice);
//
//	Mike::WidTableBase * widTable;
//
//	short thiswindownumber; //for use by class creating SimpleTableWindow - if more than one instance of SimpleTableWindow is used. for callbacks which have to be static in FLTK
//
//};
//
////     ___             ___         _                                _        _____ 
////    / _ \___  ___   /___\_ __ __| | /\/\   __ _ _ __  _   _  __ _| |/\ /\  \_   \
////   / /_)/ _ \/ __| //  // '__/ _` |/    \ / _` | '_ \| | | |/ _` | / / \ \  / /\/
////  / ___/ (_) \__ \/ \_//| | | (_| / /\/\ \ (_| | | | | |_| | (_| | \ \_/ /\/ /_  
////  \/    \___/|___/\___/ |_|  \__,_\/    \/\__,_|_| |_|\__,_|\__,_|_|\___/\____/  
////                                                                                 
//
//
//#include "FLUID/FluidPosOrdManualUI.h"
//#include "FLUID/FluidControlInterface.h"
//namespace Mike {
//
//	class PosOrdManualUI : FluidPosOrdManualUI
//	{
//	public:
//		PosOrdManualUI(void * control,
//			double starting_bid_price = 700,
//			int numberOfColumns = 16,
//			int numberOfButtoncolumns = 5);
//		//~PosOrdManualUI();
//
//	private:
//
//
//	};
//
//	//experimenting with an Interface for Control class
//	//right now used for showing windows that might have been closed
//	class ControlInterface : FluidControlInterface {
//	public:
//
//		ControlInterface();
//		//where do you want callbacks sent? Set to NULL to disable callbacks
//		Control * callbackDestination = NULL;
//		void setCallbackDestination(Control * p) { callbackDestination = p; }
//		//callbacks:
//
//		//FLTK callback have to be static
//		static void m_btnShowPositions1_cb(Fl_Widget * w, void * p);
//		virtual void maincallback(Fl_Widget * w, void * p);
//	};
//
//
//}//namespace Mike

#endif //_UserInterface_H_INCLUDED_