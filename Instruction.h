#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <regex>

using namespace std;

/**
 * Ex: lda, 0x102a, #0x80
 */
class Instruction {
	public:
		string opCode; 
		string gram;					// N-gram representation (Ex. lda.var1.var4)
		vector<string> variables; 		// All variables in instruction (Ex: var27)
		
		Instruction(string& instruction, vector<string>& usedValues);
		
		string getVariable(string operand, vector<string>& usedValues);
		string trim(string& str);
};
