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
				string expressionVariable;

				counter = 0;
				while (expStream.good()) {
					getline(expStream, expressionValue, '+');
					expressionValue = trim(expressionValue);

					expressionVariable = getVariable(operand, usedValues);
					this->variables.push_back(expressionVariable);

					expressionOperandType = getOperandType(operand);


					// Update gram representation
					if (counter <= 0) {
						gram += "." + expressionOperandType + expressionVariable;
					} else {
						gram += "+" + expressionOperandType + expressionVariable;
					}

					counter++;
				}
			// No arithmetic found
			} else {
				string variable = getVariable(operand, usedValues);
				string operandType = getOperandType(operand);
				
				this->variables.push_back(variable);

				gram += "." + operandType + variable;
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
string Instruction::getVariable(string& operand, vector<string>& usedValues)
{
	int position = find(usedValues.begin(), usedValues.end(), operand) - usedValues.begin();

	if (position < usedValues.size()) {
		return to_string(position);
	}

	usedValues.push_back(operand);

	return to_string(usedValues.size() - 1);
}

/**
 * Removes spaces on string ends
 */
string Instruction::trim(string& str)
{
	size_t start = str.find_first_not_of(" ");
	size_t end = str.find_last_not_of(" ");

	return str.substr(start, end - start + 1);
}

/**
 * Gets the type of operand 
 */
string Instruction::getOperandType(string& operand)
{
	// Check substring for gram
	if (operand.substr(0, 2) == "#0") {
		return "con";
	} else if (operand.substr(0, 2) == "0x") {
		return "mem";
	}

	return "reg";
}
