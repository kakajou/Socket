/*
#ifdef WIN32 
	
	#include <cstdlib>
	#include <iostream>
	#include <winsock2.h>
	#include <stdlib.h>

#elif defined (linux) 
*/
	#include <stdio.h>
	#include <stdlib.h>	
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h> 
	#include <netdb.h> 

	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
	typedef struct in_addr IN_ADDR;	

	#define closesocket(s) close(s)	
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1

	#define Host "127.0.0.1"
	#define Port 2012
/*
#else 
	#error not defined for this platform
#endif
*/

static void init(void)
{ 
#ifdef WIN32
	WSADATA wsa;
	int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if(err < 0)
	{
	puts("WSAStartup failed !");
	exit(EXIT_FAILURE);
	}
#endif
}

static void end(void)
{ 
#ifdef WIN32
	WSACleanup();
#endif
}	



int main(int argc, char *argv[])
{
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer [255] = ""; 
    
    sin.sin_addr.s_addr = inet_addr(Host);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(Port);
    
    init();

    sock =  socket(  AF_INET , SOCK_STREAM , IPPROTO_TCP );
    if ( sock == INVALID_SOCKET ) { perror("socket ()"); exit(1); }
    
    if ( connect( sock , ( SOCKADDR*) &sin , sizeof (sin) ) == SOCKET_ERROR ) { perror("connect ()"); exit(2); }
    
    printf("Client send :");
    scanf("%s",&buffer);

    if ( send( sock, buffer , sizeof(buffer) , 0 ) == -1 ) { perror("send ()"); exit(3); }
    
    if (closesocket(sock) == SOCKET_ERROR ) { perror("closesocket ()"); exit(4); }
    
    end();
    
    return 0;
}