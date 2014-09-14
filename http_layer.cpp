#include "http_layer.h"

CHTTPRequest::CHTTPRequest ( const string & header )
 {
 	string lowerCaseHeader, tmp;
 	stringstream ss ( header );
 	m_Header.assign ( header );
 	lowerCaseHeader.assign ( header );
 	transform ( lowerCaseHeader.begin(), lowerCaseHeader.end(), lowerCaseHeader.begin(), ::tolower );
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
 	m_Header.assign ( header );
 	m_Content.assign ( content );
 	stringstream ss (header);
 	ss >> m_HTTPVersion;
 	ss >> m_StatusCode;
 	ss >> m_ReasonPhrase;
 }

string CHTTPResponse::toString ( )
 {
 	string str = m_Header + m_Content;
 	return str;
 }
