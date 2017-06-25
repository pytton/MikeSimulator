#include <iostream>

#include "MikeSimulator.h"
#include "Control.h"

namespace Mike {
	Simulator::Simulator(int starting_bid) //: control(this), data(this), display(this)
	{
		std::cout << "Constructor with starting bid: " << starting_bid << " called." << std::endl;
		//m_pControl = new Control(this, starting_bid);
	}

	Simulator::~Simulator() //: control(this), data(this), display(this)
	{
		if (!m_pControl) delete m_pControl;
		m_pControl = NULL;

	}

	Simulator * Simulator::getPointer()
	{
		return this;
	}

	Control *Simulator::GetControl()
	{
		return m_pControl;
	}



	void Simulator::SetControl(Control *pCtrl)
	{
		m_pControl = pCtrl;
	}

}