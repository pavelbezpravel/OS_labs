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



void* toSend(void* data) {
    char buf[BUFF_SIZE];
    int  i = 0;

    while (!flag) {
        int message = sprintf(buf, "Message: %d", i);

        if (mq_send(qd, buf, message, 0) != -1) {
            printf("send: %s\n", buf);
            fflush(stdout);
        }
        else {
            printf("send error: %s\n", strerror(errno));
            fflush(stdout);
        }

        i++;
        sleep(1);
    }
    pthread_exit(NULL);
}



int main() {
    printf("lab8_1 start\n");
    printf("press <ENTER> to stop\n");

    struct mq_attr attr;

    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;
    attr.mq_msgsize = BUFF_SIZE;
    attr.mq_curmsgs = 0;

    qd = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY | O_NONBLOCK, 0644, &attr);

    if (qd == -1) {
        printf("open error: %s\n", strerror(errno));
        return 0;
    }

    pthread_create(&threadID, NULL, toSend, NULL);

    getchar();

    flag = true;

    pthread_join(threadID, NULL);

    mq_close(qd);
    mq_unlink(QUEUE_NAME);

    printf("lab8_1 end\n");
    return 0;
}