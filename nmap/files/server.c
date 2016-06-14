#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8133

int main(int argc, char** argv)
{
char str[100];
char *msg="Hello";
struct sockaddr_in server_addr;

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

int listener = socket(AF_INET,SOCK_STREAM,0);

if(listener < 0) {
    perror("Can't create socket.");
    exit(1);
}

if(bind(listener,(struct sockaddr *) &server_addr,sizeof(server_addr)) < 0) {
    perror("Can't bind socket.");
    exit(1);
}

if(listen(listener,5)) {
    perror("Erro while listening:");
    exit(1);
}

int client = accept(listener,NULL,NULL);

while(1)
{
    bzero( str, 100);
    recv(client,str, 100, 0);
    printf("Message from client - %s",str);
    send(client, msg, (int)strlen(msg), 0);
}

return 0;
}
