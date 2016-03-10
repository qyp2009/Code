//客户端

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINELENGTH 4096

int main(int argc, char** argv)
{
    int    sockfd, n;
    char    recvline[MAXLINELENGTH], sendline[MAXLINELENGTH];
    struct sockaddr_in    servaddr;

    if( argc != 2){
        printf("usage: ./client <ipaddress>\n");
        exit(0);
    }

    //socket()
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
    }

    //socket addr
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",argv[1]);
        exit(0);
    }

    //connect()
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    //send()
	printf("send msg to server: \n");
	fgets(sendline, MAXLINELENGTH, stdin);
	if( write(sockfd, sendline, strlen(sendline)) < 0){
		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	memset(recvline,0,MAXLINELENGTH);
	n = read(sockfd,recvline,MAXLINELENGTH);
	printf("response:%s\n",recvline);
    //close()
    close(sockfd);
    exit(0);
}
