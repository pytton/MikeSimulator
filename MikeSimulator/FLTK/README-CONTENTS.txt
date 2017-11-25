Everything that is needed to build FLTK	applications is here.
Compiled from fltk1.3.3
Copy this directory to the same directory in which the Visual Studio solution file is located and use property pages located in folder PropertyPages.

These libraries built using the

Multi-threaded (/MT)
and
Multi-threaded Debug (/MTd)
settings.

rebuild whole fltk libraries if you need

Multi-threaded DLL (/MD)
and
Multi-threaded Debug DLL (/MDd)

settings

Also - I renamed the file
math.h
to
Fl_math.h
because it was causing these issues:
https://stackoverflow.com/questions/26330555/fltk-in-xcode-math-h-error/44476800#44476800





Below old instructions on compiling apps with this FLTK library:


//
// In Project Properties add the following:
// Configuration Properties/ VC++ Directories/Include Directories:
// C:\code\fltkPractice\fltk-1.3.3
// Configuration Properties/ VC++ Directories/Library Directories:
// C:\code\fltkPractice\fltk-1.3.3\lib

//	C/C++ Preprocessor definitions:
//WIN32
//_DEBUG
//_WINDOWS
//
//

//
// Linker/Input/Additional Dependencies:
//fltkd.lib
//wsock32.lib
//comctl32.lib
//fltkjpegd.lib
//fltkimagesd.lib
//
// In the above - 'd' stands for debug. So fltkd.lib is debug version. release version without the 'd'
//