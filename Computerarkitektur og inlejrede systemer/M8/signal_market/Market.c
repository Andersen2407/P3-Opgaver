#include <stdio.h> // For printing
#include <string.h> // strcpy
#include <stdlib.h> // exit(1)
#include <sys/mman.h>   //mmap()
#include <unistd.h>     // sleep
#include <fcntl.h>      // no cluex
#include <signal.h>     // Use Signals
#include "Market.h"

// For signaling, we must have a static volatile atomic because of race conditions and scope.
static volatile sig_atomic_t got_signal = 0;

void sigint_callback(int signal)
{
    // Instead of doing the shutdown here, we use the got_signal instead.
    // This is because we need to unmap the shared memory.
    // This is easier in the scope of the shared memory pointer.
    printf("\nGraceful beautiful shutdown. Unlinking!");
    got_signal = 1;
}

void main()
{
    signal(SIGINT, sigint_callback);

    // 1 = execute, 2 = write, 4 = read (https://chmod-calculator.com/)
    /*
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;   // 660
    printf("Mode: %d\n", mode);
    */

    // We need to open our shared memory.
    int fd_shm = shm_open(SHARED_MEM_NAME, O_RDWR | O_CREAT, 0660); //

    // If we were not able to acess the shared memory.
    if (fd_shm == -1)
    {
        perror("shm error. Unable to open shared memory.\n");
        exit(1);
    }
    // Make shm file a certain length (size of the Market)
    ftruncate(fd_shm, sizeof(struct Market));
    // Create pointer to the shared memory
    // creates a new mapping in the virtual address space
    struct Market *shared_mem_ptr = mmap(NULL, sizeof(struct Market), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);

    // If mmap failed.
    if (shared_mem_ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    printf("Shared memory made \n");

    // We need to temp store the vars of a book.
    // We do that in a buffer
    char buffer[10];
    while (got_signal == 0)
    {
        // Are there any books in the market curently?
        if (shared_mem_ptr->numberOfBooks > 0)
        { // If market has a book
            printf("\n\n\nBOOKS IN DA HOOD?:\n");
            for (int i = 0; i < shared_mem_ptr->numberOfBooks; i++)
            {
                strcpy(buffer, shared_mem_ptr->books[i].title); // Copy book title to buffer
                printf("%s<%d$> | ", buffer, shared_mem_ptr->books[i].price);                 // Print book title and price
            }
            printf("\n");
        }
        else
        {
            printf("No books?\n");
        }
        sleep(1);
    }

    // When the siging signals comes
    // Then we must deallocate the shared memory.
    // We also check if the deallocation was a succes.
    if (munmap(shared_mem_ptr, sizeof(shared_mem_ptr)) == -1) {
        perror("munmap");
        exit(1);
    }

    // Now that we have deallocated the shared memory we also need to remove the memory in the /mnt/dev/shm. 
    // We also check if it was successful.
    if (shm_unlink(SHARED_MEM_NAME) == -1) {
        perror("shm_unlink");
        exit(1);
    }
}