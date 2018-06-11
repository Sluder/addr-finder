#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Instruction.h"
#include "ControlFile.h"
#include "EcuFile.h"

using namespace std;

vector<string> usedValues;										// Values already found & used
extern const int WINDOW_SIZE = 2;								// # of instructions to pull for feature

extern map<string, string> config;								// Defined in ControlFile.cpp
extern multimap<int, vector<Instruction>> controlFeatures;		// Defined in ControlFile.cpp
extern vector<Instruction> ecuInstructions;						// Defined in EcuFile.cpp

/**
 * Start of program
 */
int main(int argc, char* argv[])
{
	if (argc != 4) {
		cout << "Please run with args (./a.out config.txt control.txt ecu.txt)" << endl;
		return 0;
	}

	// Load everything & check for issues
	if (!loadConfig(argv[1])) {
		cout << "[error] Failed to open file " << argv[1] << endl;

	} else if (!loadControlFeatures(argv[2])) {
		cout << "[error] Failed to open file " << argv[2] << endl;

	} else if (!loadEcuInstructions(argv[3])) {
		cout << "[error] Failed to open file " << argv[3] << endl;

	} else {
		cout << endl;

		//printControlFeatures();	

		searchEcuFeatures();
	}
	
	return 0;
}