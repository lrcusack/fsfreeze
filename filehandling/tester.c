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
	
	ssize_t write_var1, write_var2, write_var3;
	ssize_t read_var1, read_var2, read_var3;
	char read_buff[PATH_MAX];
	

	char* b1 = " whats ";
	char* b2 = " up ";
	char* b3 = " bitch ";
	ssize_t count1 = strlen(b1)*sizeof(char);
	ssize_t count2 = strlen(b2)*sizeof(char);
	ssize_t count3 = strlen(b3)*sizeof(char);
	

	printf("here....\n");
	
	
	write_var1 = write(file_d, b1, count1);
	write_var2 = write(file_d, b2, count2);
	write_var3 = write(file_d, b3, count3);
	printf("finished my write \n");
	
	read_var1 = read(file_d,read_buff,PATH_MAX);
	printf("%s \n",read_buff);
	read_var2 = read(file_d,read_buff,PATH_MAX);
	printf("%s \n",read_buff);
	read_var3 = read(file_d,read_buff,PATH_MAX);
	printf("%s \n",read_buff);
	printf("finished my read \n");
	


}
