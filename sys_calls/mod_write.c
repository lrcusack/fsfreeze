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
#include <linux/modversions.h>
#include <sys/syscall.h> 

#include "../headers/project.h"

extern void *sys_call_table[]; //make sys call table that the kernel can populate

asmlinkage int (*orig_write)(const char *, int, int); //ptr to original call


asmlinkage int 
mod_sys_write(const char *filename, int flags, int mode)
{
	//if filename is in path, do the following
	{	
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
	}
	
	return orig_write(filename, flags, mode); //complete the original operation
}

int init_module()
{
  
  orig_write = sys_call_table[__NR_write];
  sys_call_table[__NR_write] = mod_sys_write;
  
  return 0;
}

void cleanup_module()
{

  sys_call_table[__NR_write] = orig_write;
}  
