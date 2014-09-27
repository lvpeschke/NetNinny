/* parsing.h
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#ifndef PARSING_1216846
#define PARSING_1216846

#include <set>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/*
 * Checking a string for presence of bad words
 * bad_words: a set of bad words
 * str: the string to be filtered
 * Returns true if no bad words are present, false otherwise.
 */
bool checkBadWords ( const set<string> & bad_words, const string & str );

/*
 * Loading all the bad words from a file in a set
 * bad_words: the resulting set
 */
void getBadWords ( set<string> & bad_words );

/*
 * Printing all the bad words stored in set to stdout
 * bad_words: the set of bad words
 */
void printBadWords ( const set<string> & bad_words );

#endif
