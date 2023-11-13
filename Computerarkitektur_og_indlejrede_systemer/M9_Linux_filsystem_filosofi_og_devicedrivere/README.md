# M9 Linux filsystem

## 4.5 Passing Command Line Arguments to a Module
> **NOTE**: Commands are explained in more detail in **M7!** (along with additional kernel module commands)

```
$ make
    # Compile program
$ sudo insmod KernelModule.ko myshort=1234
    # Insert kernel module with parameter myshort set to 1234
$ sudo dmesg -t | tail -7
    # See the logs for kernelmodules (-t: without timestamps) (tail: see only last 7 lines of logs)
$ sudo modinfo KernelModule.ko
    # Display module info.
$ sudo rmmod KernelModule.ko
    # Optional, remove module
```



## Jens's udfordring (chardriver)
[Udfordringen](https://www.moodle.aau.dk/mod/page/view.php?id=1644554)

**Lav en char devicedriver der understøtter**:
1. open
2. close
3. read, 
4. write 
5. seek, 
6. reset(? slette alt indhold og sætte str mm til  0)

Funktionalitet: ram disk eller storage som er hurtigt.

#### Solution
Provided by OpenAllah-GPT v3.5 (inshallah turbo)
![idk](https://media.tenor.com/1YaOiH6FJv8AAAAd/creative-alah.gif)


[Følger dette tutorial om char device drivers](https://www.moodle.aau.dk/mod/page/view.php?id=1598404)


```
$ cd chardriver/                    # Gå ind i mappen
$ make                              # Compile
$ sudo insmod chardriver.ko         # Insert kernel module into Linux kernel
$ modinfo chardriver.ko             # Show module info
$ cat /proc/devices                 # List devices' and their MAJOR number (remember the number for our module 'char_driver_test')
$ sudo mknod /dev/test_driver c 240 0   # Make character special files (for our driver whose major number is 240, noted from previous command, and minor is 0)
            # sudo mknod [PATH where the driver is created] [c/b for char or block driver] [MAJOR number] [MINOR number]
$ sudo chmod 777 /dev/test_driver   # Set permission bits to allow all, meaning everyone can read/write from it
$ echo 1 > test_driver              # Write "1" to the driver
$ cat test_driver                   # Read from the driver
$ sudo dmesg | tail -7              # Read logs from Linux kernel modules (only the last 7)
```

