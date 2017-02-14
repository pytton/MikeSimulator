cleaning up FirstIBAPI and orgnising the source code - putting everything into one place for easy use

old readme below:
# FirstIBAPI
First IB API code that worked without thread

This code was modified from the one originally delivered by Abhijit by removing threads. It works. It connects to Interactive Brokers TWS and pulls bid/ask values for SPY.

IN ORDER TO WORK, THE 'ALLOW CONNECTIONS FROM LOCALHOST ONLY' option has to be TICKED in Interactive Brokers TWS Software. 

This code uses Jan Boonen's Libraries located here: https://github.com/JanBoonen/TwsApiCpp

This has to be cleaned - find the location of source files, change names, create new solution.

Currently, solution located here:

C:\...\FirstIBAPI\TwsApiCpp-master_New\TwsApiC++\_win32

Settings for Visual Studio:
C++/General:
Additional Include Directories:
..\..\Api
..\..\..\source\PosixClient\Shared

C++/Preprocessor:
Preprocessor Definitions:
WIN32
_DEBUG
_CRT_SECURE_NO_WARNINGS

C++/Preprocessor:
Code Generation:
Multi-threaded Debug (/MTd)

Linker/Input:
odbc32.lib
odbccp32.lib
Ws2_32.lib



