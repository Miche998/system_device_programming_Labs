#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <aio.h>
#include <fcntl.h>
#include <errno.h>

#define STR_SIZE 50
#define WAIT_TIME_1 2
#define WAIT_TIME_2 3
#define STR_NUM 5
#define BUFF_SIZE 2048

void randomString(int n, const char seed[], char *buf);

void ToCapitalString(char *buf, int n);

int main() {
    pid_t c1, c2;
    int count = 0;
    int count2 = 0;
    const char seed_string[26] = "abcdefghijklmnopqrstuvwxyz";
    int file1[2], file2[2], r;
    struct aiocb aiocb, aiocb2;
    struct timespec t;
    t.tv_nsec = 5000;
    t.tv_sec = 1;
    r = 0;
    if (pipe(file1) == 0) { //First create the pipe 0 on success
        c1 = fork();
        if (c1 == -1) {
            fprintf(stderr, "Fork failure c1");
            exit(EXIT_FAILURE);
        }
        if (c1 == 0) { //C1 code
            close(file1[0]); //close read end

            while (count2 != STR_NUM) {
                sleep(WAIT_TIME_1);

                srandom(time(NULL));
                r = (rand() % (STR_SIZE - 1));
                char buf[r];

                randomString(r, seed_string, buf);

                write(file1[1],&r,sizeof(r));
                write(file1[1],buf,sizeof(buf) );

                count2++;
            }
            printf("EXIT C2\n");
            exit(EXIT_SUCCESS);

        } else { //Parent code
            if (pipe(file2) == 0) {
                c2 = fork();
                if (c2 == -1) {
                    fprintf(stderr, "Fork failure c2");
                    exit(EXIT_FAILURE);
                }
                if (c2 == 0) { //C2 code
                    close(file2[0]); //Close read end

                    while (count != STR_NUM) {

                        sleep(WAIT_TIME_2);
                        srandom(time(NULL));
                        r = (rand() % (STR_SIZE - 1));
                        char buf[r];
                        randomString(r, seed_string, buf);

                        write(file2[1], &r, sizeof(r));
                        write(file2[1], buf, sizeof(buf));

                        count++;
                    }
                    printf("EXIT C2\n");
                    exit(EXIT_SUCCESS);
                } else { //Parent Code
                    close(file1[1]); //close write end
                    close(file2[1]); //close write end

                    int c1_size, c2_size, f_count = 0;
                    char out1[BUFF_SIZE], out2[BUFF_SIZE];

                    memset(&aiocb, 0, sizeof(struct aiocb));
                    memset(&aiocb2, 0, sizeof(struct aiocb));
                    aiocb.aio_fildes = file1[0];
                    aiocb2.aio_fildes = file2[0];

                    while (f_count != STR_NUM) {

                        aiocb.aio_buf = &c1_size;
                        aiocb.aio_nbytes = sizeof(r);

                        aio_read(&aiocb);

                        memset(out1,0,c1_size*sizeof(char));
                        while (aio_error(&aiocb) == EINPROGRESS)
                            sleep(1);


                        aiocb.aio_buf = out1;
                        aiocb.aio_nbytes = sizeof(out1) - 1;

                        aio_read(&aiocb);
                        while (aio_error(&aiocb) == EINPROGRESS);


                        out1[c1_size] = '\0';
                        ToCapitalString(out1, c1_size);
                        printf("CHILD1 STRING %d OF SIZE %d: %s\n", f_count + 1, c1_size, out1);

                        aiocb2.aio_buf = &c2_size;
                        aiocb2.aio_nbytes = sizeof(r);

                        aio_read(&aiocb2);
                        while (aio_error(&aiocb2) == EINPROGRESS)
                            sleep(1);

                        aiocb2.aio_buf = out2;
                        aiocb2.aio_nbytes = sizeof(out2) - 1;

                        aio_read(&aiocb2);
                        while (aio_error(&aiocb2) == EINPROGRESS);


                        out2[c2_size] = '\0';
                        ToCapitalString(out2, c2_size);
                        printf("CHILD2 STRING %d OF SIZE %d: %s\n", f_count + 1, c2_size, out2);

                        f_count++;
                    }
                }
            }
        }
        exit(EXIT_SUCCESS);
    }

    return 0;
}

void randomString(int n, const char seed[], char *buf) {
    int c;
    srandom(time(NULL));
    for (int i = 0; i < n; i++) {
        c = rand() % 26;
        buf[i] = seed[c];
    }
}

void ToCapitalString(char *buf, int n) {
    for (int i = 0; i < n; i++)
        buf[i] -= 32;
}