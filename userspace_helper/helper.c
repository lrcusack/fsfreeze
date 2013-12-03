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


//#define TEST

int main(){
#ifdef TEST	
	testerfct();
#else
	helper();
#endif
	return 0;
}

void helper(){

	char* fname;
	char readbuf[BUFLEN];
	char namebuf[BUFLEN];
	char donebuf[BUFLEN];
	sprintf(donebuf, "jobsdone");
	char type;
	int fd = open(CHARDEV_NAME, O_RDWR);
	
	while(1){
		while(read(fd,readbuf,BUFLEN)==0){
			//printf("waiting\n");
		};
		
		//parse buf
		sscanf(readbuf, LOG_FORMAT, &type, namebuf);
		fname = (char*) malloc( strlen(namebuf) * sizeof(char) );
		sprintf( fname, namebuf);
		
		handle_change( type, fname );
		write(fd, donebuf, BUFLEN);
	}
	
	return; //NEVAAHHHHHHHH
}

void handle_change(char type, char* file_name){
		
		switch(type){
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
}

void write_to_log(char type, char* file_name){
	
			
	FILE* f = fopen(LOG_NAME,"a");
			
	if(f == NULL){
		printf("error opening file!\n");
		fclose(f);
		return;
	}
	
	fprintf(f, LOG_FORMAT, type, file_name);
	fprintf(f, "\n");
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
		fclose(copyfile);
		return;
	}
	
	FILE* oldfile;
	oldfile = fopen(file_name,"rb");
	if(oldfile == NULL){
		printf("cannot open input file \n");
		fclose(copyfile);
		fclose(oldfile);
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

void testerfct(){
	
	/* //Test reading log formatted string; all checked out
	char type;
	char* fname;
	char namebuf[BUFLEN];
	char readbuf[BUFLEN];
	sprintf(readbuf, "C sample.txt");
	
	sscanf(readbuf, LOG_FORMAT, &type, namebuf);
	fname = (char*) malloc( strlen(namebuf) * sizeof(char) );
	sprintf( fname, namebuf);
	
	printf("%s\n",fname);
	printf("%c\n",type);
	*/
	
	/* //Test handle_change, write_to_log, and make_clean_copy; all checked out
	handle_change('C', "sample.txt");
	handle_change('M', "sample.txt");
	handle_change('D', "sample.txt");
	*/
	
	return;
	
}
