#ifndef PARSING_1216846
#define PARSING_1216846

#include <set>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//Checks a string for presence of bad words. Returns true if no bad words are present, false otherwise
bool checkBadWords ( const string & str );

//Reads all bad words of proxy server from file and stores them in a set
void getBadWords ( set<string> & bad_words );

//Prints all bad words stored in set that is passed to it
void printBadWords ( const set<string> & bad_words );

#endif

