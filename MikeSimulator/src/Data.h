#pragma once

#include "FLUID\FluidPriceControl.h"

namespace Mike {
	enum class DataUIButton {
		UPBTN,
		DWNBTN,
		SLIDER,
		EMPTY
	};

	/*! Simple struct holding buttons/events pressed by user. */
	struct DataUIEvent
	{
		DataUIButton mButtonPressed;
	};


	class DataUI :public FluidPriceControlUI {
	public:
		DataUI();
	};

	/**
	Class designed for handling market data. Connects to Interactive Brokers to pull live bid/ask prices. Contains OrderServer(currently local dummy) which sends orders to the market and checks if they are filled.*/
	class Data {
		/*! DataUI is an FLTK window controlling the Data class */
		//typedef FluidPriceControlUI DataUI;
	public:
		Data();
		~Data();
	private:
		/*!
		DataUI is a User Interface Window used to control everything associated with market price data.
		This is designed to grow. Market price data can be either pulled from Interactive Brokers using
		Jan Boonen's library or it can be switched to 'manual' to explore behaviour of algos.
		*/
		DataUI * dataControlWindow;
	};

}//namespace Mike