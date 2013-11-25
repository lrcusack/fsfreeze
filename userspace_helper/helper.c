//### austin blackman ###*/


#include "../headers/project.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
FILE *f;
FILE *f2;
char ch;



//
void write_to_log(char type,FILE* file_name){
	
			
	f = fopen("logfile.txt","w");
			
	if(f == NULL){
		printf("error opening file!\n");
		exit(1);
		}
			
	const char *text = " writing under write_to_log";
	fprintf(f," some text: %s\n",text);
	fclose(f);		
}


//will pass in a filename complete with full path...needs to
//take that in and make a full copy of the file to the restore directory listed in headers.h
void make_clean_copy(char type, char* file_name){

	FILE *str, *cptr;
	if((str = fopen(file_name,"rb"))==NULL){
		fprintf(stderr, "cannot read file \n");
	}
	
	char* output_file = malloc((strlen(RESTOREDIR)+strlen(file_name))*sizeof(char));
	
	 sprintf(output_file,"%s%s",RESTOREDIR,file_name);
	 printf(" output file name is: %s \n",output_file);
	 cptr = fopen(output_file,"rb");
	/*if((cptr = fopen(output_file,"wb"))==NULL){
		fprintf(stderr,"cnnot open output file\n");
	}*/
	printf(" output file name is: %s \n",output_file);
	char b[2];
	int i;
	long size = ftell(str);
	
	for(i = 0;i<size;i++){
		fread(b,1,1,str);
		fwrite(b,1,1,cptr);
	}
	
	fclose(str);
	fclose(cptr); 

}


//pass a filename into this function (FILE*)
//
void handle_change(char type, FILE* file_name){
		//create
		if(type == 'C'){
			
			//write fname to LOG_NAME (using LOG_FORMAT)
			write_to_log('C',file_name);
		}
		
		//modify			
		else if(type == 'M'){
			//write fname to LOG_NAME (using LOG_FORMAT)
			//save a copy of fname to RESTOREDIR
			
			//this option does the original write in write_to_log then closes the file
			//after that, this method opens both the original log and the copy file and copys the original to the copy as a backup
			write_to_log('M',file_name);
			//make_clean_copy('M',file_name);
		}
		
		//delete
		else if (type == 'D'){
			//save a copy of fname to RESTOREDIR
			//make_clean_copy('D',file_name);
			
		}
}


int main(){
	//handle_change('M',file_name);
	
	make_clean_copy('M',"logfile.txt");
	return 0;
}
