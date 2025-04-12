/*
    A TCP server is a server that communicates with clients using the Transmission Control 
    Protocol (TCP). 
    TCP is a reliable, connection-oriented protocol that ensures the delivery of data in the 
    correct order without loss.
*/


/*
    struct sockaddr_in {
    short sin_family;         // Address family (AF_INET for IPv4)
    unsigned short sin_port;  // Port number (in network byte order)
    struct in_addr sin_addr;   // IP address (in network byte order)
    char sin_zero[8];         // Padding to make the structure the same size as `struct sockaddr`
};
*/

/*
    What is socket ? ->

    A socket is an endpoint for communication between two machines over a network. In the context of network
    programming, a socket allows for sending and receiving data between a client and server, typically
    over a network like the Internet or a local network.
*/


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8181


int main (int argc , char *args[]) {

    
    //A socket file descriptor is a unique identifier (usually an integer) 
    //returned by the system when a socket is created using the socket() function.
    int s , c;
    char buf[512];
    char *data;


    //unsigned intger 
    socklen_t addrlen;

    // strcut socket_in -> represent an internet socket address
    //struct havin two obj var
    struct sockaddr_in srv , cli;

    memset(&srv , 0 , sizeof(srv));
    memset(&cli , 0 , sizeof(cli));

    //socket() -> used to create a socket -> returns a file descritpor that is used to perform various operation
    //takes 3 arg -> int domain , int type , int protocol
    s = socket(AF_INET , SOCK_STREAM , 0);
    
    // connection failed 
    if(s < 0) {
        printf("Socket() Error!\n");
        return -1;
    }

    //sockaddr_in  structure member
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = 0;
    srv.sin_port = htons(PORT);

    if (bind(s , (struct sockaddr *)&srv , sizeof(srv)) != 0) {
        printf("bind() Eror!\n");
        close(s);
        return -1;
    }


    if (listen(s , 5) != 0) {
        printf("listen() Eror!\n");
        close(s);
        return -1;
    }

    printf("Listening 0n  0.0.0.0:%d\n" , PORT);

    c = accept(s , (struct sockaddr *)&srv , &addrlen);

    if (c < 0)  {
        printf("accept() Error!\n");
        close(s);
        return -1;
    }

    printf("Client Connected\n");

    read(c , buf , 511);

    data = "httpd v1.0\n";
    write(c , data , strlen(data));

    close(s);
    close(c);

    return 0;
}

//commmands to use -> 
// netstat -an | grep LISTEN
//telnet connection to local host  -> env - telnet localhost 8181