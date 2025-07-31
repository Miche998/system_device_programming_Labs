#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <string.h>

#define N 1000
#define BUFFERSIZE 4096

int recursive_directory(char tmp[N],char tmp2[N],int i,int k);
int main(int argc, char* argv[]){

int i,k;
k = i = 0;
 recursive_directory(argv[1],argv[2],i,k);

return (1);
}
int recursive_directory(char tmp[N],char tmp2[N],int i,int k){

DIR *dp;
struct stat buf;
struct dirent *dirp;
char buffer[BUFFERSIZE];
char fullName[N],fullNameOut[N];

if (lstat(tmp, &buf) < 0 ) {
	fprintf (stderr, "Error 1.\n"); exit (1);
 }
if (S_ISDIR(buf.st_mode) == 0) {
	fprintf (stderr, "Error 2.\n"); exit (1);
 }
if ( (dp = opendir(tmp)) == NULL) {
	fprintf (stderr, "Error 3.\n"); exit (1);
 }
while ( (dirp = readdir(dp)) != NULL) {
 	
	sprintf (fullName, "%s/%s", tmp, dirp->d_name);
	sprintf (fullNameOut, "%s/%s", tmp2, dirp->d_name);

if (lstat(fullName, &buf) < 0 ) {
	
	fprintf (stderr, "Error.\n"); exit (1);
 }
if (S_ISDIR(buf.st_mode) == 0) {
	int fp1,fp2,nR,nW;
	FILE* f2;
	fprintf (stdout, "File %d: %s\n", k, fullName);
	k++;
	char *fname,tmp[N];
	fname = basename(fullNameOut);
	fp2 = open(fullNameOut,O_CREAT|O_WRONLY,S_IRWXU | S_IRGRP | S_IXOTH);
	close(fp2);
	fp1 = open(fullName,O_RDONLY);
	struct stat st;
	stat(fullName,&st);
	int size = st.st_size;
	if((f2 = fopen(fullNameOut,"w"))==NULL)
		exit(0);
	fprintf(f2,"%s\n",fname);
	fprintf(f2,"%d\n",size);
	while( (nR = read (fp1, buffer, BUFFERSIZE) >0)){
 		fprintf(f2,"%s\n",buffer);
 	}
 	fclose(f2);
 	close(fp1);
 	
 	
} else {
	//if(i>0){
	mkdir(fullNameOut,S_IRWXU | S_IRGRP | S_IXOTH);
	fprintf (stdout, "Dir %d: %s\n", i, fullName);
	if(fullName[strlen(fullName)-1]!='.') 
	recursive_directory(fullName,fullNameOut,i,k);
	//}	
 }
i++;
 }
 if (closedir(dp) < 0) {
	fprintf (stderr, "Error.\n"); exit (1);
 }

return (1);
} 
