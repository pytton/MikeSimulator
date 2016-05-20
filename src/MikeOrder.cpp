//#include "MikeOrder.h"
//#include <iostream>
//#include "MikeSimulator.h"
//#include "UserInterface.h"
//#include "WidgetTable.h"
//
//
//MikeOrder::MikeOrder(MikeSimulator * mikesim)
//{
//	//ptr_to_mikesimulator = mikesim;
//	//long orderSize = 0;
//	//long ordertype = 0;	//0-void, 1-BLMT, 2-BSTP, 3-SLMT, 4-SSTP
//	//long price = 0;
//}
//
//void MikeOrder::NewOrder(int type, long newprice)
//{
//	//using namespace std;
//	//cout << "\nNew Order Received!";
//	//ordertype = type;
//	//price = newprice;
//}
//
//void MikeOrder::PrintOrder()
//{
////	using namespace std;
////	cout << "\nOrder price: " << price << "\nOrder type: " << ordertype;
////
////	WidgetTable * myTable = ptr_to_mikesimulator->GetDisplay()->GetUInterface()->GetTable();
////	//print order in WidgetTable:
////	//find out whick row to print it in:
////	int PrintoutRow = myTable->RowOfPrice(price);
////	//change price to char array:
////	char ch[40];
////	sprintf(ch, "%d", price);
////	//print the price:
////	myTable->printInTable(PrintoutRow, 10, ch);
////	//print the order type:
////	char ch2[40];
////	sprintf(ch2, "%d", ordertype);
////
////	myTable->printInTable(PrintoutRow, 9, ch2);
////
//////	ptr_to_mikesimulator->GetDisplay()->GetWindow()->GetTable()->printInTable(10, 10, "Order");
////
//}