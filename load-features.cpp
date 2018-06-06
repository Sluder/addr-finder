#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Instruction.h"

using namespace std;

map<string, string> config;
vector<vector<Instruction>> features;

/**
 * Loads sensor address config
 */
void loadConfig()
{
	ifstream file("config.txt");
	string sensor, addr;
	
	while (file >> sensor >> addr) {
		config[sensor] = addr;
	}
}

int main()
{
	loadConfig();
	
	ifstream sample("sample.txt");
	string fileLine;
	
	
	return 0;
}