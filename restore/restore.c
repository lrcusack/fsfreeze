/**
 * tool to restore frozen directory to freeze point
 * 
 * @author Liam Cusack
 * 
 */


#include "restore.h"

int main(){
	restore(FREEZEDIR,RESTOREDIR,LOG_NAME,DELIM);
	return 0;
}

void restore(char* dest, char* source, char* logfile, char delim){
	llqueue* ll = parse_log_file(logfile,delim);
	delete_files(ll);
	copy_files(dest,source);	
	return;
}

void copy_files(char* dest, char* source){
	//copy all files from source directory to dest directory
	
	
	
	return;
}

void delete_files(llqueue* files){
	char* fname = NULL;
	while(ll_dequeue(files, (void**) &fname)){
		//delete file with name fname
		//printf("%s\n", fname);
	}
	
	
	return;
}
	
llqueue* parse_log_file(char* fname, char delim){

	char namebuf[BUFLEN];
	char* new_fname;

	llqueue* ll = ll_create();
	FILE* logfile = fopen(fname, "r");
	if(logfile == NULL){
		printf("could not open log file\n");
		fclose(logfile);
		return ll;
	}

	while(EOF != fscanf(logfile, "%s", namebuf)){
		new_fname = (char*) malloc(sizeof(char) * strlen(namebuf));
		strcpy(new_fname, namebuf);
		//printf("%s\n", new_fname);
		ll_enqueue(ll, new_fname);
	}
	fclose(logfile);

	return ll;
}
