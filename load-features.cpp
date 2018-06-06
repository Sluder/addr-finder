#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Instruction.h"

using namespace std;

map<string, string> config;				// Defined sensor addresses
vector<vector<Instruction>> features;	// Container for found features
vector<string> usedValues;				// Values already found & used

/**
 * Loads sensor address config
 */
void loadConfig()
{
	ifstream file("config.txt");
	string sensor, addr;
	
	while (file >> sensor >> addr) {
		config[sensor] = "0x" + addr;
	}
}

/**
 * Checks if instruction operands contain a sensor address
 */
bool inConfig(vector<int> variables)
{
	for (int variable : variables) {
		for (auto const& i : config) {
			if (i.second == usedValues.at(variable)) {
				return true;
			}
		}
	}
	
	return false;
}

int main()
{
	loadConfig();
	
	ifstream sample("sample.txt");
	string fileLine;
	
	while (getline(sample, fileLine)) {
		Instruction tmp(fileLine, usedValues);
		
		if (inConfig(tmp.variables)) {
			cout << tmp.gram << endl;
		}
	}
	
	return 0;
}