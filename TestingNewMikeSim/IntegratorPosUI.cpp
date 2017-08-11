#include "IntegratorPosUI.h"
#include "UserInterface.h"
#include "MikePositionsOrders.h"
//#include "Contract.h"

#define MIKE_COMMENTSON true

Mike::IntegratorPosUI::IntegratorPosUI()
{
	//create the User Interface:
	userInterface = new Mike::UserInterfaceLinked();
	userInterface->callbackDest = this;  //point userInterface callbacks to this class
	userInterface->m_window1->label("Integrator 1");  //name the interface window

	//create positions:
	posOrders = new MikePositionOrders("Integrator 1", 20400);
}

void Mike::IntegratorPosUI::UserInterfaceCb(BtnPressed btn, long parameter1, long parameter2)
{
	using namespace std;

	if (MIKE_COMMENTSON)cout << "IntegratorPosUI::UserInterfaceCb called" << endl;
	if (btn == BtnPressed::EXTRABTN)
	{
		cout << "Reprice button pressed- implement this!!!!" << endl;
	//	rePriceWidTable(p);
	}
	if (btn == BtnPressed::PRINTORDERSBTN)
	{

		cout << "manualPositions->printoutAllOrders();" << endl;
		posOrders->printoutAllOrders();
		//TODO: Print orders in WidgetTable
	}
	if (btn == BtnPressed::CHECKFILLS)
	{
	//	long bidPrice, askPrice;
	//	bidPrice = data->GetBidPrice();
	//	askPrice = data->GetAskPrice();

		posOrders->checkFills(bidPrice, askPrice);
	}
	if (btn == BtnPressed::PRINTPOS)
	{
	//	long bidprice = data->GetBidPrice();
	//	long askprice = data->GetAskPrice();
		posOrders->printoutActivePositions(bidPrice, askPrice);
	}
	if (btn == BtnPressed::CANCELALLORDERS)
	{
		cout << "Cancelling all orders" << endl;
		posOrders->cancelAllOpenOrders();
		printCurrentAll();
	}
	if (btn == BtnPressed::CLEARALLPOSITIONS)
	{
		cout << "Clearing all positions" << endl;
		posOrders->clearAllPositions();
		printCurrentAll();
	}
}

//void Control::callbkWidTable(int row, int col, long price, MikeOrderType OrderTypePressed, int orderSize) {
//	using namespace std;
//
//	////PRICE GUARD - make sure orders executed at prices no better than bid/ask:
//	////This is old not needed anymore since CalcAvgPos was modified in PositionBook class
//	////if Order Type was BUY LMT and price was above current ask price, make the price equal to ask price:
//	//if (OrderTypePressed == BUYLMT) {
//	//	if (price > data->GetAskPrice()) price = data->GetAskPrice();	}
//	////if Order Type was BUY STP and price was below current ask price, make the price equal to ask price:
//	//if (OrderTypePressed == BUYSTP) {
//	//	if (price < data->GetAskPrice()) price = data->GetAskPrice();
//	//}
//	////if Order Type was SELL LMT and price was below current bid price, make the price equal to bid price:
//	//if (OrderTypePressed == SELLLMT) {
//	//	if (price < data->GetBidPrice()) price = data->GetBidPrice();
//	//}
//	////if Order Type was SELL STP and price was above current bid price, make the price equal to bid price:
//	//if (OrderTypePressed == SELLSTP) {
//	//	if (price > data->GetBidPrice()) price = data->GetBidPrice();
//	//}
//
//	//send order to OrderBook if order type is not 'cancel order':	
//	if (OrderTypePressed != CXLORDER) { manualPositions->newOrder(OrderTypePressed, price, orderSize); }
//	if (OrderTypePressed == CXLORDER) { manualPositions->cancelAllOrdAtPrice(price); }
//	//check for fills:
//	manualPositions->checkFills(data->GetBidPrice(), data->GetAskPrice());
//	MainLoop();
//	//printCurrentAll();
//}


void Mike::IntegratorPosUI::printCurrentAll()
{
}


//USERINTERFACE HANDLED HERE:
//btn chooses what to do, UserInterface *p
//provides the data, parameters optional
//void Control::CallbkUserInt(UserInterface * p, BtnPressed btn,
//	long parameter1, long parameter2, double parameter3)
//{
//
//	if (btn == BtnPressed::EXTRABTN)
//	{
//		//	cout << "Extra button pressed - implement this!!!!" << endl;
//		rePriceWidTable(p);
//	}
//	if (btn == BtnPressed::PRINTORDERSBTN)
//	{
//
//		cout << "manualPositions->printoutAllOrders();" << endl;
//		//	manualOrders->printoutAllOrders();
//		//TODO: Print orders in WidgetTable
//	}
//	if (btn == BtnPressed::CHECKFILLS)
//	{
//		long bidPrice, askPrice;
//		bidPrice = data->GetBidPrice();
//		askPrice = data->GetAskPrice();
//
//		manualPositions->checkFills(bidPrice, askPrice);
//	}
//	if (btn == BtnPressed::PRINTPOS)
//	{
//		long bidprice = data->GetBidPrice();
//		long askprice = data->GetAskPrice();
//		manualPositions->printoutActivePositions(bidprice, askprice);
//	}
//	if (btn == BtnPressed::CANCELALLORDERS)
//	{
//		cout << "Cancelling all orders" << endl;
//		manualPositions->cancelAllOpenOrders();
//		printCurrentAll();
//	}
//	if (btn == BtnPressed::CLEARALLPOSITIONS)
//	{
//		cout << "Clearing all positions" << endl;
//		manualPositions->clearAllPositions();
//		printCurrentAll();
//	}
//}