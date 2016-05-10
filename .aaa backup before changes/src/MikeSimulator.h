#ifndef _MIKESIMULATOR_H_INCLUDED_
#define _MIKESIMULATOR_H_INCLUDED_

#include "Data.h"
#include "Control.h"
#include "Display.h"

class Control;
class Data;
class Display;

class MikeSimulator
{
public:
	//	constructor
//MikeSimulator(Control * pControl, Data * pData, Display * pDisplay);
	MikeSimulator();
	~MikeSimulator();
	
	MikeSimulator * getPointer();

	static void callToData(void *p);

	Control *GetControl();
	Data *GetData();
	Display *GetDisplay();

	void SetControl(Control *pCtrl);
	void SetData(Data *pData);
	void SetDisplay(Display *pDisplay);

private:
	
	Control *m_pControl;
	Data *m_pData;
	Display *m_pDisplay;

};





#endif //_MIKESIMULATOR_H_INCLUDED_
