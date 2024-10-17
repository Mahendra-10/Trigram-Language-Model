#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

#include <string>
#include <tuple>
#include <map>

bool cmp(std::pair<std::tuple<std::string, std::string, std::string>, int>& a, std::pair<std::tuple<std::string, std::string, std::string>, int>& b);
void printFunction(std::pair<const std::tuple<std::string, std::string, std::string>, int> it);
int trigram(std::map < std::tuple < std::string, std::string, std::string>, int > &myMap, char command, char*argv[]);
void readTrigrams(std ::string line, std::map < std::tuple < std::string, std::string, std::string > , int > &myMap);


#endif
