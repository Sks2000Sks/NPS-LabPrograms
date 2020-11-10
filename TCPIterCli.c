#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>

void str_cli(FILE *fp,int sockfd)
{
int bufsize=1024,n;

char *buf=malloc(bufsize);
while(fgets(buf,bufsize,fp)!=NULL)
{
send(sockfd,buf,sizeof(buf),0);
if((n=recv(sockfd,buf,bufsize,0))>0)

fputs(buf,stdout);

}
printf("\nEOF\n");
}



int main(int argc,char *argv[])
{

int sockfd;
struct sockaddr_in address;

if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
printf("Socket created\n");

address.sin_family=AF_INET;
address.sin_port=htons(15001);

inet_pton(AF_INET,argv[1],&address.sin_addr);

if(connect(sockfd,(struct sockaddr *)&address,sizeof(address))==0)
printf("Client is connecting to %s\n",argv[1]);
else
printf("Error in connect\n");

str_cli(stdin,sockfd);
return(close(sockfd));
} 
