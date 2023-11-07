Exercises:  
  1. Based on your previous buying and selling book code - create a signal alarm that triggers the buying of a book every 5 second, 
and the selling of a book every 10 second.  
    - It is free of choice if you wish to do this with your thread or process based code. (We are using process based)  
    - Add code that when pressing ctrl-c, you ensure a proper shutdown of all threads and memory you have used.  
     
  `$ cd /M8/signal_market` - Go into the directory  
  `$ make` - to compile all files  
  Open three terminals, one to run each c file, run in following order.  
  `$ ./Market`  
  `$ ./SignalSeller`  
  `$ ./SignalBuyer`   
  Note: Market can max have 10 books at any time.  

  3. Write the guessing game in rust  
    - Write code in C which does the same thing  
    - Try out both type of code – what are the differences (if any)?  

   `cd /M8/guessing_game` - for Rust code  
   `cd /M8` - For C code  
   
