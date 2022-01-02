#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

struct proc_dir_entry* proc_entry = NULL;
int MaxBuffer = 64;

static int sopen(struct inode *inode, struct file *file) {
   	printk(KERN_ALERT "Device opened\n");
   	return 0;
}

static int srelease(struct inode *inode, struct file *file) {
    printk(KERN_ALERT "All device's closed\n");
    return 0;
}

static ssize_t sread(struct file *file, char __user *ubuf, size_t size, loff_t *offset) {
    char message[128];

    strcpy(message, "Welcome to this kernel pwn series");

    if (raw_copy_to_user(ubuf, message, size) != 0) {
        return -EFAULT;
    }

    printk(KERN_ALERT "%ld bytes read from device\n", size);
    return size;
}

static ssize_t swrite(struct file *file, const char __user *ubuf, size_t size, loff_t *offset) {
    char buffer[128];

    if (size > MaxBuffer) {
        printk(KERN_ALERT "Your chosen size is too large\n");
        return -EFAULT;
    }

    if (raw_copy_from_user(buffer, ubuf, size) != 0) {
        return -EFAULT;
    }

    printk(KERN_ALERT "%ld bytes written to device\n", size);
    return size;
}

static long sioctl (struct file *file, unsigned int cmd, unsigned long arg) {
    printk(KERN_ALERT "IOCTL Called\n");
    switch(cmd) {
        case 0x10:
            printk(KERN_ALERT "You passed in: %lx\n", arg);
            break;
        case 0x20:
            MaxBuffer = arg;
            break;
        default:
            printk(KERN_ALERT "Not a valid command\n");
    }
    return 0;
}

static const struct file_operations fops = {
    .owner          = THIS_MODULE,
    .open           = sopen,
    .read           = sread,
    .write          = swrite,
    .release        = srelease,
    .unlocked_ioctl = sioctl
};

static int __init init_func(void) {
    proc_entry = proc_create("pwn_device", 0666, NULL, &fops);
    printk(KERN_ALERT "Module successfuly initialized\n");
    return 0;
}

static void __exit exit_func(void) {
    if (proc_entry) {
        proc_remove(proc_entry);
    }
    printk(KERN_ALERT "Module successfuly unloaded\n");
}

MODULE_LICENSE("GPL v2");
module_init(init_func);
module_exit(exit_func);
