/* esceptions.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

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
