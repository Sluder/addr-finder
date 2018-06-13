#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "EcuFile.h"
#include "ControlFile.h"
#include "Instruction.h"

using namespace std;

vector<Instruction> ecuInstructions;
vector<string> possibleSensors;
string sensorAddress;
int sensorCounter;

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

                // Output found feature
                if (matches) {
					cout << "Found feature" << endl;

                    for (int x = 0; x <= WINDOW_SIZE; x++) {
												cout << '\t' << ecuInstructions[i + x].gramSimple << endl;
												for (int z = 0; z < ecuInstructions[i+x].listOfOperands.size(); z++){
													possibleSensors.push_back(ecuInstructions[i+x].listOfOperands.at(z));
												}
                    }
                    cout << endl;

					break;
                }
			}
		}
	}
	//count number of occurences of each operand
	sensorCounter = 0;
	int tmpCount = 0;
	for (int j = 0; j < possibleSensors.size(); j++){
		if (possibleSensors.at(j).substr(0, 2) == "0x"){
			tmpCount = count(possibleSensors.begin(), possibleSensors.end(), possibleSensors.at(j));
			if (tmpCount > sensorCounter){
				sensorCounter = tmpCount;
				sensorAddress = possibleSensors.at(j);
			}
		}
	}
	cout << "The found Sensor is: " << sensorAddress << endl;
	cout << endl;
	cout << "It occured " << sensorCounter << " times" << endl;
	cout << endl;
}
