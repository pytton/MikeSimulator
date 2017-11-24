// generated by Fast Light User Interface Designer (fluid) version 1.0303

#include "FluidInterface.h"

FluidInterface::FluidInterface() {
  { m_window1 = new Fl_Double_Window(1117, 621, "window1");
    m_window1->user_data((void*)(this));
    { m_curr_ask = new Fl_Value_Input(1080, 200, 55, 20, "Current Ask");
    } // Fl_Value_Input* m_curr_ask
    { m_top_limit = new Fl_Value_Input(1075, 100, 60, 20, "Top Limit");
    } // Fl_Value_Input* m_top_limit
    { m_top_profit = new Fl_Value_Input(1075, 150, 60, 20, "Profit at top lim");
    } // Fl_Value_Input* m_top_profit
    { m_table = new Fl_Table(0, 0, 940, 655);
      m_table->labelsize(10);
      m_table->end();
    } // Fl_Table* m_table
    { m_curr_bid = new Fl_Value_Input(1080, 225, 55, 20, "Current Bid");
    } // Fl_Value_Input* m_curr_bid
    { m_bottom_limit = new Fl_Value_Input(1075, 125, 60, 20, "Bottom Limit");
    } // Fl_Value_Input* m_bottom_limit
    { m_bottom_profit = new Fl_Value_Input(1075, 175, 60, 20, "Profit at bottom lim");
    } // Fl_Value_Input* m_bottom_profit
    { m_btn_extra = new Fl_Button(1070, 255, 70, 40, "Reprice Table");
      m_btn_extra->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Button* m_btn_extra
    { m_TotOpenPos = new Fl_Output(1075, 6, 60, 24, "Total Open Pos:");
      m_TotOpenPos->labelsize(10);
      m_TotOpenPos->textsize(12);
    } // Fl_Output* m_TotOpenPos
    { m_TotOpenPL = new Fl_Output(1075, 26, 60, 24, "Total Open P/L:");
      m_TotOpenPL->labelsize(10);
      m_TotOpenPL->textsize(12);
    } // Fl_Output* m_TotOpenPL
    { m_TotClosedPL = new Fl_Output(1075, 46, 60, 24, "Total Closed P/L:");
      m_TotClosedPL->labelsize(10);
      m_TotClosedPL->textsize(12);
    } // Fl_Output* m_TotClosedPL
    { m_TotPL = new Fl_Output(1075, 66, 60, 24, "Total P/L:");
      m_TotPL->labelsize(10);
      m_TotPL->textsize(12);
    } // Fl_Output* m_TotPL
    { m_btn_printOrders = new Fl_Button(1035, 305, 45, 30, "Print Orders");
      m_btn_printOrders->labelsize(10);
      m_btn_printOrders->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Button* m_btn_printOrders
    { m_btn_checkFills = new Fl_Button(1035, 345, 45, 30, "Check Fillls");
      m_btn_checkFills->labelsize(10);
      m_btn_checkFills->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Button* m_btn_checkFills
    { m_btn_printPos = new Fl_Button(1090, 305, 45, 30, "Print Positions");
      m_btn_printPos->labelsize(10);
      m_btn_printPos->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Button* m_btn_printPos
    { m_order_size = new Fl_Value_Input(1075, 390, 60, 20, "Order Size");
    } // Fl_Value_Input* m_order_size
    { m_btn_resetOrdSize = new Fl_Button(1005, 410, 130, 30, "Reset Order Size");
      m_btn_resetOrdSize->labelsize(10);
      m_btn_resetOrdSize->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Button* m_btn_resetOrdSize
    m_window1->end();
  } // Fl_Double_Window* m_window1
}
