#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>


void randomString(int n, const char seed[], char *buf);

void ToCapitalString(char *buf, int n);

int main() {
    pid_t c1;
    char *myfifo = "/tmp/myfifo_";
    int count = 0, n;
    int fd_c,fd_p; // file descriptor for the fifo
    char seed_string[29] = "abcdefghijklmnopqrstuvwxyz ";
    strcat(seed_string, "\n");
    int ret = mkfifo(myfifo, 0666); //make the fifo
    if( ret == -1 ) {
        perror("Error -- makefifo");
        exit(EXIT_FAILURE);
    }
    c1 = fork(); //forking process
    if (c1 == -1) {
        fprintf(stderr, "Fork failure c1\n");
        exit(EXIT_FAILURE);
    }
    if (c1 == 0) { //Child code P2

        int size;
        srand(time(NULL) + getppid()); //seed for rand()
        while (1) {
            fd_c = open(myfifo,O_RDONLY); //Open the fifo in read_mode
            if(fd_c == -1){
                perror("Error on open");
                exit(EXIT_FAILURE);
            }
            char *in_buf, *out_buf;
            read(fd_c, &size, sizeof(size));
            in_buf = malloc((size + 1) * sizeof(char));
            read(fd_c, in_buf, size);
            printf("Received string from P1:\t %s\t SIZE:%lu\n", in_buf, strlen(in_buf));
            ToCapitalString(in_buf, size);
            printf("Converted to Capital...:\t %s\n", in_buf);
            close(fd_c); //closinf fd for next write

            fd_c = open(myfifo,O_WRONLY); //Open the fifo in read_mode
            if(fd_c == -1){
                perror("Error on open");
                exit(EXIT_FAILURE);
            }
            sleep(2);
            n = rand() % 100;
            if (n == 0) {
                printf("CHILD generated 0 size string.. Dying\n");
                unlink(myfifo);
                exit(EXIT_SUCCESS);
            }
            out_buf = malloc((n + 1) * sizeof(char));
            randomString(n, seed_string, out_buf);
            write(fd_c, &n, sizeof(int));
            write(fd_c, out_buf, strlen(out_buf));
            free(in_buf);
            free(out_buf);
            close(fd_c);
        }

    } else { //Parent code P1
        int size;
        srand(time(NULL)); //seed for rand()
        while (1) {
            fd_p = open(myfifo,O_WRONLY); //Open the fifo in read_mode
            if(fd_p == -1){
                perror("Error on open");
                exit(EXIT_FAILURE);
            }
            char *in_buf, *out_buf;
            sleep(1);
            n = rand() % 100;
            if (n == 0) {
                kill(c1, SIGKILL);
                c1 = wait(NULL);
                if (c1 == -1)
                    perror("error on wait");
                else {
                    printf("Child %d killed\n", c1);
                    exit(EXIT_SUCCESS);
                }
            }
            out_buf = malloc((n + 1) * sizeof(char));
            randomString(n, seed_string, out_buf);
            write(fd_p, &n, sizeof(int));
            write(fd_p, out_buf, strlen(out_buf));
            close(fd_p);

            fd_p = open(myfifo,O_RDONLY); //Open the fifo in read_mode
            if(fd_p == -1){
                perror("Error on open");
                exit(EXIT_FAILURE);
            }
            read(fd_p, &size, sizeof(size));
            if (size == 0) {
                kill(c1, SIGKILL);
                c1 = wait(NULL);
                if (c1 == -1)
                    perror("error on wait");
                else {
                    printf("Child %d killed\n", c1);
                    unlink(myfifo);
                    exit(EXIT_SUCCESS);
                }
            }
            in_buf = malloc((size + 1) * sizeof(char));
            read(fd_p, in_buf, size);
            printf("Received string from P2 (child):\t %s\t SIZE:%lu\n", in_buf, strlen(in_buf));
            ToCapitalString(in_buf, size);
            printf("Converted to Capital...:\t %s\n", in_buf);
            free(in_buf);
            free(out_buf);
            close(fd_p);
        }
    }
    return 0;
}

void randomString(int n, const char seed[], char *buf) {
    int c;
    for (int i = 0; i < n; i++) {
        c = rand() % 29;
        buf[i] = seed[c];
    }
}

void ToCapitalString(char *buf, int n) {
    for (int i = 0; i < n; i++) {
        buf[i] = toupper((unsigned char) buf[i]);
    }
}