#include <stdio.h>
#include <stdlib.h>
int main () {
	char *str;
	int i;
	int old_addr = 0;
	int new_addr = 0;
	int diff = 0;
	for (i = 1; i < 100; i++) { 	//
    	        str = (char *) malloc(i); // 1 kB
    	        //str = (char *) calloc(1, i);  // sizeof(char) = 1
    	        new_addr = str;
    	        diff = new_addr - old_addr;
    	        old_addr = new_addr;
    	        printf("\nWasting memory! [%u] i=%u: Diff[%u]-> Header[%u] ", str, i, diff, (diff-i));
	}
	char uselessInput[80];
	printf("\nWaiting for you to analyse your memory... (press enter)");
	scanf("%s", uselessInput);
	free(str);

	return(0);
}
