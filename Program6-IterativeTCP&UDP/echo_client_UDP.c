#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>



void str_cli(FILE *fp,int sockfd,struct sockaddr* address,int servlen)
{
int bufsize=1024,n;

char *buf=malloc(bufsize);
int addrlen=sizeof(struct sockaddr_in);
while(fgets(buf,bufsize,fp)!=NULL)
{
sendto(sockfd,buf,sizeof(buf),0,address,servlen);
if((n=recvfrom(sockfd,buf,bufsize,0,NULL,NULL))>0)

fputs(buf,stdout);

}
printf("\nEOF\n");
}



int main(int argc,char *argv[])
{

int sockfd;
struct sockaddr_in address;

if((sockfd=socket(AF_INET,SOCK_DGRAM,0))>0)
printf("Socket created\n");

address.sin_family=AF_INET;
address.sin_port=htons(15001);

inet_pton(AF_INET,argv[1],&address.sin_addr);

str_cli(stdin,sockfd,(struct sockaddr *)&address,sizeof(address));
exit(0);;
} 
