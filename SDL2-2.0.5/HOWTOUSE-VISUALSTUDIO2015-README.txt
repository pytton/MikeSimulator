1. Copy this whole folder into same folder as solution file
2. Copy 'SDL2.dll' file located in lib/x86 to the same folder where .exe file is located (usually 'Release' or 'Debug' folder)
3. Use files in 'PropertyPages' with Visual Studio to build your project.
4. The 'main' function has to be in its full form:	int main(int argc, char* argv[])	otherwise it will throw errors and not compile