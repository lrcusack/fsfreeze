#include "../headers/project.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>


int main(){
	printf("beginning my test function \n");
	int file_d;
	file_d = open("/dev/filename_holder",O_RDWR);
	printf("finished my open\n");
	ssize_t read_var;
	ssize_t count = 16*sizeof(char);
	char buff[16];
	read_var = read(file_d, buff, count);
	printf("finished my read \n");
	
	


}
