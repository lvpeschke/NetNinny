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

using namespace std;

#include "exceptions.h"
#include "tcp_layer.h"

//Reads port number from list of program arguments, gets server socket from openServerSocket function and checks for socket errors.
//Calls function serverMain that contains the main server loop.
int main ( int argc, char * argv [] )
 {
 	int   socket;
 	char* port;
 	if ( argc != 2 )
 	{
 		cout << "Incorrect number of arguments. Arguments should be in following format: ./assignment_2 port_number" << endl;
 		exit ( EXIT_FAILURE );
 	}
 	port = argv[1];
 	
 	cout << "SERVER RUNNING ON PORT: " << port << endl;
 	
 	try { socket = openServerSocket ( port ); }
 	catch ( CSocketException e ) { cout << e << endl; exit ( EXIT_FAILURE ); }
 	serverMain ( socket );
 	close ( socket );
 }
