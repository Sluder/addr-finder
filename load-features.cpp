#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Instruction.h"

using namespace std;

map<string, string> config;								// Defined sensor addresses
multimap<int, vector<Instruction>> controlFeatures;		// Container for found features
vector<string> usedValues;								// Values already found & used

const int WINDOW_SIZE = 2;								// # of instructions to pull for feature

/**
 * Checks if instruction operands contain a sensor address
 * return : index of sensor if found, -1 if not
 */
int inConfig(vector<int> variables)
{
	map<string, string>::iterator it;
	
	for (int variable : variables) {
		for (it = config.begin(); it != config.end(); it++) {
			if (it->second == usedValues.at(variable)) {
				return distance(config.begin(),it);
			}
		}
	}

	return -1;
}

/**
 * Loads sensor address config
 */
bool loadConfig(string fileName)
{
	ifstream configFile(fileName);
	string sensor, addr;
	
	// Check if file was successfully opened
	if (configFile.fail()) {
		return false;
	}
	
	while (configFile >> sensor >> addr) {
		if (addr.substr(0, 2) != "0x") {
			addr = "0x" + addr;
		}
		config[sensor] = addr;
	}
	
	configFile.close();
	
	return true;
}

/**
 * Loads control features
 * return : if success or not
 */
bool loadControlFeatures(string fileName)
{
	ifstream controlFile(fileName);
	string fileLine;
	
	// Check if file was successfully opened
	if (controlFile.fail()) {
		return false;
	}
	
	// Loop through instructions to find sensors
	while (getline(controlFile, fileLine)) {
		Instruction tmp(fileLine, usedValues);
		int index, instructionCount = 0;

		index = inConfig(tmp.variables);

		// If operands contain an address
		if (index >= 0) {
			vector<Instruction> container;
			container.push_back(tmp);

			// Grab grams to create feature
			while (instructionCount < WINDOW_SIZE) {
				getline(controlFile, fileLine);
				
				Instruction tmp2(fileLine, usedValues);
				container.push_back(tmp2);
				
				cout << tmp2.gramSimple << endl;

				// Reset counter if sensor appears in window
				if (inConfig(tmp2.variables) >= 0) {
					instructionCount = 0;
				} else {
					instructionCount++;
				}
			}
			
			// Finish & reset
			controlFeatures.insert(make_pair(index, container));
			instructionCount = 0;
			container.clear();
		}
	}
	
	controlFile.close();
	
	return true;
}

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
		cout << "Failed to open file " << argv[1] << endl;

	} else if (!loadControlFeatures(argv[2])) {
		cout << "Failed to open file " << argv[2] << endl;
	}
	
	return 0;
}