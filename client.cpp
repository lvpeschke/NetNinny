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
  
  // Creating the socket
  sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (sockfd == -1) {
    freeaddrinfo(servinfo);
    throw CSocketException(SOCK_ERR);
  }
  
  // Connecting to the server
  res = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
  if (res != 0) {
    freeaddrinfo(servinfo);
    close(sockfd);
    throw CSocketException(CONN_ERR);
  }
  
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
  
  ssize_t length = 0;
  size_t request_length;
  
  // Getting the information needed for the request
  host = request.getHost().c_str();
  
  if (host == 0) {
   throw CSocketException(HOST_ERR);
  }
  request_str = request.toString().c_str();
  request_length = request.toString().length();
  
  // Setting up the connection
  sockfd = openClientSocket(host);
  
  cout << request.getHeader();
  
  // Sending the request
  length = clientSend(sockfd, request_length, request_str);
  if (length == -1) {
    throw CSocketException(SEND_ERR);
  }
  
  // Getting the incoming response
  CTCPBuffer buffer(sockfd);
  string header, content;
  buffer.getHTTPHeader(header);
  int content_length = getContentLength(header);
  buffer.getHTTPContent(content, content_length);
  
  // Cleaning up
  close(sockfd);
  
  // cout << "before checking the content" << endl;
  
  // Reconstructing the HTTP
  CHTTPResponse* response = new CHTTPResponse(header, content);
  
  cout << response->getHeader();
  
  // What is the type of content?
  const string text = "text";
  //cout << "TEST" << endl;
  if (response->getContentType().find(text) != string::npos) {
    // cout << "START OF RESPONSE" << endl;
    cout << response->toString();
    // cout << "END OF RESPONSE" << endl;
    // Is the content ok?
    if (!checkBadWords(badWords, content)) {
      
      // cout << "after checking the content" << endl;
      delete response;
      
      string empty_content;
      empty_content.clear();
      string str;
      str.assign ( BADWORD_REDIRECTION_HEADER );
      CHTTPResponse* alt_response = new CHTTPResponse(str, empty_content);
      return *alt_response;
    }
  }
  
  return *response;
}
