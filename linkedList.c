#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* next;
    struct node* prev;
};

struct linkedList {
    struct node* head;
    struct node* tail;
    int size;
};

void insert(struct linkedList* list , int value) {
    struct node* node = malloc(sizeof(struct node));
    node->val = value;
    node->next = NULL;
    node->prev = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        list->size++;
        return;
    }

    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
    list->size++;
}

void printList(struct linkedList* list) {
    struct node* node = list->head;

    while (node != NULL) {
        (node->next != NULL ? printf("%d, ", node->val) : printf("%d\n", node->val));
        node = node->next;
    }
}

void destroyList(struct linkedList* list) {
    struct node* current = list->head;
    struct node* temp;

    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }

    free(list);
}

int main(void) {
    
    struct linkedList* list = malloc(sizeof(struct linkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    for (int i = 0; i < 20; i++) {
        insert(list,i+1);
    }

    printList(list);
    destroyList(list);

    return 0;
}

