#include "chardev.h"


/* Globals localized to file (by use of static */

extern void (*freezer)(struct file *, char);

static int Major; /* assigned to device driver */

kqueue* fname_queue;

static struct file_operations fops = {
	
	.read = device_read,
	
	.write = device_write,
	
	.open = device_open,
	
	.release = device_release

};


void freezerfunction(struct file* fp, char type){
	struct dentry* thisdentry = fp->f_dentry;
	char fname[PATH_MAX];
	char* temp;
	char* logstring;
	
	kstack* path_stack = ks_create();
	ks_push(path_stack, (void*) thisdentry->d_name.name);
	printk("%s\n",thisdentry->d_name.name);
	
	while(strcmp(thisdentry->d_parent->d_name.name,"/")){
		ks_push(path_stack,(void*) thisdentry->d_parent->d_name.name);
		printk("%s\n", thisdentry->d_parent->d_name.name);
		thisdentry = thisdentry->d_parent;
	}
	
	printk("%s %s\n", FREEZEDIR, thisdentry->d_name.name);
	if(!strcmp(FREEZEDIR, thisdentry->d_name.name)){
		printk("parsing filename\n"); 
		
		while ((temp = ks_pop(path_stack))!=NULL){
			strcat(fname,temp);
			printk("%s\n", fname);
			kfree(temp);
		}
		ks_delete(path_stack);
		
		logstring = kmalloc(sizeof(char)*(strlen(fname)+4), GFP_KERNEL);
		sprintf(logstring, LOG_FORMAT, type, fname);
		kq_enqueue(fname_queue,logstring);
		//enqueue waitqueue here
	}
	
	return;
}


static int device_open(struct inode *inode, struct file *file){
	fname_queue = kq_create();
	try_module_get(THIS_MODULE);
	return 0;
}


static int device_release(struct inode *inode, struct file *file){
	kq_delete(fname_queue);
	
	module_put(THIS_MODULE);
	return 0;
}


static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off){
	//dequeue from waitqueue
	
    return 1;
}


//dequeue from the list, return to user
static ssize_t device_read(struct file *filp, char *buffer, size_t len, loff_t * offset){
	
    	char* new_string;
    	new_string = kq_dequeue(fname_queue);

    	if(new_string ==NULL){
    		return 0;
    	}  	
    	sprintf(buffer,"%s",new_string);
    	kfree(new_string);

    	return strlen(new_string);
}


int init_module(void){

	Major = register_chrdev(0, DEVICE_NAME, &fops);
	
	freezer = &freezerfunction;
	
	if (Major < 0) {
		printk(KERN_ALERT "Failed to register char device.\n");
		return Major;
	}
	
	printk(KERN_INFO "chardev is assigned to major number %d.\n", Major);
return 0;
}

void cleanup_module(void){
	int ret = unregister_chrdev(Major, DEVICE_NAME);

	if (ret < 0)
		printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
}
