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
pthread_t threadID_open;
pthread_t threadID_write;



bool sig_handler(int signo) {
    printf("SIGPIPE is gotten\n");
    fflush(stdout);

    sleep(1);

    return true;
}



void* toWrite(void* data) {
    char buf[BUFF_SIZE];
    int  i = 0;

    while (!flag) {
        if (signal(SIGPIPE, (__sighandler_t)sig_handler)) {
            int message = sprintf(buf, "Message: %d", i);

            if (write(fd, buf, message) != -1) {
                printf("write: %s\n", buf);
                fflush(stdout);
            }
        }
        i++;
        sleep(1);
    }
    pthread_exit(NULL);
}



void* toOpenFifoThread(void* data) {
    while (!flag) {
        fd = open(FIFO_NAME, O_WRONLY | O_NONBLOCK | O_CREAT);

        if (fd == -1) {
            printf("%s\n", strerror(errno));
            sleep(1);
        }
        else {
            pthread_create(&threadID_write, NULL, toWrite, NULL);
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}



int main() {
    printf("lab7_1 start\n");
    printf("press <ENTER> to stop\n");

    int fifo = mkfifo(FIFO_NAME, 0666);

    pthread_create(&threadID_open, NULL, toOpenFifoThread, NULL);

    getchar();

    flag = true;

    pthread_join(threadID_open, NULL);
    pthread_join(threadID_write, NULL);

    close(fd);
    unlink(FIFO_NAME);

    printf("lab7_1 end\n");
    return 0;
}