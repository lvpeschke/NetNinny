#ifndef SERVER_H
#define SERVER_H

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
#include "tcp_layer.h"
#include "parsing.h"

using namespace std;

struct TArg
{
  int m_Socket;
  set<string> * m_BadWords;
};
void *serverConnection ( TArg * arg ); //Function called for every received connection from client

void serverMain ( int socket ); //Main server loop that is accepting new connections and creating new threads for them

int openServerSocket ( const char * port ); //Function that opens a socket and prepares it for connections

#endif
