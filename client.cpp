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
void* get_in_addr ( struct sockaddr* sa )
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    else
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int openClientSocket ( const char *hostname )
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    struct addrinfo* servinfo;
    
    int sockfd;
    
    // Checking for the argument
    if (hostname == 0)
        throw CSocketException(HOST_ERR);
    
    // Getting information about the server
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(hostname, "http", &hints, &servinfo) != 0)
        throw CSocketException(ADDR_ERR);
    
    // Creating the socket
    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (sockfd == -1) {
        freeaddrinfo(servinfo);
        throw CSocketException(SOCK_ERR);
    }
    
    // Connecting to the server
    if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) != 0) {
        freeaddrinfo(servinfo);
        close(sockfd);
        throw CSocketException(CONN_ERR);
    }
    
    freeaddrinfo(servinfo);
    
    return sockfd;
}

ssize_t clientSend ( int sockfd, size_t request_length, const char* request )
{
    ssize_t length;
    length = send(sockfd, request, request_length, 0);
    if (length == -1) {
        close(sockfd);
        throw CSocketException(SEND_ERR);
    }
    
    return length;
}

CHTTPResponse &clientMain ( CHTTPRequest &request, const set<string> &badWords )
{
    int sockfd;
    const char* host;
    
    ssize_t length = 0;
    
    // Printing the request header to stdout
    cout << request.getHeader();
    
    // Getting the information needed for the request
    host = request.getHost().c_str();
    if (host == 0) {
        throw CSocketException(HOST_ERR);
    }
    
    // Setting up the connection
    sockfd = openClientSocket(host);
    
    // Sending the request
    length = clientSend(sockfd, request.toString().length(), request.toString().c_str());
    
    // Getting the incoming response
    CTCPBuffer buffer(sockfd);
    string header, content;
    buffer.getHTTPHeader(header);
    buffer.getHTTPContent(content, getContentLength(header));
    
    // Cleaning up
    close(sockfd);
    
    // Reconstructing the HTTP
    CHTTPResponse* response = new CHTTPResponse(header, content);
    
    // Checking the content if it is text
    // REQUIREMENT 4 & 6
    if (response->getContentType().find("text") != string::npos) {
        if (!checkBadWords(badWords, content)) {
            delete response;
            string str, empty_content;
            empty_content.clear();
            str.assign ( BADWORD_REDIRECTION_HEADER );
            CHTTPResponse* alt_response = new CHTTPResponse(str, empty_content);
            
            return *alt_response;
        }
    }
    
    // Printing the response header
    cout << response->getHeader();
    
    return *response;
}
