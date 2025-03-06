#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <time.h>
#include <string.h> 

// Структура узла двусвязного списка
typedef struct Node {
    int socket;
    struct Node* prev;
    struct Node* next;
} Node;

// Функция для создания нового узла
Node* create_node(int socket) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->socket = 0;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в конец списка
void append(Node** head, int socket) {
    Node* newNode = create_node(socket);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}



// Освобождение памяти
void free_list(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}



    //Node* head = NULL;

    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);
    //append(&head, STOP);


    
    //freeList(head);

