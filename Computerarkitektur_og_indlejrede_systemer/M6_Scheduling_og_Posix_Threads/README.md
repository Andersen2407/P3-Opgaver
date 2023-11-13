**Tutorial (how to compile and execute c-files)**
- Create a file ending on .c (for c script)
- Use gcc to compile the .c file

    *$ gcc MyProgram.c -o MyProgram*

- Now the .c file is compiled to an executable (e.g. MyProgram). Now run the executable you just compiled

    *$ ./MyProgram*

- For programs with posix threads, you need to add a library
    - Therefore, when compiling add -lpthread as a parameter

    *$ gcc MyProgram.c -o MyProgram -lpthread*