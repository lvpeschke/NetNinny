/* constants.cpp
 *
 * Written by  : Chvatal Martin & Peschke Lena
 * Written for : LiU, TDTS06, lab 2
 * Date        : Sept. 2014
 * Version     : 1.0
 */

#ifndef CONSTANTS_565441654
#define CONSTANTS_565441654

#define BUFFERSIZE 1000

// Header used in the HTTP response in case of bad url.
#define BAD_URL_HEADER "HTTP/1.1 302 Found\r\nLocation: http://www.ida.liu.se/~TDTS04/labs/2011/ass2/error1.html\r\nConnection: close\r\n\r\n"

// Header used in the HTTP response in case of bad content.
#define BAD_CONTENT_HEADER "HTTP/1.1 302 Found\r\nLocation: http://www.ida.liu.se/~TDTS04/labs/2011/ass2/error2.html\r\nConnection: close\r\n\r\n"

// Error that occurs when the host name is NULL.
#define HOST_ERR "Host name is empty"

// Error that occurs when socket cannot be created.
#define SOCK_ERR "Cannot create socket"

// Error that occurs when socket cannot be bound to port.
#define BIND_ERR "Cannot bind port to socket" 

// Error that occurs when listening on socket fails.
#define LIST_ERR "Cannot set socket to listening state" 

// Error that occurs when sending data fails.
#define SEND_ERR "Cannot send data through socket"

// Error that occurs when socket cannot receive data.
#define RECV_ERR "Cannot receive data from the socket" 

// Error that occurs when accept function fails.
#define ACCE_ERR "Cannot accept connection" 

// Error that occurs when getaddrinfo function fails.
#define ADDR_ERR "Error with initial socket setting" 

// Error that occurs when connect function fails.
#define CONN_ERR "Connection to socket failed"

// Message used when proxy receives data of zero length, signing end of connection.
#define CONNECTION_CLOSED "Connection closed by the other side"

#endif
