#include <string>

#include "Instruction.h"

using namespace std;

Instruction::Instruction(string _opcode)
{
	opcode = _opcode;
}

/**
 * Getter for opcode
 */
string Instruction::getOpcode()
{
	return opcode;
}
