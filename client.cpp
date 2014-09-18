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
        throw CSocketException(NO_HOST);
    }
    
    // Getting information about the server
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((res = getaddrinfo(hostname, "http", &hints, &servinfo)) != 0)
    {
        //freeaddrinfo(servinfo);
        throw CSocketException (ADDR_ERR);
    }
    fprintf(stdout, "correct address\n"); ///
    
    /* Create socket */
    // TODO Loop?
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                         servinfo->ai_protocol)) == -1)
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
    
    /* Return the valid file descriptor */
    return sockfd;
}

ssize_t clientSend(int sockfd, size_t request_length, char *request)
{
    ssize_t length;
    if ((length =
         send(sockfd, request, request_length, 0)) == -1)
    {
        close(sockfd);
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
        close(sockfd);
        throw CSocketException(RECV_ERR);
    }
    fprintf(stdout, "received\n"); ///
    
    return length;
}


CHTTPResponse &clientMain(CHTTPRequest &request)
{
    
    int sockfd;
    char requesttemp[BUFFERSIZE + 1]; ///
    char *buffer;
    CHTTPResponse *response;
    size_t request_length;
    ssize_t length;
    ssize_t response_length;
    
    /* Get the host */
    //TODO get host
    /*if (!host) {
        throw CSocketException(NO_HOST);
    }*/
    
    /*** CHANGE THIS, HARDCODED HOST ***/
    char host[] = "www.google.com";
    /*** CHANGE THIS, HARDCODED HOST ***/
    
    /* Get the request */
    /*** CHANGE THIS, HARDCODED REQUEST ***/
    sprintf(requesttemp,
            "GET %s%s HTTP/1.1\r\n"
            "Host: %s\r\n"
            "\r\n\r\n", host, "/", host);
    request_length = strlen(requesttemp);
    /*** CHANGE THIS, HARDCODED REQUEST ***/
    
    /* Set up connection */
    sockfd = openClientSocket(host);
    
    /* Send the request */
    length = 0;
    while ((length += clientSend(sockfd, request_length, requesttemp)) != (signed)request_length)
    {
        cout << "Not sent everything yet, trying again\n" << endl;
    }
    
    /* Get incoming response */
    buffer = (char *)malloc(BUFFERSIZE * (sizeof (char)));
    length = 0;
    response_length = 0;
    try
    {
        while ((length = clientRecv(sockfd, BUFFERSIZE, &buffer)) != 0) // only works with connection close
                                                                        // print message
        write(1, buffer, length); ///
    {
        response_length += length;
        // TODO treat the data
    }
    }
    catch (CSocketException e)
    {
        free(buffer);
        throw CSocketException(RECV_ERR);
    }
    
    //TODO build the response object
    
    /* Clean up 1/2 */
    close(sockfd);
    free(buffer);
    
    /*** CHANGE THIS, HARDCODED RESPONSE ***/
    response = new CHTTPResponse("HTTP/1.1 302 Found",
                                                "Cache-Control: private\r\n                                                Content-Type: text/html; charset=UTF-8c\n                                                Location: http://www.google.se/?gfe_rd=cr&ei=WDsbVOu8N4ir8wfxw4GwDw\r\n                                                Content-Length: 258\r\n                                              Date: Thu, 18 Sep 2014 20:06:48 GMT\r\nServer: GFE/2.0\r\n                                                Alternate-Protocol: 80:quic,p=0.002\r\n                                                \r\n\r\n                                                <HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n                                                <TITLE>302 Moved</TITLE></HEAD><BODY>\r\n                                                <H1>302 Moved</H1>\r\n                                                The document has moved\r\n                                                <A HREF=\"http://www.google.se/?gfe_rd=cr&amp;ei=WDsbVOu8N4ir8wfxw4GwDw\">here</A>.\r\n                                                </BODY></HTML>");
    /*** CHANGE THIS, HARDCODED RESPONSE ***/
    
    cout << "\n!!! REACHED THE END !!!\n" << endl;
    
    return *response;
}



// BACKUP
// TODO change everything
int mainClient(char *host)
{
    int sockfd;
    char request[MAXLINE + 1];
    char *response;
    size_t request_length;
    ssize_t length;
    
    if (!host) {
        throw CSocketException(NO_HOST);
    }
    
    /*** CHANGE THIS, HARDCODED REQUEST ***/
    
    sprintf(request,
            "GET %s%s HTTP/1.1\r\n"
            "Host: %s\r\n"
            "\r\n\r\n", host, "/", host);
    request_length = strlen(request);
    
    /*** CHANGE THIS, HARDCODED REQUEST ***/
    
    // initialize socket
    if ((sockfd = openClientSocket(host)) == -1)
    {
        return -1;
    }
    // sockfd is now connected
    
    //
    length = 0;
    while ((length += clientSend(sockfd, request_length, request)) != (signed)request_length)
    {
        fprintf(stderr, "not everything was sent\n");
        
        /*if (length == -1)
         {
         //TODO exception
         perror("ERROR send ");
         close(sockfd);
         return -1;
         }*/
    }
    
    response = (char *)malloc(MAXLINE * (sizeof (char))); //TODO content-length
    
    //
    try
    {
        length = clientRecv(sockfd, MAXLINE-1, &response);
    }
    catch (CSocketException e)
    {
        free(response);
        throw CSocketException(RECV_ERR);
    }
    
    // print message
    write(1, response, length);
    
    fprintf(stdout, "\n!!! REACHED THE END !!!\n");
    close(sockfd);
    free(response);
    return 0;
}
