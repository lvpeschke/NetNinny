/* main.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

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
#include "tcp_layer.h"
#include "client.h"
#include "server.h"

using namespace std;

/*
 * NetNinny Proxy
 *
 * Reads a port number from the list of program arguments,
 * gets a server socket from 'openServerSocket' function
 * and checks for socket errors.
 * Calls the function 'serverMain' that contains the main server loop
 * and handles requests and responses with threads.
 */
int main ( int argc, char * argv [] )
{
    int   socket;
    char* port;
    
    if (argc != 2) {
        cout << "Incorrect number of arguments. "
        "Arguments should be in following format:\n"
        "./net_ninny port_number" << endl;
        exit(EXIT_FAILURE);
    }
    // REQUIREMENT 7
    port = argv[1];
    
    cout << "SERVER RUNNING ON PORT: " << port << endl;
    
    try {
        // Set up the socket
        socket = openServerSocket(port);
    }
    catch (CSocketException e) {
        cout << e << endl;
        exit(EXIT_FAILURE);
    }
    
    // Start the proxy
    serverMain(socket);
    
    close(socket);
    
    return 0;
}
