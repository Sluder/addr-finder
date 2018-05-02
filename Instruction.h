#include <string>

class Instruction
{
	private:
		std::string opcode;
		
	public:
		Instruction(std::string opcode);
		
		// Getters & setters
		std::string getOpcode();
};