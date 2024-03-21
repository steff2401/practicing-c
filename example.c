#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

	int myFirstCVariable = 10;
	int x = 4;

	printf("Hello world!\n");
	printf("My favorite number is: %d\n", myFirstCVariable);
	printf("%.1f\n", (float) myFirstCVariable/x);
	printf("Memory size (in bytes) of my int variable: %lu\n", sizeof(x));

	if (myFirstCVariable > x) {
		printf("%d is greater than %d\n", myFirstCVariable, x);
	}

	int myNumbers[] = {10,20,30};
	// sizeof(myNumbers) returns 4 bytes * 3 elements = 12
	// sizeof((myNumbers[0])) returns 4 bytes (since the first element is an int)
	// length will be 12 / 4 = 3, which is correct
	int length = sizeof(myNumbers) / sizeof((myNumbers[0])); 

	for (int i = 0; i < length; i++) {
		printf("Num: %d ",myNumbers[i]);
		printf(" memory adress: %p, ", &myNumbers[i]);
	}
	printf("\n");

	char greetings[] = "Hello world!";
	printf("%s\n", greetings);

	int userNum;
	printf("Type a number: \n");
	scanf("%d", &userNum);
	printf("You typed in %d\n", userNum);

	int* ptr = (int*)malloc(1); // allokert 1 byte i minnet
	printf("%p\n", ptr);
	ptr = &myNumbers[0];
	printf("%p\n", ptr);
	printf("%d", *ptr);
	
	//free(ptr);


	printf("\n");
	return 0;
}
