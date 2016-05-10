//put new ideas into this file
//file excluded from build
#include <sstream> //replaces cout
#include <string>
#include "UserInterface.h"
#include "Display.h"
#include "MikeSimulator.h"
#include "WidgetTable.h"

class Control;

UserInterface::UserInterface(
	
	Control * control, double bid_price, MikeSimulator * p, Display * ptr_t_display)	//constructor


{
	ptr_to_mikesimulator = p;	//pointer to class creating Display (which creates this class)
								//add remove elements below:
	m_window1->begin();
	delete m_table;	//deleting old table supplied by fluid
	m_pTable = new WidgetTable(this, 65, 0, 920, 495, "widgettable");
	
	//setting up the textdisplay with textbuffer (in window2):
	textBuffer = new Fl_Text_Buffer();
	text_display->buffer(textBuffer);
	//setting initial Slider max/min values to that of bid/ask - offset:
	m_slider1->minimum((double)ptr_to_mikesimulator->GetData()->GetBidPrice() + ((m_pTable->GetRows()) / 2));
	m_slider1->maximum((double)ptr_to_mikesimulator->GetData()->GetBidPrice() - ((m_pTable->GetRows()) / 2));
	m_slider1->value((double)ptr_to_mikesimulator->GetData()->GetBidPrice());
	//below just playing with creating new widgets outside of fluid:

	m_window1->end();



	//SETTING CALLBACKS:
	m_btn_up->callback(m_up_btn_cb, (void*)this);
	m_btn_down->callback(m_down_btn_cb, (void*) this);
	m_slider1->callback(m_slider1_cb, (void*) this);
	m_btn_next->callback(experimental_cb, (void*)this);

	//m_myExtraBtn = new Fl_Button(250, 510, 75, 55, "Extra");
	//m_myExtraBtn->callback(experim3, (void*) ptr_to_mikesimulator);

	//m_btn_extra->callback(experim3, (void*)ptr_to_mikesimulator);	//this changes size of Widgettable
	m_btn_extra->callback(rePriceWidTable, (void*)ptr_to_mikesimulator);	//this changes size of Widgettable

	m_window1->hide();
	m_window1->redraw();
	m_window1->show();

	//populate price column with prices:
	//	ptr_to_mikesimulator->GetDisplay()->GetWindow()->GetTable()->PopPriceCol(/*mikesimulator->GetDisplay()->GetWindow()->GetTable()*/);

}