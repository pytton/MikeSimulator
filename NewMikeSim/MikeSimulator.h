#ifndef _MIKESIMULATOR_H_INCLUDED_
#define _MIKESIMULATOR_H_INCLUDED_

#include "FL/Fl.h"

class Control;
class Data;
class Simulator;

namespace Mike {

	class Simulator
	{
	public:
		//	constructor
		Simulator(int starting_bid);
		~Simulator();

		Simulator * getPointer();

		Control *GetControl();
		void SetControl(Control *pCtrl);

	private:
		Control *m_pControl;
	};
}




#endif //_MIKESIMULATOR_H_INCLUDED_
