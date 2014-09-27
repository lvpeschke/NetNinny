/* server.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#include "server.h"
#include "client.h"

void* serverConnection ( TArg * arg )
{
    string header;
    string method;
    CHTTPRequest * request = NULL;
    
    cout << endl << "Connection accepted" << endl << endl;
    
    // Getting the request
    CTCPBuffer buffer(arg->m_Socket);
    
    // Getting the header
    try {
        buffer.getHTTPHeader(header);
    }
    catch(CSocketException e) {
        cout << e << endl;
        return NULL;
    }
    method = header.substr(0, header.find_first_of(' '));
    if (!method.compare("GET")) {
        request = new CHTTPGet(header);
    }
    else {
        delete arg;
        send (arg->m_Socket, METHOD_NOT_SUPPORTED, sizeof(METHOD_NOT_SUPPORTED), 0);
        return NULL;
    }
    
    // Checking the url for bad words
    if (!checkBadWords (arg->m_BadWords, request->getURL())) {
        cout << BAD_CONTENT_HEADER;
        // Redirection in case of bad url
        // REQUIREMENT 3
        send (arg->m_Socket, BAD_URL_HEADER, sizeof (BAD_URL_HEADER), 0);
        delete request;
        delete arg;
        return NULL;
    }
    
    // Client part of the proxy
    try {
        // Forwarding the request
        CHTTPResponse & response = clientMain (*request, arg->m_BadWords);
        
        // In case of bad words in the response, redirection
        // REQUIREMENT 4
        if (!response.getStatusCode().compare("666")) {
            send ( arg->m_Socket, BAD_CONTENT_HEADER, sizeof (BAD_CONTENT_HEADER ), 0);
        }
        else {
            // Sending the response to the browser
            if (send (arg->m_Socket, response.toString().c_str(),
                      response.toString().length(), 0)
                == -1 )
                cout << "RESPONSE NOT SENT" << endl;
        }
        delete &response;
    }
    catch (CSocketException e) {
        cout << e << endl;
    }
    
    delete request;
    delete arg;
    return NULL;
}

void serverMain ( int socket )
{
    TArg* arg;
    set<string> bad_words;
    getBadWords(bad_words);
    pthread_t t;
    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    // Server side of the proxy looping for incoming requests
    while(1) {
        struct sockaddr connection;
        socklen_t connection_size = sizeof ( connection );
        arg = new TArg;
        arg->m_Socket = accept ( socket, &connection, &connection_size );
        arg->m_BadWords = bad_words;
        
        if (arg->m_Socket == -1) {
            throw CSocketException(ACCE_ERR);
        }
        
        // Creating a detached thread to handle each request
        pthread_create(&t, &attr, (void*(*)(void*)) serverConnection, (void*) arg);
    }
    pthread_attr_destroy (&attr);
    close (socket);
}

int openServerSocket ( const char * port )
{
    struct addrinfo* servinfo;
    int    sockfd;
    
    // Getting the socket address
    if (getaddrinfo("127.0.0.1", port, NULL, &servinfo))
        throw CSocketException(ADDR_ERR);
    
    // Opening the socket
    if ((sockfd = socket(servinfo -> ai_family, SOCK_STREAM, 0)) == -1) {
        freeaddrinfo(servinfo);
        throw CSocketException(SOCK_ERR);
    }
    
    // Binding the socket
    if (bind(sockfd, servinfo -> ai_addr, servinfo -> ai_addrlen) == -1) {
        close(sockfd);
        freeaddrinfo(servinfo);
        throw CSocketException(BIND_ERR);
    }
    
    // Listening to incoming messages
    if (listen(sockfd, 10) == -1) {
        close(sockfd);
        throw CSocketException(LIST_ERR);
    }
    
    // Cleaning up
    freeaddrinfo(servinfo);
    
    return sockfd;
}
