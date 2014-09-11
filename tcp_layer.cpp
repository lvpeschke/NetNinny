#include "tcp_layer.h"

void *serverConnection ( TArg * arg )
 {
    char buffer [1000];
    int len;
    cout << "Connection accepted" << endl;
    while (1)
    {    
        len = recv ( arg->m_Socket, buffer, 1000, 0 );
        if ( ! len ) break;
        cout << buffer;
    }
    delete arg;
    return NULL;
 }

void serverMain ( int socket )
 {
    TArg * arg;
 	pthread_t t;
    pthread_attr_t attr;
    pthread_attr_init ( &attr );
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
    while ( 1 )
    {
        struct sockaddr connection;
        socklen_t connection_size = sizeof ( connection );
        arg = new TArg;
        arg->m_Socket = accept ( socket, &connection, &connection_size );
        pthread_create ( &t, &attr, (void*(*)(void*)) serverConnection, (void*) arg );
    }
    pthread_attr_destroy ( &attr );
    close ( socket );
 }

int openServerSocket ( const char * port )
 {
 	struct addrinfo* servinfo;
 	struct addrinfo  hints;
 	int    sockfd;
// 	int    yes = 1;
 	memset( &hints, 0, sizeof hints );
 	hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

//    if ( getaddrinfo(NULL, port, &hints, &servinfo) != 0 ) 
//    {
//        throw CSocketException ( "Failed to get info about the provided address." );
//    }

    if ( getaddrinfo ( "127.0.0.1", port, NULL, &servinfo ) )
        throw CSocketException ( "Failed to get address info" );
    if ( ( sockfd = socket ( servinfo -> ai_family, SOCK_STREAM, 0 ) ) == -1)
    {
        freeaddrinfo ( servinfo );
        throw CSocketException ( "Failed to created socket" );
    }
    if ( bind ( sockfd, servinfo -> ai_addr, servinfo -> ai_addrlen ) == -1 )
    {
        close ( sockfd );
        freeaddrinfo ( servinfo );
        throw CSocketException ( "Failed to bind socket" );
    }
    if ( listen ( sockfd, 10 ) == -1 )
    {
      close ( sockfd );
      throw CSocketException ( "Failed to listen on socket" );
    }
    freeaddrinfo ( servinfo );	
    return sockfd; 
 }
