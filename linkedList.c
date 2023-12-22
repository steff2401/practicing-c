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

void insert(struct linkedList* list, int value) {
    struct node* node = malloc(sizeof(struct node));
    if (node == NULL) {
        printf("Allocation of memory failed.");
        exit(EXIT_FAILURE);
    }

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

void delete(struct linkedList* list, int value) {
    if (list->size == 0) {
        return;
    }

    if (list->head->val == value) {
        struct node* temp = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp);
        list->size--;
        return;
    }

    if (list->tail->val == value) {
        struct node* temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);
        list->size--;
        return;
    }

    struct node* node = list->head;
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
    if (list == NULL) {
        printf("Allocation of memory failed.");
        exit(EXIT_FAILURE);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    for (int i = 0; i < 10; i++) {
        insert(list,i+1);
    }
    printf("List: ");
    printList(list);

    delete(list,10);
    delete(list,1);
    delete(list,5);

    printf("List after deletion of 1, 5 and 20: ");
    printList(list);
    destroyList(list);

    return 0;
}

