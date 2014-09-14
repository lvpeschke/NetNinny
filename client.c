#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//#include <cstring>
//#include <pthread.h>

#include <errno.h>
//#include "exceptions.h"

//using namespace std;

#define MAXLINE 1000

/* Getting the socket address */
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main(int argc, char* argv[])
{
    int res;
    struct addrinfo hints, *servinfo;
    int sockfd;
    //char s[INET6_ADDRSTRLEN];
    //const char* sbis;
    
    char request[MAXLINE + 1];
    char response[MAXLINE + 1];
    int request_length;
    int length;
    
    if (argc != 2) {
        fprintf(stderr,"Missing hostname to connect to\n");
        return -1;
    }
    
    
    /*** CHANGE THIS, HARDCODED REQUEST ***/
    sprintf(request,
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "\r\n \r\n", "/rfc/rfc1945.txt", argv[1]);
    request_length = strlen(request);
    
    
    /* Getting information about the server */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((res = getaddrinfo(argv[1], "http", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "ERROR getaddrinfo: %s\n", gai_strerror(res));
        freeaddrinfo(servinfo);
        return 1;
    }
    fprintf(stdout, "passed 1\n");
    
    /* Create socket */
    // Loop?
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                         servinfo->ai_protocol)) == -1)
    {
        perror("ERROR socket ");
        freeaddrinfo (servinfo);
        exit(-1);
    }
    fprintf(stdout, "passed 2\n");
    
    /*if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen ) != 0)
    {
        perror("ERROR bind ");
        freeaddrinfo (servinfo);
        close(sockfd);
        exit(-1);
    }
    fprintf(stdout, "passed 3\n");*/
    
    /* Connecting to the server */
    if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) != 0)
    {
        perror("ERROR connect ");
        freeaddrinfo (servinfo);
        close(sockfd);
        exit(-1);
    }
    fprintf(stdout, "passed 4\n");
    
    /* Printing server IP */
    /*if ((sbis = inet_ntop(servinfo->ai_family, get_in_addr((struct sockaddr *)servinfo->ai_addr), s, sizeof s)) == NULL)
    {
        perror("ERROR inet_ntop ");
        freeaddrinfo(servinfo);
        close(sockfd);
        exit(-1);
    }
    printf("Client connecting to %s\n", s);
    fprintf(stdout, "passed 5\n");*/
    
    /* Clean up */
    freeaddrinfo(servinfo);
    
    /* Send request */
    if ((length = send(sockfd, request, request_length, 0)) == -1)
    {
        perror("ERROR send ");
        close(sockfd);
        exit(-1);
    }
    
    /* Get message */
    if ((length = recv(sockfd, response, 100, 0)) == -1)
    {
        perror("ERROR recv ");
        close(sockfd);
        exit(-1);
    } else if (length == 0) // connection closed
    {
        // do nothing
    } else {
        // print message
        write(1, response, length);
    }
    fprintf(stdout, "\n passed 6\n");
    
    if ((length = recv(sockfd, response, MAXLINE, 0)) == -1)
    {
        perror("ERROR recv ");
        close(sockfd);
        exit(-1);
    } else if (length == 0) // connection closed
    {
        // do nothing
    } else {
        // print message
        write(1, response, length);
    }
    fprintf(stdout, "\n passed 7\n");

    fprintf(stdout, "!!! REACHED THE END !!!\n");
    close(sockfd);
    exit(0);
}