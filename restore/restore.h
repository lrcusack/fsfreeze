/**
 * headers for restore function
 * 
 * @author Liam Cusack
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include "../headers/project.h"
#include "../headers/list.h"

void restore(char* dest, char* source, char* logfile, char delim);
void copy_files(char* dest, char* source);
void delete_logged_files(llqueue* files, char* location);
void delete_copied_files(char* location);
llqueue* parse_log_file(char* fname, char delim);
