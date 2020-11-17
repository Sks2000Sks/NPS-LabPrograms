#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
  

void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    

        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n'); 
  
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 

} 

int main() 
{ 
    int cont,listenfd,connfd,addrlen,addrlen2,fd,pid,addrlen3;
    
    struct sockaddr_in address,cli_address;
    if ((listenfd = socket(AF_INET,SOCK_STREAM,0)) > 0) 
    printf("The socket was created\n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15001);
   
    if (bind(listenfd,(struct sockaddr *)&address,sizeof(address)) == 0)
		printf("Binding Socket\n");
	 
  
    listen(listenfd,3);
    printf("server is listening\n");
  
    printf("The server's local address %s ...and port %d\n",inet_ntoa(address.sin_addr),htons(address.sin_port));
	for(;;)
	{
		addrlen = sizeof(struct sockaddr_in);
		connfd = accept(listenfd,(struct sockaddr *)&cli_address,&addrlen);
		
		addrlen2 = sizeof(struct sockaddr_in);
		
		printf("The Client  %s is Connected...on port %d\n",inet_ntoa(cli_address.sin_addr),htons(cli_address.sin_port));	
		if((pid=fork())==0)
		{
		  printf("inside child\n");
		  close(listenfd);
		  func(connfd);
		  exit(0);
		} 
		close(connfd);
	}
    return 0 ;
} 
