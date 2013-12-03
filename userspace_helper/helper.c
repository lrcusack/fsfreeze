/**
 * Userspace Helper
 * 
 * This is the code to implement the userspace helper that logs and 
 * copies files.
 * 
 * @author Liam Cusack
 * @author Austin Blackman
 * 
 */

#include "helper.h"

int main(){
	helper();
	return 0;
}

void helper(){
	int len = 10;
	char* fname;
	char readbuf[64];
	char namebuf[64];
	char donebuf[64];
	char type;
	
	while(1){
		while(read(fd,readbuf,len)==0){};
		
		//parse buf
		sscanf(buf, LOG_FORMAT, &type, namebuf);
		fname = (char*) malloc( strlen(namebuf) * sizeof(char) );
		sprintf( fname, namebuf);
		
		handle_change( type, fname );
		write(fd, donebuf, len);
	}
	
	return; //NEVAAHHHHHHHH
}

void handle_change(char type, char* file_name){
		
		switch(type)
		case 'C': //Copy
			write_to_log('C',file_name);
			break;
					
		case 'M': //Modify
			write_to_log('M',file_name);
			make_clean_copy('M',file_name);
			break;
		
		case 'D': //Delete
			make_clean_copy('D',file_name);
			break;
}

void write_to_log(char type, char* file_name){
	
			
	f = fopen(LOG_NAME,"a");
			
	if(f == NULL){
		printf("error opening file!\n");
		return;
	}

	fprintf(f, LOG_FORMAT, type, file_name);
	fclose(f);
	return;
}

void make_clean_copy(char type, char* file_name){

	char* output_file = malloc((strlen(RESTOREDIR)+strlen(file_name))*sizeof(char));
	sprintf(output_file,"%s%s",RESTOREDIR, file_name);
	printf(" output file name is: %s \n",output_file);
	
	FILE* copyfile;
	
	copyfile = fopen(output_file,"w");
	if(copyfile == NULL){
		printf("cannot open output file\n");
		return;
	}
	
	FILE* oldfile;
	oldfile = fopen(file_name,"rb");
	if(oldfile == NULL){
		printf("cannot open input file \n");
		return;
	}

	char c;
	while((c = fgetc(oldfile)) != EOF){
		fputc(c,copyfile);
	}
	
	fclose(copyfile);
	fclose(oldfile); 

	return;
}
