//This is the header file for the instruction object (ex: lda, 0x102a, #0x80)
//each line in a block of code will be an instruction object
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <regex>

using namespace std;

//INSTRUCTION OBJECT CLASS
class Instruction{
  //class type
  public:

  //instance variables
  std::vector<string> variables; //all variables in instruction line (ex: var1, var27, etc..)
  std::vector<string> values; //all values in instruction line (ex: 0x102a, #0x80, al)
  string opCode; //this has strings in it (ex: lda.num.mem)
  string Gram;  //this has variables in it (ex: bcc.Var1.Var27)
  int objNumber; //distinguishes each object from one another
  bool noOperands; //distinuguishes if a instruction line has operands or not (ex: bcc[true] or lda al, 0x102f[false])
  std::vector<string> expressions; //if arithmetic is used in any operand, the expression is stored here

  //turn this into the object's constructor potentially
  Instruction(string& instruction, int& object_number,vector<string>& usedValues){
    //set object's objNumber
    objNumber = object_number;

    //start filling object instances with file line data
    string opcode = instruction.substr(0, instruction.find(" "));
    Gram = opcode;
  	string operands = instruction.substr(opcode.size(), instruction.size());
    string operand;
  	// Check instructions with no operands
  	if (operands == "") {
  		opCode = opcode;
      noOperands = true; //this instruction does not have operands
  	}else{

      stringstream stream(operands);

      // Loop through all instruction operands
      while (stream.good()) {
        getline(stream, operand, ',');
        operand = trim(operand);
        int counter; //used for determining the position of the '+' sign
        //check to see if operand contains arithmetic or not (ex: dp + 0x03 + ix)
        if (operand.find('+') != std::string::npos){ //check for all types of arithmetic (UPDATE AT SOME POINT)
          expressions.push_back(operand); //operand contains arithemic (add to vector)
          string expression_value;
          string expression_variable;
          counter = 0; //reset for each new arithmetic operand
          //std::cout << expression<< '\n'; //TEST

          stringstream stream2(operand);
          while (stream2.good()){
            getline(stream2, expression_value, '+');
            expression_value = trim(expression_value);
            //add operand to values array for current object (Needs updating)
            values.push_back(expression_value);

            //USED FOR CREATING Gram
            //loop through usedValues vector to see if the operand has been used
            int position = find(usedValues.begin(), usedValues.end(), expression_value) - usedValues.begin();
            if (position < usedValues.size()){
              //variable has already been used
              //create a variable based on that index and add to current object's variables array
              expression_variable = "Var" + to_string(position);
              variables.push_back(expression_variable);
            }else{
              //add operand to end of the usedValues vector
              usedValues.push_back(expression_value);
              //get index where operand was just placed in array and create variable based on it
              expression_variable = "Var" + to_string(usedValues.size() - 1);
              //add new variable to instruction object's variable vector (needs updating)
              variables.push_back(expression_variable);
            }
            if (counter <= 0){
              Gram += "." + expression_variable;
            }else{
              Gram += " + " + expression_variable;
            }
            counter++; //increment fo proper arithmetic symbol position
          }
        }else{

          string variable; //instantiate variable
          //add operand to values array for current object (Needs updating)
          values.push_back(operand);

          //USED FOR CREATING Gram
          //loop through usedValues vector to see if the operand has been used
          int position = find(usedValues.begin(), usedValues.end(), operand) - usedValues.begin();
          if (position < usedValues.size()){
            //variable has already been used
            //create a variable based on that index and add to current object's variables array
            variable = "Var" + to_string(position);
            variables.push_back(variable);
          }else{
            //add operand to end of the usedValues vector
            usedValues.push_back(operand);
            //get index where operand was just placed in array and create variable based on it
            variable = "Var" + to_string(usedValues.size() - 1);
            //add new variable to instruction object's variable vector (needs updating)
            variables.push_back(variable);
          }

          //USED FOR CONSTRUCTING opCode
          if (operand.substr(0, 2) == "#0") {
            operand = "num";
          } else if (operand.substr(0, 2) == "0x") {
            operand = "mem";
          } else {
            operand = "reg";
          }
          //start concatenating to create Gram
          Gram += "." + variable;
          //start concatenating to create opcode
          opcode += "." + operand;

          //assign opcode to specific object's Gram
        }
      }
      opCode = opcode;
      noOperands = false; //this instruction has operands
    }
  }
  //Trim function used in Instruction constructor
  string trim(string& str)
  {
      size_t start = str.find_first_not_of(" ");
      size_t end = str.find_last_not_of(" ");

  	return str.substr(start, end - start + 1);
  }
};
