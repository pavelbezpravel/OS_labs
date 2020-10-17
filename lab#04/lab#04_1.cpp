#include <unistd.h>
#include <stdio.h>



int main(int argc, char* argv[]) {
    printf("lab4_1 start\n");
    printf("parent  process ID from lab4_1: %d\n", getppid());
    printf("program process ID from lab4_1: %d\n", getpid());

    if (argc == 1) {
        printf("no args\n");
        printf("lab4_1 end\n");
        return 1;
    }
    else {
        for (int i = 0; argv[i] != 0; i++) {
            printf("arg %d: %s \n", i, argv[i]);
            sleep(1);
        }
    }

    printf("lab4_1 end\n");
    return 13;
}