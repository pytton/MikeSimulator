#ifndef _MIKESIMULATOR_H_INCLUDED_
#define _MIKESIMULATOR_H_INCLUDED_



class Control;
class Data;


class MikeSimulator
{
public:
	//	constructor
//MikeSimulator(Control * pControl, Data * pData, Display * pDisplay);
	MikeSimulator();
	MikeSimulator::MikeSimulator(int starting_bid);	//this used for refactoring - new constructor
													//made to modify Control and UserInterface classes
													//do similar stuff in Control, Data, and Display
	~MikeSimulator();
	
	MikeSimulator * getPointer();

	static void callToData(void *p);

	Control *GetControl();
	Data *GetData();
//	Display *GetDisplay();

	void SetControl(Control *pCtrl);
	void SetData(Data *pData);
//	void SetDisplay(Display *pDisplay);

private:
	
	Control *m_pControl;
	Data *m_pData;
//	Display *m_pDisplay;

};





#endif //_MIKESIMULATOR_H_INCLUDED_
