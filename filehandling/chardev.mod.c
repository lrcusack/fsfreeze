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
	{ 0x89e24b9c, "struct_module" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x1d26aa98, "sprintf" },
	{ 0x19070091, "kmem_cache_alloc" },
	{ 0xab978df6, "malloc_sizes" },
	{ 0x40e4fec5, "wake_up_process" },
	{ 0x37a0cba, "kfree" },
	{ 0x4086729e, "register_chrdev" },
	{ 0x1b7d4074, "printk" },
	{ 0xc192d491, "unregister_chrdev" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C4143C538F162A991333D2A");