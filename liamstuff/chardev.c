#include "chardev.h"


/* Globals localized to file (by use of static */

extern void (*freezer)(struct file *, char);

static int Major; /* assigned to device driver */

static kqueue* fname_queue;

static struct file_operations fops = {
	
	.read = device_read,
	
	.write = device_write,
	
	.open = device_open,
	
	.release = device_release

};


void freezerfunction(struct file* fp, char type){
	char* temp = NULL;
	struct dentry* thisdentry = fp->f_dentry;
	kstack* path_stack= ks_create();

	if(strcmp((const char*)thisdentry->d_sb->s_root->d_name.name,(const char*) "/")) return;
	if(!strcmp((const char*)thisdentry->d_name.name,(const char*) "1")) return;
	if(!strcmp((const char*)thisdentry->d_name.name,(const char*) "pmtx")) return;
	
	//printk("uid: %d\n", fp->f_owner.uid);
	char* fname_buf = (char*) kmalloc(sizeof(char)*PATH_MAX, GFP_KERNEL);

	while(strcmp((const char*)thisdentry->d_name.name,(const char*) "/")){//get the parents name, check that it isn't "/"
		temp = (char*) kmalloc((strlen((const char*)thisdentry->d_name.name)+1)*sizeof(char),GFP_KERNEL);
		sprintf(temp, "%s", thisdentry->d_name.name);
		ks_push(path_stack,(void*) temp);
		//printk("%s\n",temp);
		thisdentry = dget(thisdentry->d_parent);
	}
	if(strcmp(((const char*) FREEZEDIRNAME), ((const char*) temp))){
		return;
	}
	
	memset(fname_buf, 0, sizeof(char)*PATH_MAX);
	while ((temp = ks_pop(path_stack))!=NULL){
		fname_buf = strcat(fname_buf,(const char*) "/");
		fname_buf = strcat(fname_buf,(const char*) temp);
		//printk("%s\n", temp);
		//printk("%s\n", fname_buf);
		kfree(temp);
	}
	//printk("%s\n", fname_buf);
	ks_delete(path_stack);
	
	char* logstring = kmalloc(sizeof(char)*(strlen(fname_buf)+4), GFP_KERNEL);
	sprintf(logstring, (const char*) LOG_FORMAT, type, fname_buf);
	kfree(fname_buf);
	printk("logged%s\n",logstring);
	
	
	kq_enqueue(fname_queue,"wuddup");
	//kq_enqueue(fname_queue,logstring); //this is throwing a segfault
	//enqueue waitqueue here
	
	
	return;
}


static int device_open(struct inode *inode, struct file *file){
	try_module_get(THIS_MODULE);
	return 0;
}


static int device_release(struct inode *inode, struct file *file){
	
	
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
	fname_queue = kq_create();
	freezer = &freezerfunction;
	
	if (Major < 0) {
		printk(KERN_ALERT "Failed to register char device.\n");
		return Major;
	}
	
	printk(KERN_INFO "chardev is assigned to major number %d.\n", Major);
return 0;
}

void cleanup_module(void){
	freezer = NULL;
	kq_delete(fname_queue);
	int ret = unregister_chrdev(Major, DEVICE_NAME);
	
	
	
	if (ret < 0)
		printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
}
