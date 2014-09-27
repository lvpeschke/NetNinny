/* exceptions.h
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#ifndef EXCEPTIONS_2345823513
#define EXCEPTIONS_2345823513

#include <string>
#include <iostream>

using namespace std;

/*
 * A CSocketException contains information
 * about the problem that occured.
 */
class CSocketException
{
public:
    CSocketException ( string what );
    friend ostream& operator<< ( ostream& os, CSocketException src );
private:
    string m_What;
};

#endif
