#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <string.h>
#include <pthread.h>

#define N 1000
#define BUFFERSIZE 4096

void *t_recursive_directory(void *par);
int main(int argc, char* argv[]){

int n=argc-1;
int rc;
pthread_t th[n];
void *status;

for(int i=0;i<n;i++){
	rc = pthread_create(&th[i],NULL,t_recursive_directory,(void *) argv[i+1]);
}
for(int i=0;i<n;i++){
	rc = pthread_join(th[i],&status);
}
pthread_exit(NULL);

return (1);
}
void *t_recursive_directory(void *par){

DIR *dp;
struct stat buf;
struct dirent *dirp;
char fullName[N];
char *tmp = (char *)par;

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

if (lstat(fullName, &buf) < 0 ) {
	
	fprintf (stderr, "Error.\n"); exit (1);
 }
if (S_ISDIR(buf.st_mode) == 0) {
	fprintf (stdout, "File: %s TID: %ld\n",fullName,pthread_self() );
} else {
	
	fprintf (stdout, "Dir %s: TID: %ld\n",fullName,pthread_self());
	if(fullName[strlen(fullName)-1]!='.') 
		t_recursive_directory(fullName);

 	}
 }
 if (closedir(dp) < 0) {
	fprintf (stderr, "Error.\n"); exit (1);
 }

pthread_exit(NULL);
} 
