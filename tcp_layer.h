#ifndef TCPLAYER_93983781
#define TCPLAYER_93983781

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <set>

#include "constants.h"
#include "exceptions.h"
#include "http_layer.h"
#include "parsing.h"

using namespace std;

//Buffer, that extracts characters from TCP stream to buffer and stores number of extracted characters in m_MaximalPos variable.
//Extracted characters are accesible one by one with getNextChar method. If the end of buffer is reached, new batch of characters is extracted.
class CTCPBuffer
 {
 public:
 		 CTCPBuffer     ( int socket );
 	char getNextChar    ( );
 	void getHTTPHeader  ( string & header );
 	void getHTTPContent ( string & content, int content_length );
 private:
 	char m_Buffer [BUFFERSIZE];
 	int  m_CurrentPos;
 	int  m_MaximalPos;
 	int  m_Socket;
 };

#endif
