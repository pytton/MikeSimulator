


//adding support for threading as learned from here:
//https://www.youtube.com/watch?v=3ZxZPeXPaM4&index=2&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M#t=0.8330174
//code for that experiment can be found in Learning notebook solution under BoQianThreading


#include <time.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>

#include <SDL.h>

#include "MikeSimulator.h"
#include "MikeTimer.h"

using namespace std;

class MikeSimulator;

class LogFile {//temporary now. just to understand how threading works. Refto this class will be passed to both threads
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}//needs a destructor
	~LogFile() {
		f.close();
	}
	void shared_print(string printout)
	{
		std::lock_guard<std::mutex> locker(m_mutex);	//RAII//exception safe
		f << printout << endl;
		cout << printout << endl;

	}
	void shared_print(string id, int value)
	{
		std::lock_guard<std::mutex> locker(m_mutex);	//RAII//exception safe
		f << "From: " << id << ": " << value << endl;
		cout << "From: " << id << ": " << value << endl;

	}
	//Never return f to the outside world
	ofstream& getSream() { return f; }
	//Never pass f as an argument to user provided function - this enables access to it outside of mutex
	void processf(void fun(ofstream&))
	{
		fun(f);
	}

};

std::string UTCTime();
void MikeCallback(void* p);
int sdlWindowStart(LogFile &log);

int mikesimulator(LogFile &log)
{
	int starting_bid = 20415;
	//std::cin >> starting_bid;
	MikeSimulator * mikesimulator = new MikeSimulator(starting_bid);

//	Fl::add_timeout(1.0, MikeCallback/*, (void*)mikesimulator*/);

	return Fl::run();
}

int main(int argc, char* argv[]) {

	LogFile log;

	std::thread t1(mikesimulator,std::ref(log) );


	//uncomment below for sdl in seperate thread:
	//try {
	//	sdlWindowStart(log);
	//}
	//catch (...){
	//	t1.join();
	//	throw;
	//}

	t1.join();

	

//	mikesimulator(log);

	return 0;
}

int sdlWindowStart(LogFile &log)
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL init failed." << endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Particle Fire Explosion",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		SDL_Quit();
		return 2;
	}

	bool quit = false;

	SDL_Event event;

	Timer timer;

	while (!quit) {
		// Update particles
		// Draw particles
		// Check for messages/events

		//if (timer.elapsed() > 1000) {
		//	cout << "From SDL: " << endl;
		//	timer.print();
		//	timer.reset();
		//}
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}

void MikeCallback(void* p)
{
	using namespace std;
	cout << setprecision(15) << "\nXXXXXXX MAIN CALLBACKXXXXXXXXXX " << UTCTime() << endl;
	Fl::repeat_timeout(1.0, MikeCallback);
}

