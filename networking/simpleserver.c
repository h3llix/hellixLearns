#include "unp.h"
#include <time.h>


// network byte order is always big endian which
// may differ from host byte order, hence htonl

// host to network short -> htonl 
// host to network long -> htons

int main(int argc, char **argv){
    int connfd, listenfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
    // don't bind to any specific ip
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13);	/* daytime server */

    // Anyway, the struct sockaddr holds socket address information for many types of sockets.

    // struct sockaddr {
    //     unsigned short    sa_family;    // address family, AF_xxx
    //     char              sa_data[14];  // 14 bytes of protocol address
    // }; 

    // sa_family can be a variety of things, but it’ll be AF_INET (IPv4) or AF_INET6 (IPv6) for everything we do in this document
    //. sa_data contains a destination address and port number for the socket. This is rather unwieldy since you don’t want to 
    //tediously pack the address in the sa_data by hand.

    // https://students.mimuw.edu.pl/SO/Linux/Kod/include/linux/in.h.html

    //     struct sockaddr_in {
    //     short int          sin_family;  // Address family, AF_INET
    //     unsigned short int sin_port;    // Port number
    //     struct in_addr     sin_addr;    // Internet address
    //     unsigned char      sin_zero[8]; // Same size as struct sockaddr
    // };
    // To deal with struct sockaddr, programmers created a parallel structure: struct sockaddr_in (“in” for “Internet”) 
    //to be used with IPv4.

    // And this is the important bit: a pointer to a struct sockaddr_in can be cast to a pointer to a struct sockaddr and vice-versa. 
    // So even though connect() wants a struct sockaddr*, you can still use a struct sockaddr_in and cast it at the last minute!

    Bind(listenfd, (SA *) &servaddr , sizeof(servaddr));
    
    // listenq -> queue -> 1024
    Listen(listenfd, LISTENQ)

    for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

		Close(connfd);
	}

    

}