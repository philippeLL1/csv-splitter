#include <locale>
#include <sys/stat.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

bool isNumeric(const string& stringToCheck);

int main(int argc, char** argv) {
 
  // validation of cmd-line arguments 
  if (argc != 4) {
    cout << "Usage: csv-splitter NameOfFile NumberOfLinesPerSplit NumberOfSplits" << endl;
    return 1;
  } else if (!(isNumeric(argv[2]) && isNumeric(argv[3]))) {
    cout << "The arguments for NumberOfLinesPerSplit and NumberOfSplits must be integers" << endl;
    return 1;
  }

  // rename cmd-line arguments  
  const string INPUTFILE = argv[1];
  const int NUM_LINES = stoi(argv[2]);
  const int NUM_FILES = stoi(argv[3]);

  // open file and check for success
  ifstream infile(INPUTFILE);
  if (!infile.good()) {
    cout << "Error opening the file" << endl;
    return 2;
  }

  ofstream outfile;
  string line;
  
  // store the header as it must be included in each csv file created
  string header;
  getline(infile, header);

  for (int i = 0; i < NUM_FILES; i++) {
    // open a new file
    string filename = INPUTFILE + "-split-" + to_string(i) + ".csv";
    outfile.open(filename, ios::ate);
    
    // adds header to beginning, before reading lines
    outfile << header;

    // write to the new file
    for (int j = 0; j < NUM_LINES; j++) {
      if (getline(infile, line)) {
        outfile << line;
      }
    }

    outfile.close();
  }


  infile.close();
  return 0;
}

// Helper for input validation
bool isNumeric(const string& stringToCheck) {
  // check each character individually
  for (char const& character : stringToCheck) {
    if (isdigit(character) == 0) {
      return false;
    }
  }

  return true;
 }


