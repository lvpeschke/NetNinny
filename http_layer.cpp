/* http_layer.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#include "http_layer.h"

CHTTPRequest::CHTTPRequest ( const string & header )
 {
 	string lowerCaseHeader, tmp;
 	stringstream ss ( header );
 	m_Header.assign ( header );
 	lowerCaseHeader.assign ( header );
 	transform ( lowerCaseHeader.begin(), lowerCaseHeader.end(),
                lowerCaseHeader.begin(), ::tolower );
 	string test;
 	ss >> m_Method;
 	ss >> m_URL;
 	ss >> m_HTTPVersion;
	tmp = lowerCaseHeader.substr ( lowerCaseHeader.find ( "host:" ) + 6);
 	m_Host = tmp.substr ( 0, tmp.find ( "\r\n" ) );
 }

CHTTPGet::CHTTPGet ( const string & header ) : CHTTPRequest ( header )
 {

 }

string CHTTPGet::toString ( )
 {
 	string str;
 	str = m_Method + ' ' + m_URL + ' ' + m_HTTPVersion + "\r\nHost: " + m_Host + "\r\n\r\n";
 	return str; 
 }

CHTTPResponse::CHTTPResponse ( const string & header, const string & content )
 {
 	string tmp;
 	unsigned int pos;
 	m_Header.assign ( header );
 	m_Content.assign ( content );
 	tmp.assign ( header );
 	transform ( tmp.begin(), tmp.end(), tmp.begin(), ::tolower );
 	stringstream ss (header);
 	ss >> m_HTTPVersion;
 	ss >> m_StatusCode;
 	ss >> m_ReasonPhrase;
 	pos = tmp.find ( "content-type:" );
 	if ( pos == string::npos )
 		m_ContentType.clear ( );
 	else
 	{
 		tmp = tmp.substr (  pos + 14 );
 		m_ContentType = tmp.substr ( 0, tmp.find ( "\r\n" ) );	
 	}
 }

string CHTTPResponse::toString ( )
 {
 	string str = m_Header + m_Content;
 	return str;
 }

int getContentLength ( const string & header )
 {
 	string tmp;
 	size_t pos;
 	tmp.assign ( header );
 	transform ( tmp.begin(), tmp.end(), tmp.begin(), ::tolower );
 	pos = tmp.find ( "content-length:" );
 	if ( pos == string::npos )
 		return 0;
	tmp = tmp.substr ( pos + 16 );
	tmp = tmp.substr ( 0, tmp.find ( "\r\n" ) );
	return atoi ( tmp.c_str( ) );
 }

void redirect (  )
 {
 	
 }
