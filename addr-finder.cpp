#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <regex>

using namespace std;

// Features loaded in from config
map<string, vector<string>> features;

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
 * Loads all the features we want to find
 */
void loadFeatures()
{
	ifstream file("features.txt");
	string file_line, sensor, gram;

	// Loop though file
	while (getline(file, file_line)) {
		istringstream stream(file_line);
		
		getline(stream, sensor, ' ');
		
		// Loop to load grams
		while (!stream.eof()) {
			getline(stream, gram, ' ');
			
			features[sensor].push_back(gram);
		}
	}

	// Output features
	cout << "===== LOADED FEATURES =====" << endl;
	for (auto i = features.begin(); i != features.end(); i++) {
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
	loadFeatures();
	
	ifstream sample("sample.txt");

	string file_line;

	while (getline(sample, file_line)) {
		file_line = createGram(file_line);
	}

	// Cleanup
	sample.close();

	return 0;
}