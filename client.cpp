/* client.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#include "client.h"

using namespace std;

/* Getting the socket address */
void* get_in_addr(struct sockaddr* sa)
{
  if (sa->sa_family == AF_INET)
    return &(((struct sockaddr_in*)sa)->sin_addr);
  else
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int openClientSocket(const char *hostname)
{
  struct addrinfo hints;
  memset(&hints, 0, sizeof hints);
  struct addrinfo* servinfo;
  
  int res;
  int sockfd;
  
  // Checking for the argument
  if (hostname == 0)
    throw CSocketException(HOST_ERR);
  
  // Getting information about the server
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  res = getaddrinfo(hostname, "http", &hints, &servinfo);
  if (res != 0)
    throw CSocketException(ADDR_ERR);
  fprintf(stdout, "correct address\n"); ///
  
  // Creating the socket
  sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (sockfd == -1) {
    freeaddrinfo(servinfo);
    throw CSocketException(SOCK_ERR);
  }
  fprintf(stdout, "socket\n"); ///
  
  // Connecting to the server
  res = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
  if (res != 0) {
    freeaddrinfo(servinfo);
    close(sockfd);
    throw CSocketException(CONN_ERR);
  }
  fprintf(stdout, "connected\n"); ///
  
  freeaddrinfo(servinfo);
  
  return sockfd;
}

ssize_t clientSend(int sockfd, size_t request_length, const char* request)
{
  ssize_t length;
  
  length = send(sockfd, request, request_length, 0);
  if (length == -1) {
    close(sockfd);
    throw CSocketException(SEND_ERR);
  }
  fprintf(stdout, "sent\n"); ///
  
  return length;
}

/*ssize_t clientRecv(int sockfd, size_t response_length, char** response) /// useless?
{
  ssize_t length;
  
  length = recv(sockfd, * response, response_length, 0);
  if (length == -1) {
    close(sockfd);
    throw CSocketException(RECV_ERR);
  }
  fprintf(stdout, "received\n"); ///
  
  return length;
}*/

CHTTPResponse &clientMain(CHTTPRequest &request, const set<string> &badWords)
{
  int sockfd;
  const char* host;
  const char* request_str;
  
  ssize_t length;
  size_t request_length;
  
  // Getting the information needed for the request
  host = request.getHost().c_str();
  //host = "www.google.com";
  
  
  if (host == 0) {
   throw CSocketException(HOST_ERR);
  }
  request_str = request.toString().c_str();
  request_length = request.toString().length();
  
  /*** CHANGE THIS, HARDCODED REQUEST ***
  sprintf(requesttemp,
          "GET %s%s HTTP/1.1\r\n"
          "Host: %s\r\n"
          "\r\n\r\n", host, "/", host);
  request_length = strlen(requesttemp);
  *** CHANGE THIS, HARDCODED REQUEST ***/
  
  // Setting up the connection
  sockfd = openClientSocket(host);
  
  // Sending the request
  length = 0;

  //What does this mean? What does it do? 
  while (length != (signed)request_length) {
    length += clientSend(sockfd, request_length, request_str);
    cout << "Not sent everything yet, trying again\n" << endl; ///
  }
  
  // Getting the incoming response
  CTCPBuffer buffer(sockfd);
  string header, content;
  buffer.getHTTPHeader(header);
  int content_length = getContentLength(header);
  buffer.getHTTPContent(content, content_length);
  
  // Cleaning up
  close(sockfd);
  
  //TODO get content type here, so that we only create 1 object
  
  // Reconstructing the HTTP
  CHTTPResponse* response = new CHTTPResponse(header, content);
  
  // What is the type of content ?
  const string text = "text";

  if (response->getContentType().find(text) != string::npos) {
    
    if (!checkBadWords(badWords, content)) {
      delete response;
      
      CHTTPResponse* alt_response = new CHTTPResponse(BAD_CONTENT_HEADER, BAD_CONTENT_CONTENT);

      cout << "\n!!! REACHED THE ALTERNATIVE END !!!\n" << endl;      
      return *alt_response;
    }
  }
  
  cout << "\n!!! REACHED THE END !!!\n" << endl;
//  return *response;
  return *response;
}
