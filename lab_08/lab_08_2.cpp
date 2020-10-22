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
#include <mqueue.h>

int       BUFF_SIZE    = 32;
bool      flag         = false;
char      QUEUE_NAME[] = {"/my_queue"};
pthread_t threadID;
mqd_t     qd;



void* toReceive(void* data) {
    char buf[BUFF_SIZE] = {'\0'};
    int  status;

    while (!flag) {
        memset(buf, 0, BUFF_SIZE);
        status = mq_receive(qd, buf, BUFF_SIZE, NULL);

        if (status > 0) {
            printf("receive: %s\n", buf);
            fflush(stdout);
        }
        else if (status == -1) {
            printf("receive error: %s\n", strerror(errno));
            fflush(stdout);
        }
        sleep(1);
    }
    pthread_exit(NULL);
}



int main() {
    printf("lab8_2 start\n");
    printf("press <ENTER> to stop\n");

    struct mq_attr attr;

    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;
    attr.mq_msgsize = BUFF_SIZE;
    attr.mq_curmsgs = 0;

    qd = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY | O_NONBLOCK, 0644, &attr);

    if (qd == -1) {
        printf("open error: %s\n", strerror(errno));
        return 0;
    }

    pthread_create(&threadID, NULL, toReceive, NULL);

    getchar();

    flag = true;

    pthread_join(threadID, NULL);

    mq_close(qd);
    mq_unlink(QUEUE_NAME);

    printf("lab8_2 end\n");
    return 0;
}