// generated by Fast Light User Interface Designer (fluid) version 1.0303

#ifndef FluidInterface_h
#define FluidInterface_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>

class FluidInterface {
public:
  FluidInterface();
  Fl_Double_Window *m_window1;
  Fl_Value_Input *m_curr_ask;
  Fl_Value_Input *m_top_limit;
  Fl_Value_Input *m_top_profit;
  Fl_Table *m_table;
  Fl_Value_Input *m_curr_bid;
  Fl_Value_Input *m_bottom_limit;
  Fl_Value_Input *m_bottom_profit;
  Fl_Button *m_btn_extra;
  Fl_Output *m_TotOpenPos;
  Fl_Output *m_TotOpenPL;
  Fl_Output *m_TotClosedPL;
  Fl_Output *m_TotPL;
  Fl_Button *m_btn_printOrders;
  Fl_Button *m_btn_checkFills;
  Fl_Button *m_btn_printPos;
  Fl_Value_Input *m_order_size;
  Fl_Button *m_btn_resetOrdSize;
  Fl_Button *m_btn_CancelAllOrders;
  Fl_Output *m_AvgPosPrice;
  Fl_Button *m_btn_ClearPositions;
};
#endif
