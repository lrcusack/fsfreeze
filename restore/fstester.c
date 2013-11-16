/**
 * 
 * program to perform all possible file system changes
 * 
 * @author Shawn Carrick
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fctnl.h>

#define BUFLEN 16

int main(){
	int fd = open("myfile.txt",O_RDWR | O_CREAT);
	char buffer[BUFLEN];
	sprintf(buffer, "git some\n");
	int i;
	for(i=0;i<10;i++){
		write(fd,buffer,sizeof(buffer));
	}
	
	
}
