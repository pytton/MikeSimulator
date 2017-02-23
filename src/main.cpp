//
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
////MOVED EVERYTHING FROM HERE TO ThreadMainFunction.cpp on 22/02/2017. Code below works without issues.
////Commented out for experiments.
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////FluidInterface.h and FluidInterface.cxx - these two files are generated by Fluid - DO NOT MODIFY THEM!
////UserInterface.h and UserInterface.cpp - these are the two main files implementing the User interface
////UserInterface class is derived from FluidInterface class
////add/remove elements in the UserInterface class constructor using delete and new
//
////TODO:
//
////add a Control class where the main program will run
////add an Algo class which will house all the algos and be accessed by Control - this is where trading decisions are made
////add a Data class which will deal with all the data - at first loaded from a file into some structure database
////at a later point the Data class will be getting a live feed from Interactive Brokers
////connect all the classes with pointers so they know about each other's existance - possibly through just one class
//
////first algo to write - something very very simple like a stupid scalper without any guards
//
////problems with SDL2: LNK1561: entry point must be defined? Solution here:
////http://stackoverflow.com/questions/18672303/sdl2-lnk1561-entry-point-must-be-defined
////https://www.google.com/search?q=sdl+entry+point+must+be+defined&oq=sdl+entry+poi&aqs=chrome.1.69i57j69i59.3847j0j4&sourceid=chrome&ie=UTF-8
//
//
//#include <time.h>
//#include <iostream>
//#include <iomanip>
//#include <thread>
//#include <string>
//
//#include <SDL.h>
//
//#include "MikeSimulator.h"
//
//
//class MikeSimulator;
//std::string UTCTime();
//
//using namespace std;
//
//void MikeCallback(void* p)
//{
//	using namespace std;
//	cout << setprecision(15) << "\nXXXXXXX MAIN CALLBACKXXXXXXXXXX " << UTCTime() << endl;
//	Fl::repeat_timeout(1.0, MikeCallback);
//}
//
//int mikesimulator();
//
//using namespace std;
//
//int main(int argc, char* argv[]) {
//
//	const int SCREEN_WIDTH = 800;
//	const int SCREEN_HEIGHT = 600;
//
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		cout << "SDL init failed." << endl;
//		return 1;
//	}
//
//	SDL_Window *window = SDL_CreateWindow("Particle Fire Explosion",
//		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
//		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//
//	if (window == NULL) {
//		SDL_Quit();
//		return 2;
//	}
//
//	bool quit = false;
//
//	SDL_Event event;
//
//	while (!quit) {
//		// Update particles
//		// Draw particles
//		// Check for messages/events
//
//		while (SDL_PollEvent(&event)) {
//			if (event.type == SDL_QUIT) {
//				quit = true;
//			}
//		}
//	}
//
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//	//mikesimulator();
//
//	return 0;
//}
//
//int mikesimulator()
//{
//	int starting_bid = 20415;
//	//std::cin >> starting_bid;
//	MikeSimulator * mikesimulator = new MikeSimulator(starting_bid);
//
////	MikeSimulator mikesimulator(starting_bid);
//
//	Fl::add_timeout(1.0, MikeCallback/*, (void*)mikesimulator*/);
//
//	return Fl::run();
//
//
//}
