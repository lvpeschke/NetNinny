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
#include "http_layer.h"

using namespace std;

#define BUFFERSIZE 1000
#define SOCK_ERR "Cannot create socket" //Error that occurs when socket cannot be created.
#define BIND_ERR "Cannot bind port to socket" //Error that occurs when socket cannot be bound to port.
#define LIST_ERR "Cannot set socket to listening state" //Error that occurs when listening on socket fails.
#define RECV_ERR "Cannot receive data" //Error that occurs when socket cannot receive data.
#define ACCE_ERR "Cannot accept connection" //Error that occurs when accept function fails.
#define ADDR_ERR "Error with initial socket setting" //Error that occurs when getaddrinfo function fails.
#define CONNECTION_CLOSED "Connection closed by the other side" //Message used when proxy receives data of zero length, signing end of connection.

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

struct TArg
 {
    int m_Socket;
 };
void *serverConnection ( TArg * arg ); //Function called for every received connection from client

void serverMain ( int socket ); //Main server loop that is accepting new connections and creating new threads for them

int openServerSocket ( const char * port ); //Function that opens a socket and prepares it for connections

#endif
