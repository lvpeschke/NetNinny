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
 * bad_words: a set of strings to be filtered
 * str: the string to be checked
 * Returns true if no bad words are present in str, false otherwise.
 */
bool checkBadWords ( const set<string> & bad_words, const string & str );

/*
 * Reading all bad words from a file and storing them in a set of strings
 * bad_words: the set of srings were the words should be stored
 */
void getBadWords ( set<string> & bad_words );

/* 
 * Printing all bad words stored in set to stdout
 * bad_words: the set of strings containing the bad words
 */
void printBadWords ( const set<string> & bad_words );

#endif
 
