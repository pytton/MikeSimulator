//8328506270 

#include "MikeSimulator.h"

MikeSimulator::MikeSimulator() //: control(this), data(this), display(this)
{

	m_pControl = new Control(this);
	m_pData = new Data(this);
	m_pDisplay = new Display(this);
}

MikeSimulator::~MikeSimulator() //: control(this), data(this), display(this)
{
	delete m_pControl;
	m_pControl = NULL;

	delete m_pData;
	m_pData = NULL;

	delete m_pDisplay;
	m_pDisplay = NULL;
}


MikeSimulator * MikeSimulator::getPointer()
{
	return this;
}


	Control *MikeSimulator::GetControl()
	{
		return m_pControl;
	}


	Data *MikeSimulator::GetData()
	{
		return m_pData;
	}


	Display *MikeSimulator::GetDisplay()
	{
		return m_pDisplay;
	}

	void MikeSimulator::SetControl(Control *pCtrl)
	{
		m_pControl = pCtrl;
	}


	void MikeSimulator::SetData(Data *pData)
	{		
		m_pData = pData;
	}

	void MikeSimulator::SetDisplay(Display *pDisplay)
	{
		m_pDisplay = pDisplay;
	}


void MikeSimulator::callToData(void *p)
{
	std::cout << "printed from callToData";
}