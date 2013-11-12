#include "restore.h"
	
	
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
