#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


#define NUM_THREADS 5
struct Book
{
char title[50];
int price;
};


static int *wallet_per_thread[NUM_THREADS];


const int market_opened_for = 30; // in seconds
int book_label = 0;


const int max_listings = 10;
int market_size = 0;
struct Book market[max_listings]; // Create an array to store the books


const int warehouse_capacity = 5;
int warehouse_size = 0;
struct Book warehouse[warehouse_capacity];


pthread_mutex_t lock;


void *book_supplier(void *supplierid)
{
int total_resources = 15; // 1 resource = 1 book


while (1)
{
int produced_books = (rand() % 7) + 4; // amount of books that can be produced is 1-4 at a time
if(total_resources >= produced_books && (warehouse_size + produced_books) <= warehouse_capacity) {
pthread_mutex_lock(&lock);
char bookTitle[50];
int bookPrice;
for (int i = 0; i < produced_books; i++)
{
sprintf(bookTitle, "book %d", book_label);
bookPrice = (rand() % 50) + 20;


// Deliver book to warehouse
strcpy(warehouse[warehouse_size].title, bookTitle);
warehouse[warehouse_size].price = bookPrice;


book_label++;
warehouse_size++;
total_resources--;


printf("Supplier has produced %s. Warehouse has now %d/%d books in stock. Total resources left: %d\n", bookTitle, warehouse_size, warehouse_capacity, total_resources);
}


pthread_mutex_unlock(&lock);
} else if(warehouse_size >= warehouse_capacity) {
printf("Warehouse capacity is full! Cannot produce any books atm\n.");
}
sleep(1);
}
return NULL;
}


// The function to be executed by all threads
void *worker(void *workerid)
{
long wid = (long)workerid;
int moneyLeft = 100;
struct Book purchaseHistory[max_listings];
int purchasehistory_size = 0;


while (1)
{
int action = rand() % 2;


// Sell a book
if (action == 0)
{
// get lock
pthread_mutex_lock(&lock);
if (market_size <= max_listings) // as long as there is space on the market to sell.
{
if (warehouse_size > 0) { // there is books in the warehouse, as long as size is over 0


// Get book from warehouse - always takes the last book in the warehouses
char bookTitle[50];
strcpy(bookTitle, warehouse[warehouse_size-1].title); // we know when warehouse_size > 0, then a book has been added to the warehouse, but we use the index, not the size (thats why we minus by one, because the index starts from 0)
int bookPrice = warehouse[warehouse_size-1].price;
warehouse_size--;


// listing the book on the market
strcpy(market[market_size].title, bookTitle);
market[market_size].price = bookPrice;
market_size++;


printf("Thread (%ld) is selling %s for $%d\n", wid, market[market_size-1].title, bookPrice);
}
// release the lock
pthread_mutex_unlock(&lock);
}


// release the lock
pthread_mutex_unlock(&lock);
}




// buy a book
else if (action == 1 && market_size > 0)
{
// get lock
pthread_mutex_lock(&lock);
// Check if you have enough money
if (moneyLeft >= market[market_size - 1].price) // minus by 1, since we want to compare with the last book listed on the market (index based)
{
char title[50];
market_size--; // we minus so that market_size becomes index based
moneyLeft = moneyLeft - market[market_size].price;
strcpy(title, market[market_size].title);
int price = market[market_size].price;
// Save the book in the purchase history
strcpy(purchaseHistory[purchasehistory_size].title, title);
purchaseHistory[purchasehistory_size].price = price;


purchasehistory_size++;


printf("Thread (%ld) bought %s for $%d with $%d remaining. Now %d books listed on the market.\n", wid, title, price, moneyLeft, market_size);


wallet_per_thread[wid] = &moneyLeft;
}


// release the lock
pthread_mutex_unlock(&lock);
}


sleep(1);
}


return NULL;
}


int main()
{
pthread_t threads[NUM_THREADS];
pthread_t supplier_thread;


// Seed the random number generator (usually done once in the program)
srand(time(NULL));


// Initialize the mutex
pthread_mutex_init(&lock, NULL);


printf("----------> MARKET HAS OPENED <----------\n");
// Create the book_supplier thread
pthread_create(&supplier_thread, NULL, book_supplier, (void *)1);


// Let us create NUM_THREADS threads
for (long i = 0; i < NUM_THREADS; i++)
pthread_create(&threads[i], NULL, worker, (void *)i);


sleep(market_opened_for);
printf("----------> MARKET HAS CLOSED <----------\n");
for (long i = 0; i < NUM_THREADS; i++) {
printf("Thread (%ld) had $%d left.\n", i, *wallet_per_thread[i]);
}


// Destroy the mutex
pthread_mutex_destroy(&lock);


return 0;
}
