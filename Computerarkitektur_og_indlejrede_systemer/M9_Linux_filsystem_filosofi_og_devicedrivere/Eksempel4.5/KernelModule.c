/**
 * @file	hello.c
 * @author  Jesus
 * @date	10 Sept 0022
 * @version 0.1
 * @bruh_level: 23
 * @brief  An introductory "Hello World!" loadable kernel
 *  module (LKM) that can display a message in the /var/log/kern.log
 *  file when the module is loaded and removed. The module can accept
 *  an argument when it is loaded -- the name, which appears in the
 *  kernel log files.
 */
#include <linux/module.h> 	/* Needed by all modules */
#include <linux/kernel.h> 	/* Needed for KERN_INFO */
#include <linux/moduleparam.h>
#include <linux/init.h>   	/* Needed for the macros */
#include <linux/stat.h>

///< The license type -- this affects runtime behavior
MODULE_LICENSE("GPL");
///< The author -- visible when you use modinfo
MODULE_AUTHOR("Gruppe352");
///< The description -- see modinfo
MODULE_DESCRIPTION("Hello world");
 
///< The version of the module
MODULE_VERSION("2.1");

static short int myshort = 1;
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer tihi"); 


static int __init hello_start(void) {
	printk(KERN_INFO "Loading hello module...\n");
	printk(KERN_INFO "Hello world\n");
	pr_info("hello %i", myshort);
	printk("<myshort> is sat to: %i", myshort);

	return 0;
}
 
static void __exit hello_end(void)
{
	printk(KERN_INFO "Goodbye!\n");
}
 
module_init(hello_start);
module_exit(hello_end);

// sudo dmesg -t | tail -7   # <--- Giga chad