2017/02/19
Trying to add SDL support to this solution. In order to make SDL work, the following has to be done:
/*
1. copy the directory SDL2-2.0.5, containing the lib and include files, from the zipped template file located at
C:\Users\Michael\Documents\Visual Studio 2015\My Exported Templates
to the solution directory C:\Users\Michael\Documents\Visual Studio 2015\Projects\SDL Template
2. make sure the file SDL2.dll from this folder: \SDL2-2.0.5\lib\x86
is copied to the directory of the executable file
3. also - int main function needs to be in the full form: int main(int argc, char* argv[])
using just int main() will fail
*/

2016/7/1
working on void Control::printCurrentAll()

2016/6/30
working on openPosIndex in MikePositionOrders.

lot of work done.
buying works.
selling doesn't.
I don't know why? FIX THIS!!!!

2016/05/16
Refactoring (almost?) finished.
Added new constructor for WidgetTable that enables to provide
column header names as a vector<string>,
button names as vector<string>,
number of columns and button columns as a parameter of the constructor.

finish writing SetSize so that button names are named as in the
provided vector. - DONE

2016/05/09
REFACTORING:
FROM 
{
DATA
DISPLAY
CONTROL
}
TO:
{
CONTROL(DATA, USERINTERFACE)
}

2016/04/26
Refactoring: changing the name of GetWindow function in Display class breaks it - it is not changed everywhere and has to be finished manually. Changing the name of an element in Display class - from 'window' to 'display' - works. Reverted back to version before any refactoring.
Starting to play with Visual Studio Refactoring. Compiles before starting. This archive for rollback if refactoring breaks it.

2016/04/26
Did a little work moving some public functions to private. compiles.

2016/04/20
This is work in progress. Might be broken. Go back to archive version if doesn't work.

TODO:
0. Concentrate on structure. Come up with a plan. Clean up existing code
1. DONE:Break up UserInterface.h and UserInterface.cpp into four separate files for clarity (and "one class one file" rule): 
UserInterface.h and UserInterface.cpp
WidgetTable.h and WidgetTable.cpp
2. Clean up WidgetTable - make most functions and members private, create access functions.
3. For now, implementation of functions does not have to be done - just leave a 'cout << "function such and such called" << endl;' if you need to.

2016/04/17

Builds and runs without issues
This has been put into a new solution on April 17th 2016.
Using settings that worked previously.
Headers + source files in 'src' folder.
Do not modify files in src/FLUID - these are used by FLUID, an FLTK editor.
The header file and source file in src/FLUID must be included in the project for it to work.