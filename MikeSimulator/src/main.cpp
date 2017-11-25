/** \mainpage

Description of this software:

A simulator to train how to trade live markets using custom designed algos;
using live data but also 'manual data' to understand what happens to algo orders when price moves.
Manual data means bid/ask prices controlled by the user - to simulate market moves I want to analyse.
There will be a lot of different algos to develop and try out
Some fully autonomous, most launched by user and used as 'bots'

Features:

Connect to Interactive brokers
Pull live market data from Interactive Brokers
Use that data for trading

*be able to:

*save that live market data to file

*use that saved data as historic data for future simulations

*be able to switch off live data and go to 'hand control' where I decide what the price does manually to check behaviour of algos

initially, fills are handled locally - all longs fill at ask and shorts at bid.
at some point, this will be changed so that fills are handled by Interactive Brokers
and this software only checks if an order was filled or not.

design considerations:

Make it easy to grow and add new feautres. \n
enable adding new algos at later stage \n
enable adding new ways to display current positions later \n
enagle adding new GUI to deal with postitions, orders and algos \n
enable adding new features to 'Data' class - trading multiple different instruments instead of just one,
saving live price streams to file, loading those streams from file - to use historical data instead of live data,
'speeding up', stopping and starting the flow of historical bid/ask prices to analyse algo behaviour using past historical data
*/


#include <iostream>

#include "FL\Fl.H"

#include "Control.h"


namespace Mike {}

int main()
{
	using namespace std;
	using namespace Mike;

	Control control;

	Fl::run();

	cout << "Hello there!" << endl;
	int a;
	cin >> a;
	return 0;
}



