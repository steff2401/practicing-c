#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// This program fills an array of chosen size n with numbers from 1 to and including n
int main(void) {

    printf("Choose the length of the array: ");
    int length;
    scanf("%d", &length);
    printf("\n");

    int* ptr = (int*)malloc(sizeof(int)*length);

    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < length; i++) {
        ptr[i] = i+1; // same as *(ptr+i) = i+1
    }

    for (int i = 0; i < length; i++) {

        printf("%d, ", ptr[i]);
        printf("Memory adress: %p\n",&ptr[i]);
    }
    printf("\n");
 
    free(ptr);
    return 0;
}

 