/**
 * This creates a character device for communication between the 
 * 		kernel and userspace
 */

#include "chardev.h"
#include "../headers/klist.h"
/* Globals localized to file (by use of static */
static int Major;		/* assigned to device driver */
static char msg[BUF_LEN];	/* a stored message */
//extern void (*freezerfct)(struct file *);

kqueue* filenames;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int device_open(struct inode *inode, struct file *file)
{
	printf(KERN_WARNING "trying to printk something\n");
	try_module_get(THIS_MODULE);
	printk(KERN_DEBUG "trying to create klist\n");
	filenames = kq_create();
	printk(KERN_DEBUG "created klist\n");
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	printk("trying to delete klist\n");
	kq_delete(filenames);
	printk("deleted klist\n");
	return 0;
}

/* Called when a process writes to dev file: echo "hi" > /dev/hello */
static ssize_t device_write(struct file *filp, const char *buff,
			    size_t len, loff_t * off)
{
	int copy_len = len > BUF_LEN ? BUF_LEN : len;
	unsigned long amnt_copied = 0;

	/* NOTE: copy_from_user returns the amount of bytes _not_ copied */
	amnt_copied = copy_from_user(msg, buff, copy_len);
	if (copy_len == amnt_copied)
		return -EINVAL;

	return copy_len - amnt_copied;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t len,
			   loff_t * offset)
{

	
	return 0;
	
	/*our read code
	char* fname = kq_dequeue(filenames);
	if(fname==NULL) return 0;
	sprintf(buffer, "%s", fname);
	return strlen(buffer);
	*/
	
	/* actual read
	
	unsigned long amnt_copied;
	int amnt_left = BUF_LEN - *offset;
	char *copy_position = msg + *offset;
	int copy_len = len > amnt_left ? amnt_left : len;

	//are we at the end of the buffer?
	if (amnt_left <= 0)
		return 0;

	// NOTE: copy_to_user returns the amount of bytes _not_ copied
	amnt_copied = copy_to_user(buffer, copy_position, copy_len);
	if (copy_len == amnt_copied)
		return -EINVAL;

	// adjust the offset for this process
	*offset += copy_len;

	return copy_len - amnt_copied;
	*/
	
}

/*
void freezerfunct(struct file* f){
	
	//printk("filp->f_dentry->d_name.name %s\n", filp->f_dentry->d_name.name);
	//printk("filp->f_dentry->d_parent->d_name.name %s\n", filp->f_dentry->d_parent->d_name.name);
	//printk("filp->f_dentry->d_parent->d_parent->d_name.name %s\n", filp->f_dentry->d_parent->d_parent->d_name.name);
	
	//code for determining if it is in the path
	
	struct dentry current = filp->f_dentry;
	char fname[PATH_MAX];
	char type = 'M';
	while(strcmp(current->d_parent->d_name.name)){
		//push current->d_parent->d_name.name onto a stack
		current = current->d_parent;
	}
	//put stack into fname variable
	if(!strcmp(FREEZEDIR, current->d_name.name)){
		freezerfct(type, fname);
	}	
	
	
	
	
	
	return;
}
*/

int init_module(void)
{
	Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
		printk(KERN_ALERT "Failed to register char device.\n");
		return Major;
	}

	memset(msg, '+', BUF_LEN);
	printk(KERN_INFO "chardev is assigned to major number %d.\n",
	       Major);
	       
	//freezerfct = &freezerfunct;

	return 0;
}
void cleanup_module(void)
{
	int ret = unregister_chrdev(Major, DEVICE_NAME);
	if (ret < 0)
		printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
	return;
}
