#ifndef HTTPLAYER_937236837
#define HTTPLAYER_937236837

#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;

class CHTTPRequest
 {
 public:
 	     CHTTPRequest ( string & header );
 	void setContent   ( string & content ) { m_Content.assign ( content ); }
 	void printRequest ( );
 protected:
 	string m_Method;
 	string m_URL;
 	string m_HTTPVersion;
 	string m_Host;
 	string m_Header;
 	string m_Content;
 	int    m_ContentLength;
 };

#endif
