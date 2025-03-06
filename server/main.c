#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sockets_queue.h"

#define MAX_CLIENTS_COUNT 3

Node* clients = NULL;

int main(){
    
    int server;
    
    server = socket(AF_INET, SOCK_STREAM, 0);
    if(server == -1){
         printf("Fail to create socket\n");
         exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in server_addr;
    
    memset(&server_addr, 0, sizeof(server_addr));
      
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
       printf("Fail to bind\n");
       close(server);
       exit(EXIT_FAILURE);
    }
    
    
    if(listen(server, MAX_CLIENTS_COUNT) == -1){
       printf("Fail to listen\n");
       close(server);
       exit(EXIT_FAILURE);
    }
    
    /*
     * Сокеты клиентов
     */ 
    
    int client = 0;
    char message[] = "Hello client!";
          
    
    while(1){
    
        client = accept(server, NULL, NULL);
        append(&clients, client);
        printf("Connected... ");
        send(client, message, strlen(message), 0);
        
        char recieved_msg[256];
        recv(client, recieved_msg, sizeof(recieved_msg) - 1, 0);
        recieved_msg[sizeof(recieved_msg) - 1] = '\0';
        printf("%s\n", recieved_msg);
    
    }
           
         
    
    return 0;
}
