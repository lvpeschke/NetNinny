#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <errno.h> //TODO

#include "http_layer.h"
#include "exceptions.h"
#include "constants.h"

using namespace std;

#define MAXLINE 1000 //TODO

/*
 * Getting a new socket
 * hostname: address of the host, e.g. "google.com"
 * Returns the socket fd.
 */
int openClientSocket(char *hostname);

/*
 * Sending a request to the server via sockfd
 * sockfd: socket file descriptor, must be legal
 * request_length: size of the request
 * request: message to send to the server through the socket
 * Returns the length of the sent message, or -1 upon error.
 */
ssize_t clientSend(int sockfd, size_t request_length, char *request);

/*
 * Receiving a response from the server via sockfd
 * sockfd: socket file descriptor, must be legal
 * content_length: size of the buffer
 * *response[]: buffer where the response will go
 * Returns the length of the sent message, or -1 upon error.
 */
ssize_t clientRecv(int sockfd, size_t content_length, char **response);

//TODO: main function that processes one request
int mainClient(char *host);


/*
 Client: CHTTPResponse &mainClient(CHTTPRequest &request)
 // CHHTPRequest always valid
 // we can then use request.toString().c_str()
 // CHTTP *response = new CHTTPResponse(header, content)
 */
/*
 * Sending an HTTP request and getting an HTTP response
 * request: a valid HTTP request object
 * Returns an HTTP response object.
 */
CHTTPResponse &clientMain(CHTTPRequest &request);

#endif
