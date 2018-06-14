#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "EcuFile.h"
#include "ControlFile.h"
#include "Instruction.h"

using namespace std;

vector<Instruction> ecuInstructions;
multimap<int, string> possibleSensors;

extern vector<string> usedValues;
extern multimap<int, vector<Instruction>> controlFeatures;
extern int WINDOW_SIZE;

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
	int sensorCounter = 0;
	
	for (int i = 0; i < ecuInstructions.size(); i++) {
		for (auto j : controlFeatures) {
			bool matches = true;

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
                    for (int x = 0; x <= WINDOW_SIZE; x++) {
						for (int z = 0; z < ecuInstructions[i + x].listOfOperands.size(); z++) {
							// Save possible sensor addresses
							if (ecuInstructions[i + x].listOfOperands.at(z).substr(0, 2) == "0x") {
								possibleSensors.emplace(j.first, ecuInstructions[i + x].listOfOperands.at(z)));
							}
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
	// Count the number of occurences of each operand and find the one with the most occurences
	/* for (int j = 0; j < possibleSensors.size(); j++) {
		if (possibleSensors.[j].substr(0, 2) == "0x") {
			int tmpCount = count(possibleSensors.begin(), possibleSensors.end(), possibleSensors.at(j));
			
			if (tmpCount > sensorCounter){
				sensorCounter = tmpCount;
				sensorAddress = possibleSensors.at(j);
			}
		}
	} */
}
