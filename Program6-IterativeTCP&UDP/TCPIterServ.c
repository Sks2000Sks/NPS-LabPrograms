#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>

void str_echo(int connfd)
{
int n;
int bufsize=1024;
char *buf=malloc(bufsize);

again: while((n=recv(connfd,buf,bufsize,0))>0)
	send(connfd,buf,n,0);

	if(n<0)
		goto again;
}



int main()
{
int sockfd,connfd,addrlen;
struct sockaddr_in servaddr,cliaddr;

if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
printf("Socket is created\n");

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(15001);
printf("Address before bindin:%s\n",inet_ntoa(servaddr.sin_addr));

if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==0)
printf("Binding the socket\n");
printf("The address after binding is : %s/n",inet_ntoa(servaddr.sin_addr));

listen(sockfd,3);
printf("The server is listening\n");


for(;;)
{
addrlen= sizeof(struct sockaddr_in);
connfd= accept(sockfd,(struct sockaddr*)&cliaddr,&addrlen);
printf("The client is connected\n");


printf("The client %s is connected on port %d\n",inet_ntoa(cliaddr.sin_addr),htons(cliaddr.sin_port));

str_echo(connfd);
close(connfd);
}
return 0;
}













