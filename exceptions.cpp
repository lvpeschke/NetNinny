#include "exceptions.h"

CSocketException::CSocketException ( string what )
 {
 	m_What.assign(what);
 }

ostream& operator<< ( ostream& os, CSocketException src )
 {
 	os << "Berkeley socket error: " << src.m_What << endl;
 	return os;
 }