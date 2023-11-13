# M9

### Example 3

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