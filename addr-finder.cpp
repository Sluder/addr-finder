#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <regex>

//instruction object header file
#include "instruction-object.h"
using namespace std;

// Features loaded in from config
//map<string, vector<string>> grams;


// Loads all the grams we want to find
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
*/
int main()
{
	//loadGrams();

	ifstream sample("sample.txt");
	string fileLine, instructionGram;

  std::vector<string> usedValues; //vector to keep track of values that have been seen
  std::vector<instructionObj> objects; //vector to hold all of the instruction objects created
  int object_number = 0;
	while (getline(sample, fileLine)) {
    instructionObj foo(fileLine, object_number, usedValues);
    objects.push_back(foo);
    //std::cout << object_number << '\n'; //TEST
	  //std::cout << usedValues.front() << '\n'; //TEST
    //std::cout << foo.objGram<< '\n';  //TEST
    //std::cout << foo.objOpCode<< '\n'; //TEST
    //std::cout << objects.size()<< '\n'; //TEST
    /*if(!foo.expressions.empty()){
      std::cout << foo.expressions.front()<< '\n'; //TEST
    }*/
    object_number++;
	}

	// Cleanup
	sample.close();

	return 0;
}
