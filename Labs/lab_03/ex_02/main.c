#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    int id;
    long r_no;
    char surname[30];
    char name[30];
    int mark;
} mys;

int main() {
    int fdin;
    struct stat st;
    size_t len_file;
    void *m;
    off_t fsz = 0;

    fdin = open("/home/michele/Documenti/lab_clion/lab_03/ex_02/file_1.txt",O_RDWR);
    if(fdin<0) {
        perror("Error opening file open()");
        exit(1);
    }
    if(fstat(fdin,&st)<0){
        perror("Error in file size fstat()");
        exit(1);
    }
    len_file = st.st_size;
    mys data;
    while(fsz<(1024*1024*1024)) {
        m =(int*) mmap(0, len_file, PROT_READ | PROT_WRITE, MAP_SHARED, fdin, 0);
        //m+=sizeof(int)+1;
        char tmp[200];
        fscanf(m,"%s",tmp);
        //memcpy(&r_no, m, sizeof(int));
        printf("%s",tmp);
        munmap(m,fsz);
        fsz+=(1024*1024*1024);
    }


}
