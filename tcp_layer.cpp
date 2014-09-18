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
            throw CSocketException ( CONNECTION_CLOSED );
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

void CTCPBuffer::getHTTPContent ( string & content, int content_length )
 {
    content.clear( );
    for ( int i = 0; i<content_length; i++ )
        content.push_back ( getNextChar ( ) ); 
 }

void *serverConnection ( TArg * arg )
 {
    string header;
    string method;
    CHTTPRequest * request = NULL;
    cout << "Connection accepted" << endl;
    CTCPBuffer buffer ( arg->m_Socket );
    try { buffer.getHTTPHeader ( header ); }
    catch ( CSocketException e ) { cout << e << endl; return NULL; }
    method = header.substr( 0, header.find_first_of(' ') );
    if ( !method.compare ( "GET" ) )
    {
        request = new CHTTPGet ( header );
        cout << request->toString();
    }
    if ( !checkBadWords ( *(arg->m_BadWords), request->getURL( ) ) )
        redirect ( );
    delete request;
    delete arg;
    return NULL;
 }

void serverMain ( int socket )
 {
    TArg * arg;
    set<string> bad_words;
    getBadWords ( bad_words );
    printBadWords ( bad_words );
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
        arg->m_BadWords = &bad_words;
        if ( arg->m_Socket == -1 )
        {
            throw CSocketException ( ACCE_ERR );
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
        throw CSocketException ( ADDR_ERR );
    if ( ( sockfd = socket ( servinfo -> ai_family, SOCK_STREAM, 0 ) ) == -1)
    {
        freeaddrinfo ( servinfo );
        throw CSocketException ( SOCK_ERR );
    }
    if ( bind ( sockfd, servinfo -> ai_addr, servinfo -> ai_addrlen ) == -1 )
    {
        close ( sockfd );
        freeaddrinfo ( servinfo );
        throw CSocketException ( BIND_ERR );
    }
    if ( listen ( sockfd, 10 ) == -1 )
    {
      close ( sockfd );
      throw CSocketException ( LIST_ERR );
    }
    freeaddrinfo ( servinfo );	
    return sockfd; 
 }
