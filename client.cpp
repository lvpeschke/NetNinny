#include "client.h"

using namespace std;

/* Getting the socket address */
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    else
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int openClientSocket(char *hostname)
{
    int res;
    struct addrinfo hints, *servinfo;
    int sockfd;
    
    // checking for the argument
    if (hostname == NULL) {
        //TODO exception
    }
    
    /* Getting information about the server */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((res =
         getaddrinfo(hostname, "http", &hints, &servinfo)) != 0)
    {
        freeaddrinfo(servinfo);
        throw CSocketException (ADDR_ERR);
    }
    fprintf(stdout, "correct address\n"); ///
    
    /* Create socket */
    // TODO Loop?
    if ((sockfd =
         socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        freeaddrinfo(servinfo);
        throw CSocketException(SOCK_ERR);
    }
    fprintf(stdout, "socket\n"); ///
    
    /* Connecting to the server */
    if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) != 0)
    {
        freeaddrinfo(servinfo);
        close(sockfd);
        throw CSocketException(CONNECTION_FAIL);
    }
    fprintf(stdout, "connected\n"); ///
    
    /* Clean up */
    freeaddrinfo(servinfo);
    
    /* Return the file descriptor */
    return sockfd;
}

ssize_t clientSend(int sockfd, size_t request_length, char *request)
{
    ssize_t length;
    if ((length =
         send(sockfd, request, request_length, 0)) == -1)
    {
        throw CSocketException(SEND_ERR);
    }
    fprintf(stdout, "sent\n"); ///
    
    return length;
}

ssize_t clientRecv(int sockfd, size_t content_length, char **response)
{
    ssize_t length;
    
    /* Get message */
    if ((length =
         recv(sockfd, *response, content_length, 0)) == -1)
    {
        throw CSocketException(RECV_ERR);
    }
    fprintf(stdout, "received\n"); ///
    
    return length;
}

// TODO change everything
int mainClient(int argc, char *argv[])
{
    int sockfd;
    char request[MAXLINE + 1];
    char *response;
    size_t request_length;
    ssize_t length;
    
    if (argc != 2) {
        cerr << "Missing hostname to connect to\n" << endl;
        return -1;
    }
    
    response = (char *)malloc(MAXLINE * (sizeof (char))); //TODO content-length
    
    /*** CHANGE THIS, HARDCODED REQUEST ***/
    
    sprintf(request,
             "GET %s%s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "\r\n\r\n", argv[1], "/", argv[1]);
    request_length = strlen(request);
    
    //
    if ((sockfd = openClientSocket(argv[1])) == -1)
    {
        //TODO exception
        free(response);
        return -1;
    }
    
    //
    if ((length = clientSend(sockfd, request_length, request)) == -1)
    {
        //TODO exception
        perror("ERROR send ");
        close(sockfd);
        free(response);
        return -1;
    }
    if (length != (signed)request_length)
    {
        fprintf(stderr, "not everything was sent\n");
    }
    
    //
    if ((length = clientRecv(sockfd, MAXLINE-1, &response)) == -1)
    {
        //TODO exception
        perror("ERROR recv ");
        close(sockfd);
        free(response);
        return -1;
    }
    if (length < MAXLINE) // connection closed
    {
        fprintf(stderr, "not everything was received\n"); //TODO correct length
        // do nothing
    }
    
    // print message
    write(1, response, length);
    
    fprintf(stdout, "\n!!! REACHED THE END !!!\n");
    close(sockfd);
    free(response);
    return 0;
}
