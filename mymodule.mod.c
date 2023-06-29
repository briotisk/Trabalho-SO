#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x32e21920, "module_layout" },
	{ 0x3696b2c2, "input_unregister_device" },
	{ 0x9ed554b3, "unregister_keyboard_notifier" },
	{ 0x4db09b27, "kernel_accept" },
	{ 0xaa4cf7b, "kernel_listen" },
	{ 0x3d3fe492, "kernel_bind" },
	{ 0x484f0e16, "sock_create_kern" },
	{ 0xb014a89f, "init_net" },
	{ 0xf35141b2, "kmem_cache_alloc_trace" },
	{ 0x26087692, "kmalloc_caches" },
	{ 0x1b6314fd, "in_aton" },
	{ 0x96554810, "register_keyboard_notifier" },
	{ 0x35b2d065, "input_free_device" },
	{ 0xb668d3fc, "input_register_device" },
	{ 0x710c51f5, "input_allocate_device" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x8cddb2a, "kernel_sendmsg" },
	{ 0x659ed02c, "input_event" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xe2c7e7f, "sock_release" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "980899A46257095E9DC5B27");
