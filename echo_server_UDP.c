#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>


void str_echo(int sockfd,struct sockaddr* cliaddr,int clilen)
{

int n,bufsize=1024,addrlen;
char *buf=malloc(bufsize);
int adrlen;

for(;;)
{
addrlen=clilen;
n=recvfrom(sockfd,buf,bufsize,0,cliaddr,&addrlen);
sendto(sockfd,buf,n,0,cliaddr,addrlen);
}
}


int main()
{

int sockfd;
struct sockaddr_in servaddr,cliaddr;

if((sockfd=socket(AF_INET,SOCK_DGRAM,0))>0)
printf("Socket is created\n");

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(15001);

printf("Address before bindin:%s\n",inet_ntoa(servaddr.sin_addr));

if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==0)
printf("Binding the socket\n");

str_echo(sockfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

return 0;
}

