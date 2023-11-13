/* Each worker randomly adds new books to their own shelves */
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> // Sleep function


#define max_listings 10
struct Book
{
   char title[20];
   int price;
};
struct Book market[max_listings]; // Create an array to store the books
static int marketCounter = 0;


static int bookIDCounter = 0;


pthread_mutex_t lock;
static int start = 0;


// The function to be executed by all threads
void *worker(void *workerid)
{
   while (start == 0)
       ;
   int wid = (int)workerid;
   int money = 100;


   struct Book tBooks[3];
   int tBookCounter = 0;


   for (int i = 0; i < 7; i++)
   {
       sleep(1);
       printf("\n\nT:%d KR=%d | ", wid, money);


       printf("BOOKS=["); // Print out the books of each thread
       for (int i = 0; i < sizeof(tBooks) / sizeof(tBooks[0]); i++)
       {
           printf("<%s> %dkr | ", tBooks[i].title, tBooks[i].price);
       }
       printf("\b\b]");


       // SELL OR BUY BOOK
       int action = rand() % 2;   // rand() generates number 0-650000
       pthread_mutex_lock(&lock); // Acquire the mutix lock


       // Sell book only if has books and market is not full
       if (action == 0 && (tBookCounter > 0) && (marketCounter < max_listings))
       {
           tBookCounter--;
           struct Book b = tBooks[tBookCounter]; // Grab the book to be sold
           printf("\n\tSelling   --> <%s> %dkr", b.title, b.price);
           money += b.price;


           market[marketCounter] = b; // Put the book in the market array
           marketCounter++;           // Market now has 1 more book


           // Remove book from thread's book-array (set the entry to 0 but keep the size of of course)
           memset(&tBooks[tBookCounter], 0, sizeof(struct Book));
       }
       // Buy book only if thread has room for book AND market is not empty AND if has enough money
       if (action == 1 && (tBookCounter < (sizeof(tBooks) / sizeof(tBooks[0]))) && (marketCounter > 0) && (market[marketCounter - 1].price <= money))
       {
           marketCounter--;
           struct Book b = market[marketCounter]; // Grab the book to be bought from the market
           printf("\n\tBuying   --> <%s> %dkr", b.title, b.price);
           money -= b.price;


           tBooks[tBookCounter] = b;
           tBookCounter++;


           memset(&market[marketCounter], 0, sizeof(struct Book));
       }


       // INTRODUCE A NEW BOOK IN THE THREAD (but only at a certain probability)
       int introduceNewBook = rand() % 2;
       int length = sizeof(tBooks) / sizeof(tBooks[0]);
       // Introduce new book if the thread's book array is not full and if less than 10 books have been created
       if (introduceNewBook == 0 && (tBookCounter < length) && (bookIDCounter < 10))
       {
           printf("\n\tAdded new --> ");
           char bookTitle[20];
           sprintf(bookTitle, "Book%d", bookIDCounter); // Assign name to "bookTitle" variable
           bookIDCounter++;


           // Add books to the market
           strcpy(tBooks[tBookCounter].title, bookTitle); // Copying the bookTitle into the struct in the array
           tBooks[tBookCounter].price = (rand() % 40) + 10;
           tBookCounter++;


           printf("<%s> %dkr", tBooks[tBookCounter - 1].title, tBooks[tBookCounter - 1].price);
       }


       pthread_mutex_unlock(&lock); // Release mutex
   }
   pthread_exit(tBooks);
}


int main()
{
   int NUM_THREADS = 2;
   pthread_t threads[NUM_THREADS];
   struct Book **thread_results[NUM_THREADS];


   pthread_mutex_init(&lock, NULL);


   // Seed the random number generator (usually done once in the program)
   srand(time(NULL));


   // Let us create NUM_THREADS threads
   for (int i = 0; i < NUM_THREADS; i++)
   {
       thread_results[i] = malloc(3 * sizeof(struct Book *));
       pthread_create(&threads[i], NULL, worker, (void *)i);
   }
   start = 1;
   // Join each thread and save their results in the thread_results array
   for (int i = 0; i < NUM_THREADS; i++)
   {
       pthread_join(threads[i], (void **)&thread_results[i]);
   }


   printf("\n\nMARKET=["); // Print out the books left in the market
   for (int i = 0; i < sizeof(market) / sizeof(market[0]); i++)
   {
       if (i % 3 == 0)
       {
           printf("\n");
       }
       printf("\t<%s> %dkr | ", market[i].title, market[i].price);
   }
   printf("\b\b]\n\n");


   pthread_exit(NULL);
   return 0;
}
