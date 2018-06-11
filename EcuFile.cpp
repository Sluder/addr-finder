#include <iostream>
#include <vector>
#include <string>

#include "EcuFile.h"
#include "ControlFile.h"
#include "Instruction.h"

using namespace std;

vector<Instruction> ecuInstructions;

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
                    }
                    cout << endl;
					
					break;
                }
			}
		}
	}
}