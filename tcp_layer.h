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

struct TArg
 {
    int m_Socket;
 };

void *serverConnection ( TArg * arg );

void serverMain ( int socket );

int openServerSocket ( const char * port );

#endif
