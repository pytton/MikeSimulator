To link this library:
Everything you need is in this library
Copy this whole folder into the same folder as the solution folder.
Make sure it is still named 'BoonenTWSAPI'
Use property sheets included in folder 'PropertySheets' with Visual Studio - everything should work.

Make sure that these directories are added to the 'additional include directories' under C/C++ properties in VS:

$(SolutionDir)\BoonenTWSAPI
$(SolutionDir)\BoonenTWSAPI\Api
$(SolutionDir)\BoonenTWSAPI\Shared

and this library to the 'Additional Library Directories under Linker properties in VS:
$(SolutionDir)\BoonenTWSAPI

and these files to 'Additional Dependencies' in Linker:

odbc32.lib;odbccp32.lib;Ws2_32.lib;%(AdditionalDependencies)
TwsApiD.lib - for Debug config
TwsApi.lib - for Release config





