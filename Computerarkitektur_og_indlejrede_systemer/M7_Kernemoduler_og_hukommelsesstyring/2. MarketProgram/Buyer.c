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
        printf("%d Number of books\n", sh_ptr->numberOfBooks);
        if (sh_ptr->numberOfBooks > 0) {   // If market is not empty, try to buy book
            // Buy new book
            sh_ptr->numberOfBooks--;
            printf("Bought %s from the market, at the cost: %d$\n", sh_ptr->books[sh_ptr->numberOfBooks].title, sh_ptr->books[sh_ptr->numberOfBooks].price);
        }
        // Else there are no books currently.
        else {
            printf("No books on the market to buy\n");
        }
        sleep(5.1);
    }
}
