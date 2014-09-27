/* http_layer.h
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#ifndef HTTPLAYER_937236837
#define HTTPLAYER_937236837

#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;

/*
 * Abstract class containing a pattern for all HTTP requests
 */
class CHTTPRequest
{
public:
            CHTTPRequest     ( const string & header );
    virtual ~CHTTPRequest    ( ) { }
    virtual string toString  ( ) = 0;
 			string getURL    ( ) { return m_URL;  }
 			string getHost   ( ) { return m_Host; }
            string getHeader ( ) { return m_Header; }
protected:
    string m_Method;
    string m_URL;
    string m_HTTPVersion;
    string m_Host;
    string m_Header;
};

/*
 * Class representing a HTTP GET request
 */
class CHTTPGet : public CHTTPRequest
{
public:
    CHTTPGet ( const string & header );
    ~CHTTPGet ( ) { }
    string toString ( );
};

/*
 * Class representing a HTTP response
 */
class CHTTPResponse
{
public:
    CHTTPResponse ( const string & header, const string & content );
    string toString (  );
    string getContentType ( ) { return m_ContentType; }
    string getStatusCode  ( ) { return m_StatusCode; }
    string getHeader      ( ) { return m_Header; }
private:
    string m_Header;
    string m_Content;
    string m_HTTPVersion;
    string m_StatusCode;
    string m_ReasonPhrase;
    string m_ContentType;
};

/*
 * Extracts the length of the content from the HTTP header
 * header: a HTTP header
 * Returns the length of the HTTP content.
 */
int getContentLength ( const string & header );

#endif
