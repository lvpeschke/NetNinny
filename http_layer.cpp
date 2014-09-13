#include "http_layer.h"

CHTTPRequest::CHTTPRequest ( string & header )
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
 	if ( m_Method == "POST" )
 	{
 		tmp = lowerCaseHeader.substr ( lowerCaseHeader.find ( "content-length:" ) + 16);
 		m_ContentLength = atoi ( tmp.substr ( 0, tmp.find ( "\r\n" ) ).c_str() );
 	}
 	else
 		m_ContentLength = 0;
 	printRequest (  );
 }

void CHTTPRequest::printRequest ()
 {
 	cout << "Method:      " << m_Method        << endl;
 	cout << "URL:         " << m_URL           << endl;
 	cout << "Protocol:    " << m_HTTPVersion   << endl;
 	cout << "Host:        " << m_Host          << endl;
 	cout << "Content len: " << m_ContentLength << endl;
 }
