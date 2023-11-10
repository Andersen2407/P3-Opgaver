#ifndef MARKET_H
#define MARKET_H

// Shared memory is located at /dev/shm in Linux.
// We define the name of the shared memory.
#define SHARED_MEM_NAME "/bookstore"

struct Book // We must defind a book.
{
    short price;
    char title[8];
};

struct Market
{ 
    // We have a market containing x books.
    struct Book books[10];
    int bookIDtracker;    // Every book has an ID
    int numberOfBooks;  // How many books in the market
};

#endif
