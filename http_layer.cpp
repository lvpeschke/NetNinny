#include "http_layer.h"

CHTTPRequest::CHTTPRequest ( string & header )
 {
 	string lowerCaseHeader;
 	m_Header.assign ( header );
 	lowerCaseHeader.assign ( header );
 	transform ( lowerCaseHeader.begin(), lowerCaseHeader.end(), lowerCaseHeader.begin(), ::tolower );
 	cout << lowerCaseHeader;
 }