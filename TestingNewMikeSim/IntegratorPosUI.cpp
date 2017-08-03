#include "IntegratorPosUI.h"
#include "UserInterface.h"
#include "MikePositionsOrders.h"

Mike::IntegratorPosUI::IntegratorPosUI()
{
	//create the User Interface:
	userInterface = new Mike::UserInterfaceLinked();
	userInterface->callbackDest = this;  //point userInterface callbacks to this class
	userInterface->m_window1->label("Integrator 1");  //name the interface window

	//create positions:
	posOrders = new MikePositionOrders("Integrator 1", 20400);
}
