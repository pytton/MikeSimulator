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

enum class BtnPressed;
class UserInterface;
class MikePosition;
class MikeOrder;
class MikePositionOrders;
namespace Mike {
	class UserInterfaceLinked;
}

namespace Mike {
	//integrates MikePositionOrders with a user interface derived from UserInterfaceBase
	class IntegratorPosUI {
		friend class UserInterfaceLinked;
	public:
		IntegratorPosUI();

		//getters/setters:
		MikePositionOrders * getPosOrders() { return posOrders; }
	private:

		Mike::UserInterfaceLinked * userInterface;
		MikePositionOrders * posOrders;

	public:
		//callbacks:
		void UserInterfaceCb(BtnPressed btn, long parameter1 = 0, long parameter2 = 0);

		void printCurrentAll();
		void update(long bidprice, long askprice);

		//bid prices:
		long bidPrice =0, askPrice=0, prevBidPrice=0, prevAskPrice=0;

	};  //class IntegratorPosUI
}  //namespace Mike

#endif //IntegratorPosUI_h