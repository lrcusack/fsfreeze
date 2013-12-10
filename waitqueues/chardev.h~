#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/dcache.h>
#include <linux/string.h>

#include "../headers/klist.h"
#include "../headers/kstack.h"
#include "../headers/project.h"
/* Function Prototypes */
/* TODO: Add comments for each prototype */
int init_module(void); 
void freezerfct(struct file*, char);
void cleanup_module(void);
static int device_open(struct inode *, struct file *); 
static int device_release(struct inode *, struct file *); 
static ssize_t device_read(struct file *, char *, size_t, loff_t *); 
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
//EXPORT_SYMBOL(freezerfct);
#define DEVICE_NAME "chardev" /* entry in /proc/devices */	
#define BUF_LEN (80)

