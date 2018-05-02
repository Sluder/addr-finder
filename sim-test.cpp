#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

#include "Instruction.h"

using namespace std;

int main()
{
	vector<Instruction*> instructions;
	cout << explode("t t", ' ') << endl;
	// Open sample files
	ifstream sample_1, sample_2;
	sample_1.open("sample1.txt");
	sample_2.open("sample2.txt");

	// Loop through instructions
	string file_line, opcode;
	
	while (getline(sample_1, file_line)) {
		opcode = file_line.substr(0, file_line.find(" "));
		opperands = file_line.substr(opcode.size(), file_line.size());

		instructions.push_back(new Instruction(opcode));
	} 

	
	// Cleanup
	sample_1.close();
	sample_2.close();
	
	return 0;
}