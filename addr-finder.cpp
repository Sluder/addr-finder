#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <regex>

#include "Instruction.h"

using namespace std;

vector<Instruction> instructions;	// Instruction objects
vector<string> usedValues;			// Keep track of values used by instructions

int main()
{
	ifstream sample("sample.txt");
	string fileLine;

	// Load all instructions
	while (getline(sample, fileLine)) {
		Instruction tmp(fileLine, usedValues);
		instructions.push_back(tmp);

		cout << fileLine << endl;
		cout << "Gram: " <<  tmp.gram << endl;
		cout << endl;
	}

	// Cleanup
	sample.close();

	return 0;
}
