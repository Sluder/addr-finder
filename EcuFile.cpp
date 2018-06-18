#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "EcuFile.h"
#include "ControlFile.h"
#include "Instruction.h"

using namespace std;

extern map<string, string> config;							// Defined in ControlFile.cpp
extern multimap<int, vector<Instruction>> controlFeatures;	
extern vector<string> usedValues;							// Defined in Main.cpp
extern int WINDOW_SIZE;									

vector<Instruction> ecuInstructions;
vector<vector<string>> possibleSensors(config.size());

/**
 * Loads instructions from file in question
 * return : if success or not
 */
bool loadEcuInstructions(string fileName)
{
	ifstream ecuFile(fileName);
	string fileLine;

	// Check if file was successfully opened
	if (ecuFile.fail()) {
		return false;
	}

	while (getline(ecuFile, fileLine)) {
		ecuInstructions.push_back(Instruction(fileLine, usedValues));
	}

	ecuFile.close();
	cout << "[success] Loaded ECU instructions" << endl;

	return true;
}

/**
 * Searches ECU file for matching features
 */
void searchEcuFeatures()
{
	for (int i = 0; i < ecuInstructions.size(); i++) {
		for (auto j : controlFeatures) {
			bool matches = true;
			possibleSensors.push_back(vector<string>());
			
			// Instruction matches first item in feature
			if (ecuInstructions[i].gramSimple == j.second.front().gramSimple) {
				for (int k = 0; k < WINDOW_SIZE; k++) {
                    // This block doesnt match w/ the control feature
                    if (j.second[k + 1].gramSimple != ecuInstructions[(i + 1) + k].gramSimple) {
                        matches = false;
                        break;
                    }
                }

                // Operate on found feature
                if (matches) {
					for (int z = 0; z < ecuInstructions[i].listOfOperands.size(); z++) {
						// Save possible sensor addresses
						if (ecuInstructions[i].listOfOperands.at(z).substr(0, 2) == "0x") {
							possibleSensors[j.first].push_back(ecuInstructions[i].listOfOperands.at(z));
						}
					}
                } // end if
			}
		} //end j for
	}
	
	outputResults();
}

/**
 * Output possible sensor addresses
 */
void outputResults()
{
	map<string, int> counters;
	
	// Loop through config
	for (map<string, string>::iterator it = config.begin(); it != config.end(); it++) {
		string maxAddr;
		int maxCount = 0;
		
		// Check for empty possible sensors
		if (possibleSensors[distance(config.begin(), it)].empty()) {
			printf("%-15s : %-15s\n",  it->first.c_str(), "Not found");
			continue;
		}

		// Figure out sensor counts
		for (int i = 0; i < possibleSensors[distance(config.begin(), it)].size(); i++) {
			counters[possibleSensors[distance(config.begin(), it)][i]]++;
			
			if (counters[possibleSensors[distance(config.begin(), it)][i]] > maxCount) {
				maxAddr = possibleSensors[distance(config.begin(), it)][i];
				maxCount = counters[possibleSensors[distance(config.begin(), it)][i]];
			}
		}
		
		printf("%-15s : %-15s\n", it->first.c_str(), maxAddr.c_str());
		counters.clear();
	}
}
