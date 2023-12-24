#include <stdio.h>
#include <stdlib.h>

struct Heap {
    int maxSize, currentSize;
    int *array;
};

void insert(struct Heap *heap, int element);
int removeMin(struct Heap *heap);
void printHeap(struct Heap *heap);
void destroyHeap(struct Heap *heap);

int main(void) {
    
    struct Heap *heap = malloc(sizeof(struct Heap));
    if (heap == NULL) {
        printf("Allocation of memory failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("Choose the maxiumum elements the heap can contain: ");
    scanf("%d", &heap->maxSize);
    heap->currentSize = 0;
    heap->array = calloc(heap->maxSize, sizeof(int));
    if (heap->array == NULL) {
        printf("Allocation of memory failed.\n");
        exit(EXIT_FAILURE);
    }

    insert(heap, 20);
    insert(heap, 15);
    insert(heap, 30);
    insert(heap, 5);
    insert(heap, 10);

    printf("Heap: ");
    printHeap(heap);

    while (heap->currentSize > 0) {
        int min = removeMin(heap);
        printf("Heap after removing the minimum (%d): ", min);
        printHeap(heap);
    }

    return 0;
}

void insert(struct Heap *heap, int element) {
    if (heap->currentSize >= heap->maxSize) {
        printf("Heap is full.\n");
        destroyHeap(heap);
        exit(EXIT_FAILURE);
    }

    heap->array[heap->currentSize] = element;
    int i = heap->currentSize;
    int parentIndex = (i-1)/2;

    while (i > 0 && heap->array[parentIndex] > heap->array[i]) {
        int temp = heap->array[parentIndex];
        heap->array[parentIndex] = heap->array[i];
        heap->array[i] = temp;

        i = parentIndex;
        parentIndex = (i-1)/2;
    }
    heap->currentSize++;
}

int removeMin(struct Heap *heap) {
    if (heap->currentSize <= 0) {
        printf("Heap is empty.\n");
        destroyHeap(heap);
        exit(EXIT_FAILURE);
    }

    int min = heap->array[0];
    heap->currentSize--; 
    heap->array[0] = heap->array[heap->currentSize];

    int i = 0;
    while (2*i+1 < heap->currentSize) { 
        int leftChildIndex = 2*i+1;
        int rightChildIndex = 2*i+2;
        int smallestChildIndex = leftChildIndex;

        if (rightChildIndex < heap->currentSize && heap->array[rightChildIndex] < heap->array[leftChildIndex]) {
            smallestChildIndex = rightChildIndex;
        }

        if (heap->array[i] <= heap->array[smallestChildIndex]) {
            break;
        }

        int temp = heap->array[smallestChildIndex];
        heap->array[smallestChildIndex] = heap->array[i];
        heap->array[i] = temp;

        i = smallestChildIndex;
    }

    return min;
}

void printHeap(struct Heap *heap) {

    for (int i = 0; i < heap->currentSize; i++) {
        printf("%d, ", heap->array[i]);
    }
    printf("\n");
}

void destroyHeap(struct Heap *heap) {
    free(heap->array);
    heap->array = NULL;
    free(heap);
    heap = NULL;
}