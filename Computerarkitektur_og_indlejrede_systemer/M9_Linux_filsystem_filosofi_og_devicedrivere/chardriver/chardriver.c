#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DISK_SIZE 1000000

static char disk[DISK_SIZE];
static int actWrPos = 0;
static int actRdPos = 0;
static int nrBytesWrittenFromStart = 0;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gruppe253");
MODULE_DESCRIPTION("Character device driver for reading, writing, etc.");
MODULE_VERSION("1.0");

static int chardev_open(struct inode *inode, struct file *filp) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int chardev_release(struct inode *inode, struct file *filp) {
    printk(KERN_INFO "Device released\n");
    return 0;
}

static ssize_t chardev_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
    int bytes_to_read = count;

    if (actRdPos + count > DISK_SIZE) {
        bytes_to_read = DISK_SIZE - actRdPos;
    }
    if (copy_to_user(buf, &disk[actRdPos], bytes_to_read) != 0) {
        return -EFAULT;
    }
    actRdPos += bytes_to_read;
    pr_info("CharDriver READ");
    return bytes_to_read;
}

static ssize_t chardev_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos) {
    int bytes_to_write = count;
    if (actWrPos + count > DISK_SIZE) {
        bytes_to_write = DISK_SIZE - actWrPos;
    }
    if (copy_from_user(&disk[actWrPos], buf, bytes_to_write) != 0) {
        return -EFAULT;
    }
    actWrPos += bytes_to_write;
    nrBytesWrittenFromStart += bytes_to_write;
    pr_info("CharDriver WRITE");
    return bytes_to_write;
}

static loff_t chardev_llseek(struct file *filp, loff_t offset, int whence) {
    loff_t newpos;

    switch (whence) {
        case 0: /* SEEK_SET */
            newpos = offset;
            break;
        case 1: /* SEEK_CUR */
            newpos = filp->f_pos + offset;
            break;
        case 2: /* SEEK_END */
            newpos = DISK_SIZE + offset;
            break;
        default: /* Can't happen */
            return -EINVAL;
    }
    if (newpos < 0 || newpos > DISK_SIZE)
        return -EINVAL;
    filp->f_pos = newpos;
    actRdPos = newpos;
    actWrPos = newpos;
    return newpos;
}

static int chardev_reset(void) {
    memset(disk, 0, DISK_SIZE);
    actWrPos = 0;
    actRdPos = 0;
    nrBytesWrittenFromStart = 0;
    return 0;
}

static const struct file_operations chardev_fops = {
    .owner = THIS_MODULE,
    .open = chardev_open,
    .release = chardev_release,
    .read = chardev_read,
    .write = chardev_write,
    .llseek = chardev_llseek,
};

static int major_num;
static struct cdev chardev_cdev;

static int __init chardev_init(void) {
    dev_t dev = 9000;

    if (alloc_chrdev_region(&dev, 0, 1, "char_driver_test") < 0) {
        return -1;
    }

    major_num = MAJOR(dev);
    cdev_init(&chardev_cdev, &chardev_fops);

    if (cdev_add(&chardev_cdev, dev, 1) < 0) {
        unregister_chrdev_region(dev, 1);
        return -1;
    }

    printk(KERN_INFO "Character device driver initialized\n");
    return 0;
}

static void __exit chardev_exit(void) {
    cdev_del(&chardev_cdev);
    unregister_chrdev_region(MKDEV(major_num, 0), 1);
    printk(KERN_INFO "Character device driver exited\n");
}

module_init(chardev_init);
module_exit(chardev_exit);