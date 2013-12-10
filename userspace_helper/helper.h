#include "../headers/project.h"
#include "../headers/list.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void write_to_log(char type, char* file_name);
void make_clean_copy(char type, char* file_name);
void handle_change(char type, char* file_name);
void helper();
void testerfct();
int isInList(llqueue** fnames_addr, char* newname);

