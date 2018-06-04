#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <regex>

using namespace std;

// Grams loaded in from config
vector< vector<string> > grams;

/**
 * Trim whitespace on string
 */
string trim(string& str)
{
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");

	return str.substr(start, end - start + 1);
}

/**
 * Replaces opperands with normalized code
 */
string createGram(string& instruction)
{
	string opcode = instruction.substr(0, instruction.find(" "));
	string opperands = instruction.substr(opcode.size(), instruction.size());

	// Checks instructions with no opperands
	if (opperands == "") {
		return opcode;
	}
	
	stringstream stream(opperands);
	string opperand;

	// Loop through all instruction opperands
	while (stream.good()) {
		getline(stream, opperand, ',');
		opperand = trim(opperand);

		if (opperand.substr(0, 2) == "#0") {
			opperand = "num";
		} else if (opperand.substr(0, 2) == "0x") {
			opperand = "mem";
		} else {
			opperand = "reg";
		}

		opcode += "." + opperand;
	}

	return opcode;
}

/**
 * Loads all the grams from config
 */
void loadGrams()
{
	ifstream file("grams.txt");
	string fileLine, sensor, gram;

	// Loop though file
	while (getline(file, fileLine)) {
		istringstream stream(fileLine);
		
		getline(stream, sensor, ' ');
		
		// Loop to load grams
		while (!stream.eof()) {
			getline(stream, gram, ' ');
			
			grams[sensor].push_back(gram);
		}
	}

	// Output grams
	cout << "===== LOADED GRAMS =====" << endl;
	
	for (auto i = grams.begin(); i != grams.end(); i++) {
		cout << i->first << endl;
		
		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			cout << "\t" << *j << endl;
		}
	} 
}

/**
 * Start of program
 */
int main()
{
	loadGrams();
	
	ifstream sample("sample.txt");
	string fileLine, instructionGram;
	
	vector<string> stack;

	while (getline(sample, fileLine)) {
		instructionGram = createGram(fileLine);
		
		for (auto i = grams.begin(); i != grams.end(); i++) {
			for (auto j = i->second.begin(); j != i->second.end(); j++) {
				cout << "\t" << *j << endl;
			}
		}
	}

	// Cleanup
	sample.close();

	return 0;
}