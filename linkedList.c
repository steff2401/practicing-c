#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

struct Node {
    int val;
    struct Node *next;
    struct Node *prev;
};

struct LinkedList {
    struct Node *head;
    struct Node *tail;
    int size;
    int bucketIndex; // to use with hashmap
};

struct LinkedList* createEmptyList(void);
struct Node* createNode(int value);
void insertNode(struct LinkedList *list, int value);
void removeNode(struct LinkedList *list, int value);
void printList(struct LinkedList *list);
void destroyList(struct LinkedList *list);

struct LinkedList* createEmptyList(void) {
    struct LinkedList *list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    if (!list) {
        printf("Allocation of memory failed.\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

struct Node* createNode(int value) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Allocation of memory failed.\n");
        exit(EXIT_FAILURE);
    }

    node->val = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insertNode(struct LinkedList *list, int value) {
    struct Node *node = createNode(value);

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->size++;
}

void removeNode(struct LinkedList *list, int value) {
    if (list->size == 0) {
        printf("Could not delete %d: list is empty.\n", value);
        return;
    }

    // if value in head
    if (list->head->val == value) {
        struct Node *temp = list->head;
        list->head = list->head->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL; // List is now empty
        }
        free(temp);
        list->size--;
        return;
    }

    // if value in tail (here it's guranteed to be at least two elements in list)
    if (list->tail->val == value) {
        struct Node *temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);
        list->size--;
        return;
    }

    // if value not in head or tail
    struct Node *node = list->head;
    while (node != NULL) {
        if (node->val == value) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            free(node);
            list->size--;
            return;
        }
        node = node->next;
    }
    printf("Could not delete %d: value not in list.\n", value);
}

void printList(struct LinkedList *list) {
    if (list->size == 0) {
        printf("List is empty.\n");
        return;
    }
    
    struct Node *node = list->head;
    while (node != NULL) {
        (node->next != NULL ? printf("%d, ", node->val) : printf("%d\n", node->val));
        node = node->next;
    }
}

void destroyList(struct LinkedList *list) { 
    struct Node *current = list->head;
    struct Node *temp;

    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }

    free(list);
}
