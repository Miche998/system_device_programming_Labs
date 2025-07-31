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
void SearchDirectory(const char *name);

int main(int argc, char* argv[]){
	struct stat buf;
	DIR *dp,*dp2;

	char buffer[BUFFERSIZE];
	struct dirent *dirp;
	int i;
/*
	if (lstat(argv[1], &buf) < 0 ) {
		fprintf (stderr, "Error 1.\n"); exit (1);
 	}
	if (S_ISDIR(buf.st_mode) == 0) {
		fprintf (stderr, "Error 2.\n"); exit (1);
 	}
	if ( (dp = opendir(argv[1])) == NULL) {
		fprintf (stderr, "Error 3.\n"); exit (1);
 	}
 	if ( (dp2 = opendir(argv[2])) == NULL) {
		fprintf (stderr, "Error 3.\n"); exit (1);
 	}
	i = 0;
*/
	SearchDirectory(argv[1]);

return (1);
}


void SearchDirectory(const char *name) {
    DIR *dir = opendir(name);                //Assuming absolute pathname here.
    if(dir) {
        char Path[256], *EndPtr = Path;
        struct dirent *e;
        strcpy(Path, name);                  //Copies the current path to the 'Path' variable.
        EndPtr += strlen(name);              //Moves the EndPtr to the ending position.
        while((e = readdir(dir)) != NULL) {  //Iterates through the entire directory.
            struct stat info;                //Helps us know about stuff
            strcpy(EndPtr, e->d_name);       //Copies the current filename to the end of the path, overwriting it with each loop.
            if(!stat(Path, &info)) {         //stat returns zero on success.
                if(S_ISDIR(info.st_mode)) {  //Are we dealing with a directory?
                    //Make corresponding directory in the target folder here.
                    printf("Dir: %s\n",Path);
                    SearchDirectory(Path);   //Calls this function AGAIN, this time with the sub-name.
                } else if(S_ISREG(info.st_mode)) { 
		     //Or did we find a regular file?
		     printf("File: %s\n",Path);
                    //Run Copy routine
                }
            }
        }
    }
}
