#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/tty.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Seu Nome");
MODULE_DESCRIPTION("Driver de teclado");
MODULE_VERSION("0.1");

static ssize_t keyboard_driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    char c;
    struct tty_struct *tty;

    tty = get_current_tty();
    if (tty == NULL)
        return -ENODEV;

    //c = get_tty_driver(tty)->ops->read(tty, &c, 1);
    if (c == -1)
        return -EIO;

    if (put_user(c, buf) != 0)
        return -EFAULT;

    return 1;
}

static int keyboard_driver_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int keyboard_driver_release(struct inode *inode, struct file *file)
{
    return 0;
}

static loff_t keyboard_driver_llseek(struct file *file, loff_t offset, int whence)
{
    return 0;
}

static const struct file_operations keyboard_driver_fops = {
    .owner = THIS_MODULE,
    .read = keyboard_driver_read,
    .open = keyboard_driver_open,
    .release = keyboard_driver_release,
    .llseek = keyboard_driver_llseek,
};

static int __init keyboard_driver_init(void)
{
    // Registra o driver
    if (register_chrdev(0, "keyboard_driver", &keyboard_driver_fops) < 0) {
        printk(KERN_ALERT "Falha ao registrar o driver de teclado\n");
        return -1;
    }

    printk(KERN_INFO "Driver de teclado registrado\n");
    return 0;
}

static void __exit keyboard_driver_exit(void){

    printk(KERN_INFO "Driver de teclado encerrado\n");

}

module_init(keyboard_driver_init);
module_exit(keyboard_driver_exit);