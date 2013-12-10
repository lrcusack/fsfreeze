#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0xb499ef18, "struct_module" },
	{ 0x865edc9b, "finish_wait" },
	{ 0x4292364c, "schedule" },
	{ 0xc8f02aeb, "prepare_to_wait" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x19cacd0, "init_waitqueue_head" },
	{ 0x19070091, "kmem_cache_alloc" },
	{ 0xab978df6, "malloc_sizes" },
	{ 0x1e8e5fac, "register_chrdev" },
	{ 0x1d26aa98, "sprintf" },
	{ 0x37a0cba, "kfree" },
	{ 0x59968f3c, "__wake_up" },
	{ 0xf2a644fb, "copy_from_user" },
	{ 0xdcef6636, "wake_up_process" },
	{ 0x1b7d4074, "printk" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x5640e49e, "freezer" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "45B6338BE86DCAA12F58C0E");
