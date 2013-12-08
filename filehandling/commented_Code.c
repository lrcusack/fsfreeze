
	

/* in read_write.c
	
	//printk("filp->f_dentry->d_name.name %s\n", filp->f_dentry->d_name.name);
	//printk("filp->f_dentry->d_parent->d_name.name %s\n", filp->f_dentry->d_parent->d_name.name);
	//printk("filp->f_dentry->d_parent->d_parent->d_name.name %s\n", filp->f_dentry->d_parent->d_parent->d_name.name);
#include "/root/fsfreeze/headers/project.h"
#include "/root/fsfreeze/headers/kstack.h"
	
//in sys_write	
	if(freezerfct != NULL){
		//code for determining if it is in the path
		
		struct dentry current = [file pointer]->f_dentry;
		char fname[PATH_MAX];
		char* dirname;
		char type = 'M';
		kstack* path_stack = ks_create();
		ks_push(path_stack, current->d_name.name);
		printk("%s\n",current->d_name.name);
		while(strcmp(current->d_parent->d_name.name,"/")){
			ks_push(path_stack, current->d_parent->d_name.name);
			printk("%s\n", current->d_parent->d_name.name);
			current = current->d_parent;
		}
		printk("%s %s\n", FREEZEDIR, current->d_name.name);
		if(!strcmp(FREEZEDIR, current->d_name.name)){
			printk("parsing filename\n"); 
			while ((temp = ks_pop(path_stack))!=NULL){
				strcat(fname,temp);
				printk("%s\n", fname);
				kfree(temp);
			}
			ks_delete(path_stack);
			//freezerfct(type, fname);
		}
	}
*/
