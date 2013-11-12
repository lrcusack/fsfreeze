#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>




int main(){
	
	int fd = open("filenames.txt", O_RDONLY);
	struct stat* data = malloc(sizeof(struct stat));
	//fstat(fd, data);
	//stat("filenames.txt", data);
	//size_t filesize = data->st_size;
	size_t filesize = 1024;
	char* buf = malloc(filesize);
	read(fd, buf, filesize);
	printf("%s", buf);
	return 0;
}
