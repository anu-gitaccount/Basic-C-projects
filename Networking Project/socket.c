
/*
    This program just make connection to www.yahoo.com as a client and get some header Info
    A socket is an endpoint for sending or receiving data across a network. 
    It enables communication between two devices

*/




/*
    terminal commands to make connection with tcp/ip 
    sockets : in terminal

    (Domain address = google.com) -> nc www,google.se 80

    HEAD / HTTP/1.0

    (WE WILL GET SOME INFO LIKE THIS)

    HTTP/1.0 200 OK
    Content-Type: text/html; charset=ISO-8859-1
    Content-Security-Policy-Report-Only: object-src 'none';base-uri 'self';script-src 'nonce-9R_lI-u7_xvN_Jr1ay5l4A' 'strict-dynamic' 'report-sample' 'unsafe-eval' 'unsafe-inline' https: http:;report-uri https://csp.withgoogle.com/csp/gws/other-hp
    P3P: CP="This is not a P3P policy! See g.co/p3phelp for more info."
    Date: Tue, 17 Sep 2024 19:36:00 GMT
    Server: gws
    X-XSS-Protection: 0
    X-Frame-Options: SAMEORIGIN
    Expires: Tue, 17 Sep 2024 19:36:00 GMT
    Cache-Control: private
    Set-Cookie: AEC=AVYB7coduMADTRd2QZOPpj3ul85Cy0SzgyLHVpS6ttxkAT2T-c4Wyj8YdQ; expires=Sun, 16-Mar-2025 19:36:00 GMT; path=/; domain=.google.com; Secure; HttpOnly; SameSite=lax
    Set-Cookie: NID=517=EUlSEX6IWZX_tPScxpkQ5hzJHLHUNdnxy0OqAU7dovAMosTZehX2fj7L4r8zOtBOd9EjMUUuifJkRo6DX6o3-ik8bKUMllhuKMpp-aYIpSc1qNsW1U81M2zKIEvaWgIX0OCka4TPTY00YntcD_M_CVwtkX5AU6eqbcFl8aQsmgJ3zKVsfuFXjr3RhBRb1ZSu; expires=Wed, 19-Mar-2025 19:36:00 GMT; path=/; domain=.google.com; HttpOnly

    to get the hardcoded ip addresswe can use commands
    -> host www.google.se
    (host commmand)

    -> nslookup www.google.se

    -> ping www.google.se


*/

//Note imp = we can use strace with -o file
//  strace -f ./sockets

//to use any linux command in vim :!linux cmd

// note -> when we dont know the format of structure type we can use grap command
//grep -r sockaddr_in /usr/include/x86_64-linux-gnu 
///usr is gnu directory

/*
    This code establishes a connection to a remote server over a network 
    using a TCP socket
*/

#include <stdio.h>
#include <sys/types.h>
//for socket() func
//A socket file descriptor is a unique identifier (usually an integer) returned by the system when a socket is created using the socket() function.
#include <sys/socket.h>
//for inet_addr() that converts ip num and dots notation to binary
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define IP "98.137.11.164" // www.yahoo.com
#define PORT 80 


int main(int argc , char *args[]) {

    //socket return val
    int s;

    // structual type : we put ip add here
    //struct  sock_addr_in -> specifies the addres for the socket
    //s_addr = ip addres stored in binary format
    struct sockaddr_in sock;

    char buf[512];

    char *data = "HEAD / HTTP/1.0\r\n\r\n";

    // man 2 sockst 
    /* int socket(int domain, int type, int protocol); */
    // AF_INET      IPv4 Internet protocols  ip(7)
    //SOCK_STREAM -> Provides  sequenced,  reliable, two-way, connection-based byte 
    //streams.  An out-of-band data transmission  mechanism may be supported.

    s = socket(AF_INET , SOCK_STREAM , 0);

    if (s < 0) {
        printf("Socket() error\n");
        return -1;
    }

    //sets the IP address for the socket using the IP string.
    //inet_addr() -> converst the host address from IPV4 num and dots to binary
    //in network order || on succes -> returns converted IP
    //-> on fail -1 
    sock.sin_addr.s_addr = inet_addr(IP);
    
    //htons() -> function converts the unsigned short integer hostshort from host 
    //byte order to network byte order.
    sock.sin_port = htons(PORT);

    sock.sin_family = AF_INET;


    //connect ->  (int sockfd , const struct sockaddr *addr , socklen_t addrlen);
    //return value  -> 0 it work other not works
    
    if (connect(s , (struct sockaddr *)&sock , sizeof(struct sockaddr_in)) != 0) {
        printf("cpnnect()  Error!\n");
        //closing the socket
        close(s);
        return -1;
    }


    write(s , data , strlen(data));

    memset(buf , 0 , 512);

    int bytes = read(s , buf , 511);

    if (bytes > 0) {
        buf[bytes] = '\0';
        printf("\n%s\n" , buf);
    }
    else {
        printf("read() error or no data recieved\n");
    }

    close(s);

    return 0;
}

