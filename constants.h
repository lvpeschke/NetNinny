#ifndef CONSTANTS_565441654
#define CONSTANTS_565441654

#define BUFFERSIZE 1000

#define SOCK_ERR "Cannot create socket"
//Error that occurs when socket cannot be created.

#define BIND_ERR "Cannot bind port to socket" 
//Error that occurs when socket cannot be bound to port.

#define LIST_ERR "Cannot set socket to listening state" 
//Error that occurs when listening on socket fails.

#define SEND_ERR "Cannot send data through socket"

#define RECV_ERR "Cannot receive data from the socket" 
//Error that occurs when socket cannot receive data.

#define ACCE_ERR "Cannot accept connection" 
//Error that occurs when accept function fails.

#define ADDR_ERR "Error with initial socket setting" 
//Error that occurs when getaddrinfo function fails.

#define CONNECTION_FAIL "Connection to socket failed"
//Error that occurs when connect function fails.

#define CONNECTION_CLOSED "Connection closed by the other side" 
//Message used when proxy receives data of zero length, signing end of connection.

#endif
