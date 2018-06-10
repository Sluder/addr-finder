#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "Control.h"
#include "Instruction.h"

using namespace std;

map<string, string> config;								// Configuration for sensor addresses
multimap<int, vector<Instruction>> controlFeatures;		// Container for found features

extern vector<string> usedValues;
extern int WINDOW_SIZE;

/**
 * Loads sensor address config
 * return : if success or not
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
	cout << "[success] Loaded config" << endl;
	
	return true;
}

/**
 * Checks if instruction operands contain a sensor address
 * return : index of sensor if found, -1 if not
 */
int inConfig(vector<int> variables)
{
	if (variables.empty()) {
		return -1;
	}
	
	map<string, string>::iterator it;
	
	for (int variable : variables) {
		for (it = config.begin(); it != config.end(); it++) {
			if (it->second == usedValues.at(variable)) {
				return distance(config.begin(), it);
			}
		}
	}

	return -1;
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
	
	cout << "[success] Loaded control features" << endl;
	
	return true;
}

/**
 * Print control file features
 */
void printControlFeatures()
{
	for (auto i : controlFeatures) {
		cout << i.first << endl;
		
		for (auto j : i.second) {
			cout << '\t' << j.gramSimple << endl;
		}
	}
}