#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <regex>

using namespace std;

// Features loaded in from config
map<string, vector<string>> grams;

/**
 * Trim whitespace on string
 */
string trim(string& str)
{
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");

	return str.substr(start, end - start + 1);
}

/**
 * Replaces opperands with normalized code
 */
 class instructionObj{
   //class type
   public:

   //instance variables
   std::vector<string> variables; //all variables in instruction line (ex: var1, var27, etc..)
   std::vector<string> values; //all values in instruction line (ex: 0x102a, #0x80, al)
   string objOpCode; //this has strings in it (ex: lda.num.mem)
   string objGram;  //this has variables in it (ex: bcc.Var1.Var27)
   int objNumber; //distinguishes each object from one another

 //turn this into the object's constructor potentially
  instructionObj(string& instruction, int& object_number){
    //set object's objNumber
    objNumber = object_number;

    //start filling object instances with file line data
    string opcode = instruction.substr(0, instruction.find(" "));

  	string opperands = instruction.substr(opcode.size(), instruction.size());

  	// Check instructions with no opperands
  	if (opperands == "") {
  		return opcode;
  	}

  	stringstream stream(opperands);
  	string opperand;

  	// Loop through all instruction opperands
  	while (stream.good()) {
  		getline(stream, opperand, ',');
  		opperand = trim(opperand);

      //add operand to values array for current object (Needs updating)
      values.push_back(opperand);

      //USED FOR CREATING objGram
      //loop through usedValues vector to see if the opperand has been used
      int position = find(usedValues.begin(), usedValues.end(), opperand) - usedValues.begin())
      if (position < usedValues.size()){
        //variable has already been used
        //create a variable based on that index and add to current object's variables array
        string variable = "Var" + to_string(position);
        variables.push_back(variable);
      }else{
        //add opperand to end of the usedValues vector
        usedValues.push_back(opperand);
        //get index where operand was just placed in array and create variable based on it
        string variable = "Var" + to_string(usedValues.size() - 1);
        //add new variable to instruction object's variable vector (needs updating)
        variables.push_back(variable);

      }

      //USED FOR CONSTRUCTING objOpCode
  		if (opperand.substr(0, 2) == "#0") {
  			opperand = "num";
  		} else if (opperand.substr(0, 2) == "0x") {
  			opperand = "mem";
  		} else {
  			opperand = "reg";
  		}
      //start concatenating to create objGram
      objGram += "." + variable;
      //start concatenating to create opcode
  		opcode += "." + opperand;

  	}
    //assign opcode to specific object's objGram
    objOpCode = opcode;

  	return opcode;
  }
}

/**
 * Loads all the grams we want to find
 */
/*void loadGrams()
{
	ifstream file("grams.txt");
	string fileLine, sensor, gram;

	// Loop though file
	while (getline(file, fileLine)) {
		istringstream stream(fileLine);

		getline(stream, sensor, ' ');

		// Loop to load grams
		while (!stream.eof()) {
			getline(stream, gram, ' ');

			grams[sensor].push_back(gram);
		}
	}

	// Output grams
	cout << "===== LOADED GRAMS =====" << endl;

	for (auto i = grams.begin(); i != grams.end(); i++) {
		cout << i->first << endl;

		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			cout << "\t" << *j << endl;
		}
	}
}

/**
 * Start of program
 */
int main()
{
	loadGrams();

	ifstream sample("sample.txt");
	string fileLine, instructionGram;

  //list to keep track of values that have been seen
  std::vector<string> usedValues;
  int object_number = 0;
	while (getline(sample, fileLine)) {
    instructionGram = instructionObj(fileLine, object_number);
    object_number++;
    std::cout << object_number << '\n';
		//todo: check grams
	}

	// Cleanup
	sample.close();

	return 0;
}
