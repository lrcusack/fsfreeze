/**
 * 
 * test writing to and reading from chardev
 * 
 * @author Austin Blackman
 * 
 */

#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>

int main(){
	int fd;
	char stuff[16];
	char other[16];
	memset(stuff,0,16);
	memset(other,0,16);
	snprintf(stuff,sizeof(char)*16,"my name is");
	printf("%s \n",other);
	fd = open("/dev/filename_holder",O_RDWR);
	write(fd, stuff, sizeof(stuff));
	printf("%s \n",other);
	read(fd, other, sizeof(other));
	printf("%s \n",other);
	return 0;

}
