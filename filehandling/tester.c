#include "../headers/project.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>


int main(){
	printf("beginning my test function \n");
	int file_d;
	file_d = open("/dev/filename_holder",O_RDWR);
	printf("finished my opennnnn\n");
	
	ssize_t write_var;
	ssize_t read_var;
	char read_buff[PATH_MAX];
	
	char* buff = " whaddup bitch ";
	
	
	ssize_t count = strlen(buff)*sizeof(char);
	printf("here....\n");
	
	
	write_var = write(file_d, buff, count);
	printf("finished my write \n");
	
	read_var = read(file_d,read_buff,PATH_MAX);
	printf("finished my read \n");
	printf("%s \n",read_buff);
	


}
