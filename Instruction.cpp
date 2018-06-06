#include "Instruction.h"

using namespace std;

/**
 * Constructor
 */
Instruction::Instruction(string& instruction, vector<string>& usedValues)
{
	string opcode = instruction.substr(0, instruction.find(" "));
	string operands = instruction.substr(opcode.size(), instruction.size());
	string gram = opcode;
	string operand;

	// Cycle through opperands if they exist
	if (operands != "") {
		stringstream opStream(operands);

		int counter;
		while (opStream.good()) {
			getline(opStream, operand, ',');
			operand = trim(operand);

			// Check for arithmetic
			if (operand.find('+') != string::npos) {
				stringstream expStream(operand);
				string expressionValue;
				string expressionOperandType;
				int expressionVariable;

				counter = 0;
				while (expStream.good()) {
					getline(expStream, expressionValue, '+');
					expressionValue = trim(expressionValue);

					expressionVariable = getVariable(operand, usedValues);
					this->variables.push_back(expressionVariable);

					expressionOperandType = getOperandType(operand);


					// Update gram representation
					if (counter <= 0) {
						gram += "." + expressionOperandType + to_string(expressionVariable);
					} else {
						gram += "+" + expressionOperandType + to_string(expressionVariable);
					}

					counter++;
				}
			// No arithmetic found
			} else {
				int variable = getVariable(operand, usedValues);
				string operandType = getOperandType(operand);
				
				this->variables.push_back(variable);

				gram += "." + operandType + to_string(variable);
			}
		}
	}

	// Set values for new instruction
	this->opCode = opcode;
	this->gram = gram;
}

/**
 * Checks if variable exists, if not start tracking it
 */
int Instruction::getVariable(string& operand, vector<string>& usedValues)
{
	int position = find(usedValues.begin(), usedValues.end(), operand) - usedValues.begin();

	if (position < usedValues.size()) {
		return position;
	}

	usedValues.push_back(operand);

	return usedValues.size() - 1;
}

/**
 * Removes unwated chars on str
 */
string Instruction::trim(string& str)
{
	size_t start = str.find_first_not_of(" ");
	size_t end = str.find_last_not_of(" ");

	str.erase(remove(str.begin(), str.end(), '\t'), str.end());
	str.erase(remove(str.begin(), str.end(), '\r'), str.end());
	str.erase(remove(str.begin(), str.end(), '\n'), str.end());
	
	return str.substr(start, end - start + 1);
}

/**
 * Gets the type of operand for gram
 */
string Instruction::getOperandType(string& operand)
{
	if (operand.substr(0, 2) == "#0") {
		return "con";
	} else if (operand.substr(0, 2) == "0x") {
		return "mem";
	}

	return "reg";
}
