#include "restore.h"
	


int next_token(char** text, char* token, char delim){
	int ii;
	int end=0;
	while(){
		ii++;
		char current = *(*text+ii);
		if (current == EOF){
			end=1;
			break;
		}
		if (current == delim) break;
	}
	token=(char*)malloc(ii+1);
	strncpy(token,*text,ii+1);
}
	
void read_file(char* fname, char* contents)	{
	int fd = open(fname, O_RDWR);
	struct stat* data = malloc(sizeof(struct stat));
	fstat(fd, data);
	size_t filesize = data->st_size;
	contents = malloc(filesize);
	read(fd, contents, filesize);
	//printf("%s", contents);
	return;

}
