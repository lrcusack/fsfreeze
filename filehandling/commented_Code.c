
	

/* in read_write.c
	
	//printk("filp->f_dentry->d_name.name %s\n", filp->f_dentry->d_name.name);
	//printk("filp->f_dentry->d_parent->d_name.name %s\n", filp->f_dentry->d_parent->d_name.name);
	//printk("filp->f_dentry->d_parent->d_parent->d_name.name %s\n", filp->f_dentry->d_parent->d_parent->d_name.name);
	
	if(freezerfct != NULL){
		//code for determining if it is in the path
		
		struct dentry current = [file pointer]->f_dentry;
		char fname[PATH_MAX];
		char* dirname;
		char type = 'M';
		[kernel stack type name]* path_stack = [kernel stack create]();
		while(strcmp(current->d_parent->d_name.name,"/")){
			[kernel stack push](path_stack, current->d_parent->d_name.name);
			current = current->d_parent;
		}
		if(!strcmp(FREEZEDIR, current->d_name.name)){
			while ((temp = [kernel stack pop](path_stack))!=NULL){
				strcat(fname,temp);
				kfree(temp);
			}
			[kernel stack delete](path_stack);
			freezerfct(type, fname);
		}
	}
*/
