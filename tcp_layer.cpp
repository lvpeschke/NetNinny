#include "tcp_layer.h"

CTCPBuffer::CTCPBuffer ( int socket )
 {
    m_Socket = socket;
    m_MaximalPos = 0;
    m_CurrentPos = 0;
 }

char CTCPBuffer::getNextChar ( )
 {
    if ( m_CurrentPos == m_MaximalPos )
    {
        m_MaximalPos = recv ( m_Socket, m_Buffer, BUFFERSIZE, 0 );
        if ( !m_MaximalPos )
            throw CSocketException ( "Connection closed" );
        m_CurrentPos = 0;
    }
    return m_Buffer[m_CurrentPos++];
 }

void CTCPBuffer::getHTTPHeader ( string & header )
 {
    header.clear( );
    state_0:
        header.push_back ( getNextChar ( ) );
        if ( *header.rbegin() == '\r' )
            goto state_1;
        else
            goto state_0;
    state_1:
        header.push_back ( getNextChar ( ) );
        if ( *header.rbegin() == '\n' )
            goto state_2;
        else if ( *header.rbegin() == '\r' )
            goto state_1;
        else
            goto state_0;    
    state_2:
        header.push_back ( getNextChar ( ) );
        if ( *header.rbegin() == '\r' )
            goto state_3;
        else
            goto state_0;
    state_3:
        header.push_back ( getNextChar ( ) );
        if ( *header.rbegin() == '\n' )
            return;
        else if ( *header.rbegin() == '\r' )
            goto state_1;
        else
            goto state_0;
 }

void *serverConnection ( TArg * arg )
 {
    string header;
    cout << "Connection accepted" << endl;
    CTCPBuffer buffer ( arg->m_Socket );
    try { buffer.getHTTPHeader ( header ); }
    catch ( CSocketException e ) { cout << e << endl; return NULL; }
    CHTTPRequest request ( header );
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
        if ( arg->m_Socket == -1 )
        {
            throw CSocketException ( "Failed to accept connection." );
        }
        pthread_create ( &t, &attr, (void*(*)(void*)) serverConnection, (void*) arg );
    }
    pthread_attr_destroy ( &attr );
    close ( socket );
 }

int openServerSocket ( const char * port )
 {
 	struct addrinfo* servinfo;
 	int    sockfd;

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
