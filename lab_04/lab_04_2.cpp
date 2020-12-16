#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char* argv[]) {
    printf("lab4_2 start\n");

    pid_t pid = fork();

    if (pid != 0) {
        printf("parent  process ID from lab4_2: %d\n", getppid());
        printf("program process ID from lab4_2: %d\n", getpid());

        int status;
        while (waitpid(pid, &status, WNOHANG) == 0) {
            printf("wait\n");
            sleep(1);
        }

        if (WIFEXITED(status)) {
            printf("process finished successfully with status: %d \n", WEXITSTATUS(status));
        }
        else {
            printf("process finished unsuccessfully\n");
        }
    }
    else {
        printf("parent  process ID from lab4_2: %d\n", getppid());
        printf("program process ID from lab4_2: %d\n", getpid());

        execlp("./lab_04_1", "0", "1", "2", "3", NULL);
    }

    printf("lab4_2 end\n");
    return 0;
}
