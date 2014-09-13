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

#include "exceptions.h"

using namespace std;

#define BUFFERSIZE 1000

//Buffer, that extracts characters from TCP stream to buffer and stores number of extracted characters in m_MaximalPos variable.
//Extracted characters are accesible one by one with getNextChar method. If the end of buffer is reached, new batch of characters is extracted.
class CTCPBuffer
 {
 public:
 		 CTCPBuffer    ( int socket );
 	char getNextChar   ( );
 	void getHTTPHeader ( string & header ); 
 private:
 	char m_Buffer [BUFFERSIZE];
 	int  m_CurrentPos;
 	int  m_MaximalPos;
 	int  m_Socket;
 };

struct TArg
 {
    int m_Socket;
 };

void *serverConnection ( TArg * arg );

void serverMain ( int socket );

int openServerSocket ( const char * port );

#endif
