// generated by Fast Light User Interface Designer (fluid) version 1.0303

#include "FluidInterface.h"

FluidInterface::FluidInterface() {
  { m_window1 = new Fl_Double_Window(981, 640, "window1");
    m_window1->user_data((void*)(this));
    { m_starting_bid = new Fl_Value_Input(410, 565, 45, 20, "Starting Bid");
      m_starting_bid->labelsize(10);
      m_starting_bid->textsize(10);
    } // Fl_Value_Input* m_starting_bid
    { m_curr_ask = new Fl_Value_Input(410, 590, 45, 20, "Current Ask");
    } // Fl_Value_Input* m_curr_ask
    { m_top_limit = new Fl_Value_Input(575, 540, 45, 20, "Top Limit");
    } // Fl_Value_Input* m_top_limit
    { m_top_profit = new Fl_Value_Input(575, 590, 45, 20, "Profit at top lim");
    } // Fl_Value_Input* m_top_profit
    { m_table = new Fl_Table(65, 0, 940, 495);
      m_table->labelsize(10);
      m_table->end();
    } // Fl_Table* m_table
    { m_curr_bid = new Fl_Value_Input(410, 615, 45, 20, "Current Bid");
    } // Fl_Value_Input* m_curr_bid
    { m_bottom_limit = new Fl_Value_Input(575, 565, 45, 20, "Bottom Limit");
    } // Fl_Value_Input* m_bottom_limit
    { m_bottom_profit = new Fl_Value_Input(575, 615, 45, 20, "Profit at bottom lim");
    } // Fl_Value_Input* m_bottom_profit
    { m_btn_up = new Fl_Button(255, 540, 65, 40, "Up");
    } // Fl_Button* m_btn_up
    { m_btn_down = new Fl_Button(255, 595, 65, 40, "Down");
    } // Fl_Button* m_btn_down
    { m_btn_next = new Fl_Button(75, 580, 80, 55, "Next");
    } // Fl_Button* m_btn_next
    { m_slider1 = new Fl_Value_Slider(5, 0, 35, 650, "m_slider1");
      m_slider1->minimum(200);
      m_slider1->maximum(0);
      m_slider1->step(1);
      m_slider1->value(100);
    } // Fl_Value_Slider* m_slider1
    { m_btn_extra = new Fl_Button(165, 580, 80, 55, "Extra");
    } // Fl_Button* m_btn_extra
    { m_TotOpenPos = new Fl_Output(240, 501, 45, 24, "Total Open Pos:");
      m_TotOpenPos->labelsize(10);
      m_TotOpenPos->textsize(12);
    } // Fl_Output* m_TotOpenPos
    { m_TotOpenPL = new Fl_Output(365, 501, 45, 24, "Total Open P/L:");
      m_TotOpenPL->labelsize(10);
      m_TotOpenPL->textsize(12);
    } // Fl_Output* m_TotOpenPL
    { m_TotClosedPL = new Fl_Output(495, 501, 45, 24, "Total Closed P/L:");
      m_TotClosedPL->labelsize(10);
      m_TotClosedPL->textsize(12);
    } // Fl_Output* m_TotClosedPL
    { m_TotPL = new Fl_Output(600, 501, 45, 24, "Total P/L:");
      m_TotPL->labelsize(10);
      m_TotPL->textsize(12);
    } // Fl_Output* m_TotPL
    { m_btn_printOrders = new Fl_Button(685, 500, 45, 30, "Print Orders");
      m_btn_printOrders->labelsize(10);
      m_btn_printOrders->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Button* m_btn_printOrders
    { m_btn_checkFills = new Fl_Button(685, 540, 45, 30, "Check Fillls");
      m_btn_checkFills->labelsize(10);
      m_btn_checkFills->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Button* m_btn_checkFills
    m_window1->end();
  } // Fl_Double_Window* m_window1
  { m_window2 = new Fl_Double_Window(486, 320, "window2");
    m_window2->user_data((void*)(this));
    { text_display = new Fl_Text_Display(80, 40, 325, 255, "text");
    } // Fl_Text_Display* text_display
    m_window2->end();
  } // Fl_Double_Window* m_window2
}
