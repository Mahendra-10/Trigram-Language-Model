#include "language_model.h"

#include <iostream>

#include <fstream>

#include <string>

#include <map>

using namespace std;

int main(int argc, char * argv[]) {
  std::ifstream myFile;

  map < tuple < string, string, string > , int > myMap;
  if (argc > 1) {
    myFile.open(argv[1]);
    if (myFile.is_open()) { // checking if the filelist opens
      std::string line;
      while (myFile >> line) { // reading files in filelist
        std::ifstream fileToOpen(line);
        if (fileToOpen.is_open()) {
          fileToOpen.close();

          readTrigrams(line, myMap); // Call the trigram function

        } else {
        
          cerr << "Invalid file: " << line << endl;
          
        }
      }
      myFile.close();
    } else {
      cerr << "Invalid file list: " << argv[1] << endl;
      return 1;
    }

  }

  if (argv[2][0] == 'f' && argc < 5) { //makes sure users input two more args if command f
    cerr << "Invalid argument list: f requires two additional command-line arguments" << endl;
    return 1;
  }

  trigram(myMap, argv[2][0], argv);
  return 0;
}