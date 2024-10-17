#include "language_model.h"

#include <iostream>

#include <sstream>

#include <vector>

#include <algorithm>

#include <map>

#include <fstream>

using namespace std;

// Comparator function to sort trigrams highest frequency
bool cmp(pair < tuple < string, string, string > , int > & a, pair < tuple < string, string, string > , int > & b) {

  if (a.second != b.second) {
    return a.second > b.second;

  } else {
    return a.first < b.first;

  }

}
//Output format which prints trigrams and frequency
void printFunction(pair <
  const tuple < string, string, string > , int > it) {
  cout << it.second << " - [" << get < 0 > (it.first) << " " << get < 1 > (it.first) << " " << get < 2 > (it.first) << "]\n";
}

//extracts the trigram from the file
void readTrigrams(string line, map < tuple < string, string, string > , int > & myMap) {
  vector < string > words;
  string word;
  ifstream file(line);

  // Also handle the case where there is only one word or the array is empty and handle those case
  // added start1 and start2 to words vector

  words.push_back("<START_1>");

  words.push_back("<START_2>");

  while (file >> word) {
    words.push_back(word);
  }
  words.push_back("<END_1>");

  words.push_back("<END_2>");

  // added end1 and end2 to words vector

  for (size_t i = 0; i + 2 < words.size(); ++i) {
    tuple < string, string, string > trigram(words[i], words[i + 1], words[i + 2]);
    myMap[trigram] = myMap[trigram] + 1; //keeps track of frequency and aligns with the trigram
  }
}

// handles the commands and gets the file
int trigram(map < tuple < string, string, string > , int > & myMap, char command, char * argv[]) {

  vector < pair < tuple < string, string, string > , int >> trigramWords;

  string x;
  string y;

  switch (command) {
  case 'a': //prints the trigrams in ascending order 

    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
      pair < tuple < string, string, string > , int > Cpair;
      Cpair.first = it -> first;
      Cpair.second = it -> second;

      printFunction(Cpair);
    }
    break;

  case 'd': //prints the trigrams in descending order 
    for (auto it = myMap.rbegin(); it != myMap.rend(); ++it) {
      pair < tuple < string, string, string > , int > Cpair;
      Cpair.first = it -> first;
      Cpair.second = it -> second;
      printFunction(Cpair);
    }
    break;

  case 'c': //prints all the trigram frequency from highest to lowest
    for (auto & it: myMap) {
      trigramWords.push_back(it);
    }

    // Sort using comparator function
    sort(trigramWords.begin(), trigramWords.end(), cmp);

    // Print the sorted value
    for (auto & it: trigramWords) {
      pair < tuple < string, string, string > , int > Cpair;
      Cpair.first = it.first;
      Cpair.second = it.second;
      printFunction(Cpair);
    }
    break;

  case 'f': // prints the most repeated third word in trigram based on userchoice
    x = argv[3]; //converts to string
    y = argv[4];

    for (auto & it: myMap) {

      if (get < 0 > (it.first) == x && get < 1 > (it.first) == y) {
        trigramWords.push_back(it);
      }

    }
    sort(trigramWords.begin(), trigramWords.end(), cmp);

    if (trigramWords.size() == 0) { //if no trigram exist
      cout << "No trigrams of the form [" << x << " "<< y << " ?]" << endl; //ask

    } else {
      printFunction(trigramWords.at(0));
    }

    break;

  default:
    cerr << "Invalid command: valid options are a, d, c, and f" << endl;
    return 1;
  }
  return 0;
}