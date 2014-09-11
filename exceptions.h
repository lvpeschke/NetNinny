#ifndef EXCEPTIONS_2345823513
#define EXCEPTIONS_2345823513

#include <string>
#include <iostream>

using namespace std;

class CSocketException
 {
 public:
	CSocketException ( string what );
	friend ostream& operator<< ( ostream& os, CSocketException src );
 private:
 	string m_What;
 };

#endif