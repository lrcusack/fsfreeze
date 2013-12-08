/**
 * This creates a character device for communication between the 
 * 		kernel and userspace
 */

#include "chardev.h"
#include <linux/module.h>
/*#define MODULE
#define _KERNEL_
#define	EXPORT_SYMTAB*/
/* Globals localized to file (by use of static */
static int Major;		/* assigned to device driver */
static char msg[BUF_LEN];	/* a stored message */
wait_queue_head_t wq;
int condition = 0;
extern void (*freezer)(struct file *);
//EXPORT_SYMBOL(freezer);

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int device_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);

	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	return 0;
}

/* Called when a process writes to dev file: echo "hi" > /dev/hello */
static ssize_t device_write(struct file *filp, const char *buff,
			    size_t len, loff_t * off)
{
	int copy_len = len > BUF_LEN ? BUF_LEN : len;
	unsigned long amnt_copied = 0;
	printk("***** i'm allup innat device write, yup yup \n");
	/* NOTE: copy_from_user returns the amount of bytes _not_ copied */
	amnt_copied = copy_from_user(msg, buff, copy_len);
	if (copy_len == amnt_copied)
		return -EINVAL;
		
	// wake up processes on the wait_queue after the userspace
	// helper has finished reading the information from
	// the chardev and made a clean copy of the file being
	// modified
	condition = 1;
	// incompatible argument
	// wake_up_interruptible(wait_queue);
	//printk("***** process has been woken up on wait_queue \n");
	return copy_len - amnt_copied;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t len,
			   loff_t * offset)
{
	
	unsigned long amnt_copied;
	int amnt_left = BUF_LEN - *offset;
	char *copy_position = msg + *offset;
	int copy_len = len > amnt_left ? amnt_left : len;
	printk("***** device_read is in biniss \n");
	/* are we at the end of the buffer? */
	if (amnt_left <= 0)
		return 0;

	/* NOTE: copy_to_user returns the amount of bytes _not_ copied */
	amnt_copied = copy_to_user(buffer, copy_position, copy_len);
	if (copy_len == amnt_copied)
		return -EINVAL;

	/* adjust the offset for this process */
	*offset += copy_len;

	return copy_len - amnt_copied;
}

// 
void freezerfct(struct file* f){
	// add the process calling sys_write to the wait_queue
	// when freezerfct is called and condition = 0
	printk("made it into the freezerfct \n");
	printk("*****a process has been added to the wait_queue \n");
	//wait_event_interruptible(wait_queue, condition != 1);
	//printk("*****process woken up, wake_up call not required \n");
	
	
	
	
	return;
}

int init_module(void)
{
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	
	// initialize the wait_queue, print statement for debugging
	//incompatible argument
	init_waitqueue_head(&wq);
	printk("*****wait_queue has been initialized \n");
	printk("***** device all initialized n wutevuh \n");
	if (Major < 0) {
		printk(KERN_ALERT "Failed to register char device.\n");
		return Major;
	}

	memset(msg, '+', BUF_LEN);
	printk(KERN_INFO "chardev is assigned to major number %d.\n",
	       Major);
	       
	freezer = &freezerfct;

	return 0;
}
void cleanup_module(void)
{
	int ret = unregister_chrdev(Major, DEVICE_NAME);
	if (ret < 0)
		printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
	return;
}
MODULE_LICENSE("GPL");
