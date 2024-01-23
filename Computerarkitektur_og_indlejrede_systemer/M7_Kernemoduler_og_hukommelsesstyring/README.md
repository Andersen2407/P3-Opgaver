**Exercises:** 
  1. Write a program in C that uses malloc() to allocate some memory
     `$ ./M7/Memory` - Go into directory
  
      - Attempt to vary the amount of memory that you allocate throughout the questions  
        `AllocateMemory.c`- Allocates increasingly large amounts of bytes.  
          
      - You can use e.g. pmap PID to analyze memory usage (Linux)  
        Use `$ top` to find PID of process  
         ![PID_Analyzes](https://github.com/Andersen2407/P3-Opgaver/assets/112859566/13ae3c75-3479-4ef9-9436-4c9bb995f033)
        Using `$ pmap -X [PID]` to find the memory map  
        ![PID_Analyzes2](https://github.com/Andersen2407/P3-Opgaver/assets/112859566/7fd13128-6892-4d25-8b91-cad0e377276c)

        Here we can see that most of the memory used is heap, which is what malloc() uses. Stack is also used for our few intial variables

      - What happens if you attempt to access free’d memory?  
        `AccessMemory.c` - Attempts to acess free'd memory  
        Outputs (seperated by comma): 0 , 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 0, 0, 1949679632, 22024, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38.  
        We get access to previously free’d memory. Note that it is not safe to access free’d data and could fail. When memory is deallocated the memory will be overwritten over time, as can be seen with 0, 1949679632, 22024, values.  
   
      - If you use flags `-x`, `-X` and `–XX` with pmap pid, what additional information can you get?  
        - `-x`, shows the extended format `$ pmap` e.g. the amount of bytes.  
        - `-X`, shows even more details than the `-x` option.  
        - `-XX`, shows everything the kernel provides.
      
  2. Previous time you worked with a multithreaded book buy/selling program – now create a Market program (as an independent process) that accepts buying and selling of books.  
     - Create a buyer and seller program that interacts with the market
You may reuse code from previous.

        To run:  
       `cd ../M7/MarketProgram` - Go into directory  
        `$ make` - Run makefile to compile `Market.c`, `Seller.c`, and `Buyer.c`  
        Open three terminals, one to run each c file, run in following order.   
        `$ ./Market`  
        `$ ./Seller`  
        `$ ./Buyer`
        Note: There is a max on the amount of books.  
     
        Additional: (To inspect the shared memory - displays a hexdump of shared memory file)  
        `$ cd /dev/shm`  
        `$ xxd bookstore`  

  3. Make the kernel module Hello world example work  
     source: [https://www.geeksforgeeks.org/linux-kernel-module-programming-hello-world-program/]  

      To run:  
      `$ cd ../M7/HelloKernel` - Go into directory  
      `$ make` - Run makefile to compile  
      `$ sudo insmod KernelModule.ko` - Inserts code into kernel and runs it  
      
      Additional:
     `$ lsmod | grep "Kernel"` - Checks that the module is inserted.  
     `$ modinfo KernelModule.ko` - Program to show information about a Linux Kernel module.  
     `$ dmesg` - Prints out the message buffer of the kernel  
     `$ rmmod KernelModule` - Removes module from kernel.  
     `$ lsmod | grep "Kernel"` - Checks that the module is removed.  

