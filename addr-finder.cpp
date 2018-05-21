#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <regex>

using namespace std;

/**
 * Trim whitespace on string
 */
string trim(string& str)
{
    size_t startpos = str.find_first_not_of(" ");
    size_t endpos = str.find_last_not_of(" ");
	
	return str.substr(startpos, endpos - startpos + 1);
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
 * Start
 */
int main()
{
	// Open sample files
	ifstream sample;
	sample.open("sample.txt");

	// Loop through instructions
	string file_line, opcode, opperands;
	
	while (getline(sample, file_line)) {
		file_line = createGram(file_line);
	}
	
	// Cleanup
	sample.close();
	
	return 0;
}