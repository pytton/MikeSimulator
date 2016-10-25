#ifndef _ORDERBOOKPROTOTYPE_H_INCLUDED_
#define _ORDERBOOKPROTOTYPE_H_INCLUDED_

#include <vector>
#include <unordered_set>
#include <set>
#include <iostream>

class MikeOrder;
class MikeOrdersAtPrice;
class MikePositionOrders;
class PositionBook;

enum BtnPressed;
enum MikeOrderType;

	class OrderbookPrototype
	{
	private:
		void fill(int assignedtopos, int fillprice, int orderamount, long bidPrice, long askPrice);// { std::cout << "\nImplement filling orders!!!" << std::endl; }
	public:

		OrderbookPrototype(MikePositionOrders * p_mikepositionorders, long highestprice);
//		OrderbookPrototype(::PositionBook * positionbook);
		~OrderbookPrototype();



		int neworder(MikeOrderType type, long orderPrice, long orderAmount);//creates a new order and returns the OrderId of the just created order to the caller of the function
		void checkfills(long bidPrice, long askPrice);//checks fills of open orders
		void cancelordersatprice(int price);//checks all open orders at price and cancels them
//		OrderStatus checkstatusoforder(long orderID);//returns an enum: open, filled, partial fill, cancelled
		MikeOrdersAtPrice totOrdAmtatPrice();
		void updateOpenOrdersByPrice();//copied from MikePositionOrders
		void printoutAllOrders();//prototype function to print out all orders in the console:

		const std::vector <MikeOrdersAtPrice> * GetOpOrdersbyPrice() { return &openOrdersByPrice;  }

		void modifyorder(long orderID);//modifies order pointed to by orderID
		void cancelorder(long orderID);//cancels order pointed by orderID

		


	private:

		MikePositionOrders * mypositionorders;//pointer to the positionbook which will be affected by orders in this orderbook
		std::vector <MikeOrder> allOrders;//this stores ALL the orders ever entered - both the ones not filled yet, filled ones, cancelled and everything else. The index of this vector HAS TO MATCH the OrderId of the order - this is ensured by the implementation.
		std::set <int> indexOpenOrd;//index stores OrderIds of open orders in allorders vector. So if it has only two elements: eg. 4 and 72, then the orderId of open orders are 4 and 72. This can be used to access the allorders vector at locations 4 and 72 to get only the open orders - this is used for speed - instead of going through hundreds of past and current orders and finding which one is open, which one is closed and which one cancelled - we only have to access two. The implementation of this class has to ensure that this index is kept current ALL the time. This index also stores partial fills as of now.
		std::unordered_set <int> indexClosedOrd;//index stores OrderIds locations of closed orders in allorders vector. For now it also stores all the cancelled orders. Partial fills will still be kept in the indexOpenOrd index.
		std::vector<MikeOrdersAtPrice> openOrdersByPrice;//this vector stores all the currently open orders sorted by their price. this is used to print out open orders in WidgetTable. Might be used by algos at later stage to eg. determine maximum possible P/L taking into account currently open orders. This has to be kept current by the implementation!
		int newOrderId = 0;//this for generating OrderIds for new orders. Used by allOrders vector and indexes. Crucial for proper operation of indexOpenOrd. THIS IS CRUCIAL to ensure that the index of the allOrders vector matches the OrderId of the Order stored under that index. Eg. allOrders.at(234) should store an order with OrderId = 234

	};






#endif //_ORDERBOOKPROTOTYPE_H_INCLUDED_