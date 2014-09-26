/* parsing.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#include "parsing.h"
#include "constants.h"

bool checkBadWords ( const set<string> & bad_words, const string & str )
 {
 	for ( set<string>::const_iterator it = bad_words.begin ( ); it != bad_words.end ( ); ++it )
 	{
 		if ( str.find ( *it ) != string::npos )
 			return false;
 	}
 	return true;
 }

void getBadWords ( set<string> & bad_words )
 {
 	ifstream input;
 	char buffer [BUFFERSIZE];
 	string line;
 	input.open ( "badwords", ifstream::in | ifstream::binary );
 	while ( input.good (  ) )
 	{
 		input.getline ( buffer, BUFFERSIZE );
		line.assign ( buffer );
		bad_words.insert ( line );
	}
 	input.close ( );
 }

void printBadWords ( const set<string> & bad_words )
 {
	for ( set<string>::const_iterator it = bad_words.begin ( ); it != bad_words.end ( ); ++it )
		cout << *it << endl;
 }
