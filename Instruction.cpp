#include "Instruction.h"

using namespace std;

extern vector<string> usedValues;			// Defined in Main.cpp

/**
 * Constructor
 */
Instruction::Instruction(string& instruction, vector<string>& usedValues)
{
	string opcode = instruction.substr(0, instruction.find(" "));
	string operands = instruction.substr(opcode.size(), instruction.size());
	string gram = opcode;
	string gramSimple = opcode;
	vector<string> listOfOperands;

	// Cycle through opperands if they exist
	if (operands != "") {
		stringstream opStream(operands);

		while (opStream.good()) {
			string operand;

			getline(opStream, operand, ',');
			operand = trim(operand);
			listOfOperands.push_back(operand);

			// Check for arithmetic in operand
			if (operand.find('+') != string::npos) {
				stringstream expStream(operand);
				string expressionValue;
				string expressionOperandType;
				int expressionVariable;

				int counter = 0;
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
					gramSimple += "." + expressionOperandType;

					counter++;
				}
			// No arithmetic found
			} else {
				int variable = getVariable(operand, usedValues);
				string operandType = getOperandType(operand);

				this->variables.push_back(variable);

				gram += "." + operandType + to_string(variable);
				gramSimple += "." + operandType;
			}
		}
	}

	// Set values for new instruction
	this->opCode = opcode;
	this->gram = gram;
	this->gramSimple = gramSimple;
	this->listOfOperands = listOfOperands;
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
 * Removes unwanted chars on str
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

/**
 * Print variables for operands
 */
void Instruction::printVariables()
{
	for (int i = 0; i < this->variables.size(); i++) {
		cout << usedValues[this->variables[i]] << endl;
	}
}
