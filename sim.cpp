#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	// Open sample files
	ifstream sample_1, sample_2;
	sample_1.open("sample1.txt");
	sample_2.open("sample2.txt");

	string file_line;
	
	while (getline(sample_1, file_line)) {
		
	}
	
	// Cleanup
	sample_1.close();
	sample_2.close();
	
	return 0;
}