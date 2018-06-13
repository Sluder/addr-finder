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
		string gram;					// Gram representation (Ex. lda.reg21.mem38)
		string gramSimple;				// Generic gram representation (Ex. lda.reg.mem)
		vector<int> variables; 			// Indexes of all variables in instruction
		vector<string> listOfOperands;

		Instruction(string& instruction, vector<string>& usedValues);

		int getVariable(string& operand, vector<string>& usedValues);

		string getOperandType(string& operand);

		void printVariables();

	private:
		string trim(string& str);
};
