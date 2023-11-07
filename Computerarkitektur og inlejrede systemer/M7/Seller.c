#include <stdio.h> // For printing
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "Market.h" // Include Market structs

void main()
{
    int fd_shm = shm_open(SHARED_MEM_NAME, O_RDWR, 0); // mode is 0, because we arent creating a new file
    if (fd_shm == -1)
    {
        perror("shm error. Unable to open shared memory.\n");
        exit(1);
    }
    
    struct Market *sh_ptr = mmap(NULL, sizeof(struct Market), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (sh_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    printf("Shared memory accessed.\n");

    
    char BookTitle[255];
    // Total size of bookarray, divided by size of 1 element. Gives how many elements in the array
    int BookCapacity = sizeof(sh_ptr->books) / sizeof(struct Book);
    
	while(1) {
        if (sh_ptr->numberOfBooks < BookCapacity) {   // Room for an extra book?
            // Now creating new book
            sprintf(BookTitle, "Bk[%d]", sh_ptr->bookIDtracker);
            
            strcpy(sh_ptr->books[sh_ptr->numberOfBooks].title, BookTitle);
            sh_ptr->books[sh_ptr->numberOfBooks].price = rand() % 100 + 1; 
            printf("Added %s to the market, which costs: %d$\n", BookTitle, sh_ptr->books[sh_ptr->numberOfBooks].price);

            sh_ptr->numberOfBooks++;
            sh_ptr->bookIDtracker++;
        } 
        // Else there are no books currently.
        else {
            printf("Too many books, cant sell?\n");
        }
    	sleep(2);
    }
}