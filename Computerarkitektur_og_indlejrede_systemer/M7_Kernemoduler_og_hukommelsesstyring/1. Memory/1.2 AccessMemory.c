#include <stdlib.h>
#include <stdio.h>

void main() {
	// Allocate an array of ints with size 20.
	int *ptr = (int *)malloc(20 * sizeof(int));

	// Assign some values.
	for (int i = 0; i < 20; i++) {
    	      ptr[i] = i * 2;
	}

	// Print the values.
	for (int i = 0; i < 20; i++) {
    	      printf("%d\n", ptr[i]);
	}

	// Lets free it.
	free(ptr);
	printf("\n");

	// Lets check what is left.
	for (int i = 0; i < 20; i++) {
    	      printf("%d\n", ptr[i]);
	}
}
