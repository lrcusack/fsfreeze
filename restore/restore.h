/**
 * headers for restore function
 * 
 * @author Liam Cusack
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

void restore(char* dest, char* source, char* logfile, char delim);
void copy_files(char* dest, char* source);
void delete_files(llqueue* files);
int next_token(char** text, char* token, char delim);
void read_file(char* fname, char* contents);
llqueue* parse_log_file(char* fname, char delim);
