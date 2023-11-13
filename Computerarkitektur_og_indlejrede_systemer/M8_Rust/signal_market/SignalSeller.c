#include <stdio.h> // For printing
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include "Market.h" // Include Market structs


struct Market *sh_ptr;
void sell()
{
    char BookTitle[255];
    // Total size of bookarray, divided by size of 1 element. Gives how many elements in the array
    int BookCapacity = sizeof(sh_ptr->books) / sizeof(struct Book);

    // printf("%d Number of books\n", sh_ptr->numberOfBooks);
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
}

void timer_callback(int signum)
{
    time_t now = time(NULL);
    printf("Signal %d caught on %li \n", signum, now);
    sell();
    alarm(10); // sell every 10 seconds
}

void main()
{
    signal(SIGALRM, timer_callback);    // Make  signal alarm (will signal after n seconds)

    int fd_shm = shm_open(SHARED_MEM_NAME, O_RDWR, 0); // mode is 0, because we arent creating a new file
    if (fd_shm == -1)
    {
        perror("shm error. Unable to open shared memory.\n");
        exit(1);
    }

    sh_ptr = mmap(NULL, sizeof(struct Market), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (sh_ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    printf("Shared memory accessed.\n");

    
    alarm(1);   // Alarm() then sets the timer to send a SIGALRM after n seconds
    while(1){} // Wait forever >:-)
}