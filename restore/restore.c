/**
 * tool to restore frozen directory to freeze point
 * 
 * @author Liam Cusack
 * 
 */


#include "restore.h"

int main(){
	restore(FREEZEDIR,RESTOREDIR,LOG_NAME,DELIM);
	return 0;
}

void restore(char* dest, char* source, char* logfile, char delim){
	llqueue* ll = parse_log_file(logfile,delim);
	delete_logged_files(ll, dest);
	copy_files(dest,source);
	delete_copied_files(source);
	return;
}

void copy_files(char* dest, char* source){
	//copy all files from source directory to dest directory
	DIR* derp;
	struct dirent* dp;
	char outfilename[BUFLEN];
	char infilename[BUFLEN];
	FILE* copyfile;
	FILE* oldfile;
	
	derp = opendir(source);
	while ((dp = readdir(derp)) != NULL){
		//fname is in dp->d_name
		if (strcmp(dp->d_name, LOG_FILE) && strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
			
			sprintf(outfilename, "%s%s", dest, dp->d_name);
			copyfile = fopen(outfilename,"w");
			if(copyfile == NULL){
				printf("cannot open output file\n");
				fclose(copyfile);
				return;
			}
			
			sprintf(infilename, "%s%s", source, dp->d_name);
			oldfile = fopen(infilename,"rb");
			if(oldfile == NULL){
				printf("cannot open input file \n");
				fclose(copyfile);
				fclose(oldfile);
				return;
			}
		
			char c;
			while((c = fgetc(oldfile)) != EOF){
				fputc(c,copyfile);
			}
			
			fclose(copyfile);
			fclose(oldfile); 
		}
	}
	closedir(derp);
	return;
}

void delete_logged_files(llqueue* files, char* location){
	char* fname = NULL;
	char namebuf[BUFLEN];
	while((fname = ll_dequeue(files))){
		//delete file with name fname
		sprintf(namebuf, "%s%s", location, fname);
		unlink(namebuf);
		free(fname);
		//printf("%s\n", fname);
	}
	return;
}
	
llqueue* parse_log_file(char* fname, char delim){

	char namebuf[BUFLEN];
	char* new_fname;

	llqueue* ll = ll_create();
	FILE* logfile = fopen(fname, "r");
	if(logfile == NULL){
		printf("could not open log file\n");
		fclose(logfile);
		return ll;
	}

	while(EOF != fscanf(logfile, "%s", namebuf)){
		new_fname = (char*) malloc (sizeof(char)* strlen(namebuf));
		strcpy(new_fname, namebuf);
		//printf("%s\n", new_fname);
		ll_enqueue(ll, new_fname);
	}
	fclose(logfile);

	return ll;
}

void delete_copied_files(char* location){
	DIR* derp;
	struct dirent* dp;
	char filedel[BUFLEN];
	derp = opendir(location);
	while ((dp = readdir(derp)) != NULL){
		if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
			sprintf(filedel, "%s%s", location, dp->d_name);
			unlink(filedel);
		}
	}
	closedir(derp);
	return;
}
