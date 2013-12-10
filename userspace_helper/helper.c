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
	char donebuf[2];
	llqueue* changelist;
	sprintf(donebuf, "X");
	char type;
	int fd = open(CHARDEV_NAME, O_RDWR);
	
	changelist = ll_create();
	while(1){
		while(read(fd,readbuf,BUFLEN)==0){
			//printf("waiting\n");
		}
		 //parse buf
		 //printf("did a read\n");
		if(!isInList(&changelist, readbuf)){
			sscanf(readbuf, LOG_FORMAT, &type, namebuf);
			printf("%c %s\n", type, namebuf);
			fname = (char*) malloc( strlen(namebuf) * sizeof(char) );
			sprintf( fname, namebuf);
			printf("handling change: %c for file: %s\n", type, fname);
			handle_change( type, fname );
		}
		write(fd, donebuf, BUFLEN);
		
	}
	ll_delete(changelist);
	
	return; //NEVAAHHHHHHHH
}

int isInList(llqueue** fnames_addr, char* newname){
	
	llqueue* fnames = *fnames_addr;
	int found = 0;
	llqueue* temp = ll_create();
	char* thisname;
	
	while(ll_isnonempty(fnames)){
		thisname = ll_dequeue(fnames);
		if(!strcmp(thisname,newname)){
			found=1;
		}
		ll_enqueue(temp, thisname);
	}
	*fnames_addr = temp;
	
	return found;
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
	
	fprintf(f, "%s\n", file_name);
	fclose(f);
	return;
}

void make_clean_copy(char type, char* file_name){

	char* output_file = malloc((strlen(RESTOREDIR)+strlen(file_name))*sizeof(char));
	
	sprintf(output_file,"%s%s",RESTOREDIR, (file_name+strlen(FREEZEDIR)));
	
	FILE* copyfile;
	
	copyfile = fopen(output_file,"w");
	if(copyfile == NULL){
		printf("cannot open output file\n");
		fclose(copyfile);
		return;
	}
	
	FILE* oldfile;
	oldfile = fopen(file_name,"r");
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
	
	
	 //Test handle_change, write_to_log, and make_clean_copy; all checked out
	handle_change('C', "sample.txt");
	handle_change('M', "sample.txt");
	handle_change('D', "sample.txt");
	*/
	
	return;
	
}
