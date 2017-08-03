#ifndef IntegratorPosUI_h
#define IntegratorPosUI_h

//////////////////////////////////////////////////////////////////////////////

/*
This class links classes derived from UserInterface class and MikePositionOrders class
together. 

UserInterface callbacks link to this class which then calls appropriate functions in
MikePositionOrders.

This class has a function to print out data from MikePositionOrders in UserInterface




*/




//////////////////////////////////////////////////////////////////////////////


class UserInterface;
class MikePosition;
class MikeOrder;
class MikePositionOrders;
namespace Mike {
	class UserInterfaceLinked;
}

namespace Mike {
	class IntegratorPosUI {
	public:
		IntegratorPosUI();
	private:

		Mike::UserInterfaceLinked * userInterface;
		MikePositionOrders * posOrders;

	};  //class IntegratorPosUI
}  //namespace Mike

#endif //IntegratorPosUI_h