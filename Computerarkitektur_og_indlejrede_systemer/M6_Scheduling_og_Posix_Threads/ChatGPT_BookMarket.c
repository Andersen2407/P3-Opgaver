#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 5  // Number of threads
#define MAX_BOOK_PRICE 100
#define INITIAL_FUNDS 500

pthread_mutex_t market_mutex = PTHREAD_MUTEX_INITIALIZER;
int market_size = 0;
int thread_funds[N];

// Structure to represent a book
typedef struct {
    int id;
    int price;
} Book;

Book market_books[100];

void add_book_to_market(int thread_id) {
    if (market_size < 100) {
        Book new_book;
        new_book.id = market_size + 1; // Assign a unique book ID
        new_book.price = rand() % (MAX_BOOK_PRICE + 1);
        market_books[market_size] = new_book;
        market_size++;
        printf("Thread %d added Book %d to the market for $%d\n", thread_id, new_book.id, new_book.price);
    }
}

int remove_book_from_market(int thread_id) {
    if (market_size > 0) {
        Book sold_book = market_books[market_size - 1];
        market_size--;
        printf("Thread %d bought Book %d from the market for $%d\n", thread_id, sold_book.id, sold_book.price);
        return sold_book.price;
    }
    return -1; // Market is empty
}

void* thread_function(void* thread_id) {
    int id = *(int*)thread_id;
    thread_funds[id] = INITIAL_FUNDS;

    // Seed the random number generator with a unique value for each thread
    srand(time(NULL) + id);

    while (1) {
        int action = rand() % 2; // 0 for put a book, 1 for buy a book

        if (action == 0) {
            pthread_mutex_lock(&market_mutex);
            add_book_to_market(id);
            pthread_mutex_unlock(&market_mutex);
        } else {
            pthread_mutex_lock(&market_mutex);
            int book_price = remove_book_from_market(id);
            pthread_mutex_unlock(&market_mutex);

            if (book_price != -1 && thread_funds[id] >= book_price) {
                thread_funds[id] -= book_price;
            }
        }

        // Sleep for a random time
        usleep((rand() % 500000) + 500000); // Sleep for 0.5 to 1.0 seconds
    }

    return NULL;
}

int main() {
    pthread_t threads[N];
    int thread_ids[N];

    for (int i = 0; i < N; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
