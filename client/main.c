#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "192.168.0.103"  
#define PORT 8080

int main(){
   
    int my_socket;
    
    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(my_socket == -1){
         printf("Fail to create socket\n");
         exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in my_addr;
    
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

      
    if(connect(my_socket, (struct sockaddr*)&my_addr, sizeof(my_addr)) != 0) {
        printf("Can't connect\n");
        exit(EXIT_FAILURE);
    }
    
    char recieved_msg[256];
    recv(my_socket, recieved_msg, sizeof(recieved_msg) - 1, 0);
    recieved_msg[sizeof(recieved_msg) - 1] = '\0';
    printf("%s\n", recieved_msg);
    
    char message[] = "Hi, server!";
    if(send(my_socket, message, strlen(message), 0)) {
        printf("I can't send message!");
        exit(EXIT_FAILURE);
    }
           
    close(my_socket); 
    
    return 0;
}
