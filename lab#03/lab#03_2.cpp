#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

bool flag1     = false;
bool flag2     = false;
int  BUFF_SIZE = 256;
int  field[2];



void* function1(void* arg) {
    printf("thread1\n");

    bool* flag = (bool*)arg;
    int   i    = 0;
    char  buf[BUFF_SIZE];

    while (!*flag) {
        int message = sprintf(buf, "Message %d\n", i);
        int err     = write(field[1], buf, message);

        if(!err) {
            perror("write");
        }

        i++;
        sleep(1);
    }

    printf("end1\n");
    pthread_exit(NULL);
}

void* function2(void* arg) {
    printf("thread2\n");

    bool* flag = (bool*)arg;
    char  buf[BUFF_SIZE];

    while (!*flag) {
        memset(buf, 0, BUFF_SIZE);
        int err = read(field[0], buf, BUFF_SIZE);

        if (err > 0) {
            printf("%s\n", buf);
            fflush(stdout);
        }
        else {
            perror("read");
        }

        sleep(1);
    }

    printf("end2\n");
    pthread_exit(NULL);
}


int main() {
    printf("thread0\n");

    pthread_t t1;
    pthread_t t2;

    pipe(field);

    int fl1 = fcntl(field[0], F_GETFL);
    int fl2 = fcntl(field[1], F_GETFL);

    fcntl(field[0], F_SETFL, fl1 | O_NONBLOCK);
    fcntl(field[1], F_SETFL, fl2 | O_NONBLOCK);

    pthread_create(&t1, NULL, function1, (void*)&flag1);
    pthread_create(&t2, NULL, function2, (void*)&flag2);

    getchar();

    flag1 = true;
    flag2 = true;


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    close(field[0]);
    perror("close");

    close(field[1]);
    perror("close");

    printf("end0\n");

    return 0;
}