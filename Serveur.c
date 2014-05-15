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



int main(int argc, char const *argv[])
{

   
    SOCKET sock, csock;
    SOCKADDR_IN sin ,csin;
    char buffer [255];
    int csin_size;
    
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(Port);

    init();
    
    sock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP );
    if ( sock == INVALID_SOCKET ) { perror("socket ()"); exit(1);}
    
    if ( bind( sock , (SOCKADDR *) &sin , sizeof(sin)) == SOCKET_ERROR ) { perror("bind ()"); exit(2);}
    
    if ( listen(sock , 5 ) == SOCKET_ERROR ) { perror("listen ()"); exit(3);}
    
       
    csin_size = sizeof(csin);

        csock = accept( sock , (SOCKADDR *) &csin, &csin_size );
        if ( csock == INVALID_SOCKET ) { perror("accept ()"); exit(4);}
    
        if ( recv( csock , buffer , sizeof(buffer) , 0 ) == -1 ) { perror("recv ()"); exit(5);}
    
        printf("Server recieve : %s\n",buffer); 
    
        if ( closesocket( csock ) ==-1 ) { perror("closesocket ()"); exit(6);}
    	if ( closesocket( sock ) ==-1 ) { perror("closesocket ()"); exit(7);}
    
    end();	

	return 0;
}

