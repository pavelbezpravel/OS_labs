#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

int       BUFF_SIZE   = 256;
int       fd;
char      FIFO_NAME[] = {"/tmp/my_pipe"};
bool      flag        = false;
pthread_t threadID_read;



void* toRead(void* data) {
    char buf[BUFF_SIZE] = {'\0'};

    while (!flag) {
        memset(buf, 0, BUFF_SIZE);

        if (read(fd, buf, BUFF_SIZE) != -1) {
            if (*buf != 0) {
                printf("read: %s\n", buf);
                fflush(stdout);
            }
        }

        sleep(1);
    }
    pthread_exit(NULL);
}



int main() {
    printf("lab7_2 start\n");
    printf("press <ENTER> to stop\n");

    int fifo = mkfifo(FIFO_NAME, 0666);
        fd   = open(FIFO_NAME, O_RDONLY | O_NONBLOCK | O_CREAT);

    pthread_create(&threadID_read, NULL, toRead, NULL);

    getchar();

    flag = true;

    pthread_join(threadID_read, NULL);

    close(fd);
    unlink(FIFO_NAME);

    printf("lab7_2 end\n");
    return 0;
}