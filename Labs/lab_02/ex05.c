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

typedef struct {
    char path[N];
    char *filename;
} t_data;

void *t_recursive_directory(void *par);

int main(int argc, char *argv[]) {

    int n = argc - 1;
    int rc, i;
    void *status;
    pthread_t th[n];

    t_data out[N];

    for (i = 0; i < n; i++) {
        //strcpy(out[i].path,argv[i+1]);
        rc = pthread_create(&th[i], NULL, t_recursive_directory, (void *) &out[i]);
    }
    for (i = 0; i < n; i++) {
        rc = pthread_join(th[i], &status);
    }
    pthread_exit(NULL);

    return (1);
}

void *t_recursive_directory(void *par) {

    DIR *dp;
    struct stat buf;
    struct dirent *dirp;
//char buffer[BUFFERSIZE];
    char fullName[N];
    t_data *values;
    values = (t_data *) par;
    char tmp[N];
//strcpy(tmp,values->path);

    FILE *fp;
    pid_t pId = getppid();
    pthread_t tId = pthread_self();
    char *adhoc = malloc(4 * sizeof(long int));
    sprintf(adhoc, "pid_%d_tid_%ld", pId, tId);
    strcpy(values->filename, adhoc);

    if ((fp = fopen(values->filename, "a")) == NULL)
        exit(0);

    if (lstat(tmp, &buf) < 0) {
        fprintf(stderr, "Error 1.\n");
        exit(1);
    }
    if (S_ISDIR(buf.st_mode) == 0) {
        fprintf(stderr, "Error 2.\n");
        exit(1);
    }
    if ((dp = opendir(tmp)) == NULL) {
        fprintf(stderr, "Error 3.\n");
        exit(1);
    }
    while ((dirp = readdir(dp)) != NULL) {

        sprintf(fullName, "%s/%s", tmp, dirp->d_name);

        if (lstat(fullName, &buf) < 0) {

            fprintf(stderr, "Error.\n");
            exit(1);
        }
        if (S_ISDIR(buf.st_mode) == 0) {
            /*int fp1,fp2,nR,nW;
            FILE* f2;
            int fp1
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
             close(fp1);*/



            fprintf(fp, "%s\n", fullName);
            //fprintf (stdout, "File: %s TID: %ld\n",fullName,pthread_self() );
        } else {
            //fprintf (stdout, "Dir %s: TID: %ld\n",fullName,pthread_self());
            fprintf(fp, "%s\n", fullName);
            if (fullName[strlen(fullName) - 1] != '.')
                t_recursive_directory(fullName);
        }
    }
    if (closedir(dp) < 0) {
        fprintf(stderr, "Error.\n");
        exit(1);
    }
    fclose(fp);

    pthread_exit(NULL);
} 
