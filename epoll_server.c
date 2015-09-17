#include <sys/socket.h> 
#include <sys/epoll.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <errno.h>
#include <stdio.h>
 
#define OPEN_MAX 100
#define SERV_PORT 6666 

int main()
{
   int i, maxi, listenfd, connfd, sockfd, epfd, nfds; 
   ssize_t n; 
   char line[200];
   socklen_t clilen;

   //声明epoll_event结构体的变量, ev用于注册事件, events数组用于回传要处理的事件
   struct epoll_event ev,events[20];
   //生成用于处理accept的epoll专用的文件描述符, 指定生成描述符的最大范围为256 
   epfd = epoll_create(256);
   struct sockaddr_in clientaddr; 
   struct sockaddr_in serveraddr;
   
   //socket()
   listenfd = socket(AF_INET, SOCK_STREAM, 0);
 
   //setnonblocking(listenfd);       //把用于监听的socket设置为非阻塞方式
   ev.data.fd = listenfd;          //设置与要处理的事件相关的文件描述符
   ev.events = EPOLLIN | EPOLLET;  //设置要处理的事件类型
   
   //epoll_ctl()
   epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);     //注册epoll事件
   
   //socket addr
   memset(&serveraddr,0,sizeof(serveraddr)); 
   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
   serveraddr.sin_port = htons(SERV_PORT);  //或者htons(SERV_PORT);
   
   //bind()
   bind(listenfd,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
   //listen()
   listen(listenfd, 20);

   maxi = 0;
   while(1)
   {
       //epoll_wait()
      nfds = epoll_wait(epfd, events, 20, 500); //等待epoll事件的发生
      for(i = 0; i < nfds; ++i)                 //处理所发生的所有事件
      {
         if(events[i].data.fd == listenfd)      //监听事件
         {
            connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clilen); 
            if(connfd < 0){
               perror("connfd<0");
               exit(1);
            }
            //setnonblocking(connfd);           //把客户端的socket设置为非阻塞方式
            char *str = inet_ntoa(clientaddr.sin_addr);
            printf("connect from %s\n",str);
            ev.data.fd=connfd;                //设置用于读操作的文件描述符
            ev.events=EPOLLIN | EPOLLET;      //设置用于注测的读操作事件
            epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
            //注册ev事件
         }
         else if(events[i].events&EPOLLIN)      //读事件
         {
            if ( (sockfd = events[i].data.fd) < 0){
               continue;
            }
            if ( (n = read(sockfd, line, 200)) < 0){
               if (errno == ECONNRESET){
                  close(sockfd);
                  events[i].data.fd = -1; 
               }else{
                  printf("readline error\n");
               }
            }else if (n == 0){
               close(sockfd); 
               events[i].data.fd = -1; 
            }

            printf("receive data:%s\n",line);
            ev.data.fd=sockfd;              //设置用于写操作的文件描述符
            ev.events=EPOLLOUT | EPOLLET;   //设置用于注测的写操作事件 
            //修改sockfd上要处理的事件为EPOLLOUT
            epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
         } 
         else if(events[i].events&EPOLLOUT)//写事件
         {
            sockfd = events[i].data.fd;
            write(sockfd, line, n);
            ev.data.fd = sockfd;               //设置用于读操作的文件描述符
            ev.events = EPOLLIN | EPOLLET;     //设置用于注册的读操作事件
            //修改sockfd上要处理的事件为EPOLIN
            epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
         }
      }
   }
   return 0;
}
