/**
 * tool to restore frozen directory to freeze point
 * 
 * @author Liam Cusack
 * 
 */

#include "../headers/restore.h"

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
	char* fname;
	while(ll_dequeue(ll,fname)){
		//delete file with name fname
	}
	
	
	return;
}
	
llqueue* parse_log_file(char* fname, char delim){
	char* filetext;
	char* new_fname;
	int len;
	llqueue* ll = ll_create();

	read_file(fname, filetext);//get full log file text
	
	while(len = next_token(&filetext, new_fname, delim)){
		ll_enqueue(ll,new_fname); //put new filename in linked list
	}

	free(filetext);//release memory for full file text
	return ll;
}

int next_token(char** text, char* token, char delim){
	int ii;
	int end=0;
	while(){//iterate over text until delimiter or end of file is found
		ii++;
		char current = *(*text+ii);
		if (current == EOF) break;
		if (current == delim) break;
	}
	if(0==ii) return -1;//if it has reached the end of the file or an empty token, return -1

	token=(char*)malloc(ii); //make space for token string plus end of string char.
	snprintf(token, *text, ii-1);//put the token string in the token pointer, do not include delimiter

	*text= *text + ii + 1; //offsets the pointer to the beginning of the text to the beginning of the next token
	return ii; //return length of token
}
	
void read_file(char* fname, char* contents){
	int fd = open(fname, O_RDWR);

	struct stat* data = malloc(sizeof(struct stat));
	fstat(fd, data);//get size of file
	size_t filesize = data->st_size;

	contents = malloc(filesize);
	read(fd, contents, filesize);//read entire file
	//printf("%s", contents);
	return;

}
