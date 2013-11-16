/**
 * 
 * This is the code to modify the write system call.
 * 
 * @author Liam Cusack
 * 
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <linux/syscalls.h>

#include "../../headers/project.h"

extern void* sys_call_table[]; //make sys call table that the kernel can populate

asmlinkage int (*orig_write)(int fd, const void* buf, size_t count); //ptr to original call


asmlinkage int  mod_sys_write(int fd, const void* buf, size_t count){
	
	printk("we're in");
	
	//if filename is in path, do the following{	
		
	// write filename and the type of change to a buffer
		//char buffer[64];
		//snprintf(LOG_FORMAT,63,filename,MODIFY);
	//get lock on chardev
		
	//write filename and type to chardev (adds it to a linked list)
		//int chardev = open(CHARDEV_NAME);
		//write(chardev,buf);
		
	//release lock on chardev
		
	//signal userspace helper that it needs to log the file
		
	//wait for signal from userspace
	//}
	
	return orig_write(fd, buf, count); //complete the original operation
}

int init_module(){
  
  orig_write = sys_call_table[__NR_write]; //get pointer to actual write function
  sys_call_table[__NR_write] = mod_sys_write; //put pointer to our new function in sys_call table
  
  return 0;
}

void cleanup_module(){
  sys_call_table[__NR_write] = orig_write;
}  
