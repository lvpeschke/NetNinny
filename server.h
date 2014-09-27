/* server.h
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

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

/*
 * Structure containg the arguments needed
 * by the threads to handle the requests
 * from the browser.
 */
struct TArg
{
  int m_Socket;
  set<string> m_BadWords;
};

/*
 * Connecting the proxy-server to the client
 * after an accepted connection on the socket
 * arg: the argument structure needed to process the connection
 */
void* serverConnection ( TArg * arg );

/*
 * Main server loop accepting new connections and creating new threads for them
 * socket: the socket file descriptor on which connections are accepted
 */
void serverMain ( int socket );

/*
 * Opening a socket and preparing it for connections
 * port: the port number on which to open the socket
 * Returns a file descriptor for the socket upon success.
 */
int openServerSocket ( const char * port );

#endif
