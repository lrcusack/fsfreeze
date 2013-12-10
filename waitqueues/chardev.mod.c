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
	{ 0xdd8818e1, "struct_module" },
	{ 0x2a7b11d4, "finish_wait" },
	{ 0x4292364c, "schedule" },
	{ 0x7d1ed1f2, "prepare_to_wait" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x1d26aa98, "sprintf" },
	{ 0x37a0cba, "kfree" },
	{ 0x6cb34e5, "init_waitqueue_head" },
	{ 0x8523fd53, "kmem_cache_alloc" },
	{ 0xb13d73c9, "malloc_sizes" },
	{ 0xb468ccf9, "register_chrdev" },
	{ 0xc281c899, "__wake_up" },
	{ 0xf2a644fb, "copy_from_user" },
	{ 0x7e691aed, "wake_up_process" },
	{ 0x1b7d4074, "printk" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x474b7b16, "freezer" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E073E27C469BB8AF1C37F2B");
