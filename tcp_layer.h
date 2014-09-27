/* tcp_layer.h
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

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

/*
 * Buffer that extracts characters from a TCP stream
 * and stores the number of extracted characters in 'm_MaximalPos'.
 * Extracted characters are accesible one by one with
 * the 'getNextChar' method.
 * If the end of buffer is reached, a new batch of characters is extracted.
 */
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
