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

// Функция для удаления узла по значению socket
void remove_node(Node** head, int socket) {
    if (*head == NULL) return; // Список пуст

    Node* current = *head;

    // Поиск узла с нужным socket
    while (current != NULL && current->socket != socket) {
        current = current->next;
    }

    if (current == NULL) return; // Узел не найден

    // Если узел является головой
    if (current == *head) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        // Перенастройка указателей соседних узлов
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    free(current); // Освобождение памяти
}

// Функция для удаления узла по указателю
void remove_node_by_pointer(Node** head, Node* node_to_remove) {
    if (!head || !node_to_remove) return; // Проверка на NULL

    // Если узел является головой списка
    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        if (*head) {
            (*head)->prev = NULL;
        }
    } else {
        // Перенастраиваем указатели соседних узлов
        Node* prev_node = node_to_remove->prev;
        Node* next_node = node_to_remove->next;

        if (prev_node) {
            prev_node->next = next_node;
        }
        if (next_node) {
            next_node->prev = prev_node;
        }
    }

    free(node_to_remove); // Освобождаем память
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

