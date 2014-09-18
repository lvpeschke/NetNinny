#ifndef HTTPLAYER_937236837
#define HTTPLAYER_937236837

#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;

//Abstract class containing things common to all HTTP requests
class CHTTPRequest
 {
 public:
 	               CHTTPRequest ( const string & header );
	virtual       ~CHTTPRequest ( ) { }
 	virtual string toString (  ) = 0;
 protected:
 	string m_Method;
 	string m_URL;
 	string m_HTTPVersion;
 	string m_Host;
 	string m_Header;
 };

//Class representing HTTP GET request
class CHTTPGet : public CHTTPRequest
 {
 public:
 	       CHTTPGet ( const string & header );
 	      ~CHTTPGet ( ) { }
 	string toString ( );
 };

class CHTTPResponse
 {
 public:
 	       CHTTPResponse ( const string & header, const string & content );
 	string toString (  );
 private:
 	string m_Header;
 	string m_Content;
 	string m_HTTPVersion;
 	string m_StatusCode;
 	string m_ReasonPhrase;
 };

int getContentLength ( const string & header );

#endif
