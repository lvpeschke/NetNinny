/* server.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#include "server.h"
#include "client.h"

void *serverConnection ( TArg * arg )
{
  string header;
  string method;
  CHTTPRequest * request = NULL;

  cout << "Connection accepted" << endl;
  CTCPBuffer buffer ( arg->m_Socket );
  
  try {
    buffer.getHTTPHeader ( header );
  }
  catch ( CSocketException e ) {
    cout << e << endl; return NULL;
  }
  method = header.substr( 0, header.find_first_of(' ') );
  if ( !method.compare ( "GET" ) ) {
    request = new CHTTPGet ( header );
    cout << request->toString();
  }
  else
  {
    delete arg;
    cout << "PREPARE TO BE ASSIMILATED. RESISTANCE IS FUTILE." << endl;
    cout << header;
    return NULL;
  }
  if ( !checkBadWords ( arg->m_BadWords, request->getURL( ) ) )
  {
    send ( arg->m_Socket, BAD_CONTENT_HEADER, sizeof ( BAD_CONTENT_HEADER ), 0 );
    delete request;
    delete arg;
    return NULL;
  }
  CHTTPResponse & response = clientMain ( *request, arg->m_BadWords );
  send ( arg->m_Socket, response.toString ( ).c_str ( ), response.toString ( ).length(), 0);
  
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
    arg->m_BadWords = bad_words;
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
