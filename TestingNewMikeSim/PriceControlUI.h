#ifndef PRICECONTROLUI_H_INCLUDED
#define PRICECONTROLUI_H_INCLUDED

#include "FLUID\FluidPriceControl.h"

//#include "Control.h"



class Control;

class PriceControlUI : public FluidPriceControlUI
{
public:
	friend class Control;

	private:

	
	//inherited from FluidPriceControlUI:
	//Fl_Double_Window *m_window1;
	//Fl_Button *m_btnUp;
	//Fl_Button *m_btnDown;
	//Fl_Output *m_BidDisplay;
	//Fl_Output *m_AskDisplay;
	//Fl_Value_Slider *m_slider1;
public:
	//constructor:
	PriceControlUI(Control * control, double starting_bid_price = 700 , int displayedRows = 200);

	Fl_Value_Slider * Getm_slider1() { return m_slider1; }


	void setSlider(int value, int max, int min);

private:
	Control * m_pControl;
	int bid_price;

	Control * getControl() { return m_pControl; }
	//callbacks:
	static void m_down_btn_cb(Fl_Widget *w, void * p);
	static void m_up_btn_cb(Fl_Widget *w, void * p);
	static void m_slider1_cb(Fl_Widget *w, void * p);
	static void m_btnPrint_cb(Fl_Widget *w, void * p);
	static void m_btnLiveDataConsolePrint_cb(Fl_Widget *w, void * p);
	static void m_btnConnectLiveData_cb(Fl_Widget *w, void * p);
	static void m_btnStartLoop_cb(Fl_Widget *w, void * p);
	static void m_experimentbtn_cb(Fl_Widget *w, void * p);

};

//enum BtnPressed	//used for callbacks from UserInterface and WidgetTable
//				//to Control class
//{
//	UPBTN,
//	DOWNBTN,
//	EXTRABTN,
//	SLIDER1,
//	NEXTBTN,
//	PREVBTN,
//};


#endif //PRICECONTROLUI_H_INCLUDED

