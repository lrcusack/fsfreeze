#include "chardev.h"


/* Globals localized to file (by use of static */

static int Major; /* assigned to device driver */

static char msg[BUF_LEN]; /* a stored message */

kqueue* test_queue;

static struct file_operations fops = {

.read = device_read,

.write = device_write,

.open = device_open,

.release = device_release

};


static int device_open(struct inode *inode, struct file *file){
	printk("in open\n");
	test_queue = kq_create();
	try_module_get(THIS_MODULE);
	printk("did not seg fault in device_open \n");
	printk("the test_queue pointer is %p \n",test_queue);
	return 0;
}


static int device_release(struct inode *inode, struct file *file)

{
	kq_delete(test_queue);
	
	module_put(THIS_MODULE);

return 0;

}


/* Called when a process writes to dev file: echo "hi" > /dev/hello */

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off){
    	static int enqueue_check;
    	char * new_string;
    	printk("starting to try and enqueue something \n");
    	new_string = (char*)kmalloc(sizeof(char)*strlen(buff),GFP_KERNEL);
    	sprintf(new_string,"%s",buff);
    	enqueue_check = kq_enqueue(test_queue, new_string);
    	printk("got through enqueing something \n");
    	return strlen(new_string);
}

//dequeue from the list, return to user
static ssize_t device_read(struct file *filp, char *buffer, size_t len, loff_t * offset){
	
    	char* new_string;
    	new_string = kq_dequeue(test_queue);
    	printk("starting to try and dequeue something \n");
    	if(new_string ==NULL){
    		return 0;
    	}  	
    	sprintf(buffer,"%s",new_string);
    	kfree(new_string);
    	printk("got through dequeing something \n");
    	return 1;

}


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


return 0;

}

void cleanup_module(void)

{
	int ret = unregister_chrdev(Major, DEVICE_NAME);

	if (ret < 0)
		printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
}
