/*
 * socket_client.c
 *
 *  Created on: Mar 15, 2014
 *      Author: nerohwang
 */
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>       //pthread_t , pthread_attr_t and so on.
#include<stdio.h>
#include<netinet/in.h>      //structure sockaddr_in
#include<arpa/inet.h>       //Func : htonl; htons; ntohl; ntohs
#include<assert.h>          //Func :assert
#include<string.h>          //Func :memset
#include<unistd.h>          //Func :close,write,read
#define SOCK_PORT 6666
#define BUFFER_LENGTH 10240
int main(int argc,char *argv[])
{
    int sockfd;
    int tempfd;
	int i,send_times;
    struct sockaddr_in s_addr_in;
    char data_send[BUFFER_LENGTH];
    char data_recv[BUFFER_LENGTH];
    memset(data_send,0,BUFFER_LENGTH);
    memset(data_recv,0,BUFFER_LENGTH);
	
	if(argc <3){
		send_times=2;
	}else{
		send_times=atoi(argv[2]);
	}

	printf("send_times:%d\n",send_times);
    if(argc < 2){
		printf("%s 172.18.11.204\n",argv[0]);
		exit(0);
    }
	sockfd = socket(AF_INET,SOCK_STREAM,0);       //ipv4,TCP
    if(sockfd == -1)
    {
        fprintf(stderr,"socket error!\n");
        exit(1);
    }

    //before func connect, set the attr of structure sockaddr.
    memset(&s_addr_in,0,sizeof(s_addr_in));
    s_addr_in.sin_family = AF_INET;
    s_addr_in.sin_port = htons(SOCK_PORT);
    if( inet_pton(AF_INET, argv[1], &s_addr_in.sin_addr) <= 0){
		printf("inet_pton error for %s\n",argv[1]);
		exit(0);
    }
	printf("dport:%d\n",s_addr_in.sin_port);
    //s_addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");      //trans char * to in_addr_t
    tempfd = connect(sockfd,(struct sockaddr *)(&s_addr_in),sizeof(s_addr_in));
    if(tempfd == -1)
    {
        fprintf(stderr,"Connect error! \n");
        exit(1);
    }

    while(1)
    {
        printf("Please input something you wanna say(input \"quit\" to quit):\n");
        gets(data_send);
        //scanf("%[^\n]",data_send);         //or you can also use this
		for(i=0;i<send_times;i++){
		    tempfd = write(sockfd,data_send,sizeof(data_send));
			if(tempfd == -1){
				fprintf(stderr,"write error\n");
				exit(0);
			}
			tempfd = read(sockfd,data_recv,BUFFER_LENGTH);
			assert(tempfd != -1);
			printf("%s\n",data_recv);
			memset(data_recv,0,BUFFER_LENGTH);
        }

        if(strcmp(data_send,"quit") == 0)  //quit,write the quit request and shutdown client
        {
            break;
        }
        memset(data_send,0,BUFFER_LENGTH);
    }

    int ret = shutdown(sockfd,SHUT_WR);       //or you can use func close()--<unistd.h> to close the fd
    assert(ret != -1);
    return 0;
}
