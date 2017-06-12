#include "FLUID\FluidPriceControl.h"
#include "PriceControlUI.h"
#include "Control.h"
#include "MikeEnums.h"

//class control;

enum BtnPressed;

PriceControlUI::PriceControlUI(Control * control, double starting_bid_price, int displayedRows)
{
	using namespace std;
	m_pControl = control;
	bid_price = starting_bid_price;
	//displayedRows - how many rows can be seen in WidgetTable

	m_window1->begin();

	m_slider1->minimum(bid_price + (displayedRows / 2));
	m_slider1->maximum(bid_price - (displayedRows / 2));
	m_slider1->value(bid_price);
	m_slider1->textsize(9);

	//CALLBACK SETUP:
	m_btnUp->callback(m_up_btn_cb, (void*)this);
	m_btnDown->callback(m_down_btn_cb, (void*) this);
	m_slider1->callback(m_slider1_cb, (void*) this);
	m_btnPrint->callback(m_btnPrint_cb, (void*) this);
	m_btnLiveDataConsolePrint->callback(m_btnLiveDataConsolePrint_cb, (void*) this);
	m_btnConnectLiveData->callback(m_btnConnectLiveData_cb, (void*) this);
	m_btnStartLoop->callback(m_btnStartLoop_cb, (void*) this);

	m_window1->end();

	m_window1->hide();
	m_window1->redraw();
	m_window1->show();

}

void PriceControlUI::setSlider(int value, int max, int min)
{
	m_slider1->value(value);
	m_slider1->maximum(max);
	m_slider1->minimum(min);

	m_slider1->redraw();
}

void PriceControlUI::m_down_btn_cb(Fl_Widget * buttonPressed, void * p)
{
	PriceControlUI * myPriceControlUI = (PriceControlUI*)p;
	myPriceControlUI->getControl()->CallbkPriceControlUI(myPriceControlUI, DOWNBTN, buttonPressed);
}

void PriceControlUI::m_up_btn_cb(Fl_Widget * buttonPressed, void * p)
{
	PriceControlUI * myPriceControlUI = (PriceControlUI*)p;
	myPriceControlUI->m_pControl->CallbkPriceControlUI(myPriceControlUI, UPBTN, buttonPressed);
}

void PriceControlUI::m_slider1_cb(Fl_Widget * slider1Pointer, void * p)
{
	PriceControlUI * myPriceControlUI = (PriceControlUI*)p;
	myPriceControlUI->m_pControl->CallbkPriceControlUI(myPriceControlUI, SLIDER1, slider1Pointer);
}

void PriceControlUI::m_btnPrint_cb(Fl_Widget * buttonPressed, void * p)
{
	PriceControlUI * myPriceControlUI = (PriceControlUI*)p;
	myPriceControlUI->m_pControl->CallbkPriceControlUI(myPriceControlUI, PRINTBUT, buttonPressed);
}

void PriceControlUI::m_btnLiveDataConsolePrint_cb(Fl_Widget * buttonPressed, void * p)
{
	PriceControlUI * myPriceControlUI = (PriceControlUI*)p;
	myPriceControlUI->m_pControl->CallbkPriceControlUI(myPriceControlUI, LIVEDATACONSOLEPRINTOUT, buttonPressed);
}

void PriceControlUI::m_btnConnectLiveData_cb(Fl_Widget * buttonPressed, void * p)
{
	PriceControlUI * myPriceControlUI = (PriceControlUI*)p;
	myPriceControlUI->m_pControl->CallbkPriceControlUI(myPriceControlUI, CONNECTLIVEDATA, buttonPressed);
}

void PriceControlUI::m_btnStartLoop_cb(Fl_Widget * buttonPressed, void * p)
{
	PriceControlUI * myPriceControlUI = (PriceControlUI*)p;
	myPriceControlUI->m_pControl->CallbkPriceControlUI(myPriceControlUI, STARTLOOP, buttonPressed);
}
