<<<<<<< HEAD
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
=======
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
		string gram;					// N-gram representation (Ex. lda.reg21.mem38)
		vector<string> variables; 		// All variables in instruction (Ex: reg3, mem72)

		Instruction(string& instruction, vector<string>& usedValues);

		string getVariable(string& operand, vector<string>& usedValues);
		string trim(string& str);
		string getOperandType(string& operand);
};
>>>>>>> ec7dfd5b8446a887b862ff8089c6cdd6a3a0dc39
