//### austin blackman ###*/


//#include "../headers/project.h>"
#include<stdlib.h>
#include<stdio.h>
FILE *f;
FILE *f2;
char ch;

int main(){
	handle_change('M');

	return 0;
}

void write_to_log(char type){
	
			
	f = fopen("logfile.txt","w");
			
	if(f == NULL){
		printf("error opening file!\n");
		exit(1);
		}
			
	const char *text = " writing under write_to_log";
	fprintf(f," some text: %s\n",text);
	fclose(f);		
}

void make_log_copy(char type){
	f = fopen("logfile.txt","r");
	f2 = fopen("logcopy.txt","w");
	
	while(1){
		ch = fgetc(f);
		if(ch==EOF){
			break;
		}
		else{
			putc(ch,f2);
		}

	}
	fclose(f);
	fclose(f2);
}

void handle_change(char type){
		//create
		if(type == 'C'){
			
			//write fname to LOG_NAME (using LOG_FORMAT)
			write_to_log('C');
		}
		
		//modify			
		else if(type == 'M'){
			//write fname to LOG_NAME (using LOG_FORMAT)
			//save a copy of fname to RESTOREDIR
			
			//this option does the original write in write_to_log then closes the file
			//after that, this method opens both the original log and the copy file and copys the original to the copy as a backup
			write_to_log('M');
			make_log_copy('M');
		}
		
		//delete
		else if (type == 'D'){
			//save a copy of fname to RESTOREDIR
			make_log_copy('D');
			
		}
	}
