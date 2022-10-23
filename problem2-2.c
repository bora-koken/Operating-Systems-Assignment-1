#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int fd1[2];
    int fd2[2];
    int fd3[2];
    int fd4[2];

    int child1Result = 0;
    int child2Result = 0;

    if (pipe(fd1) == -1) {
        printf("Pipe Failed!");
    }
    
    if (pipe(fd2) == -1) {
        printf("Pipe Failed!");
    }

    if (pipe(fd3) == -1) {
        printf("Pipe Failed!");
    }

    if (pipe(fd4) == -1) {
        printf("Pipe Failed!");
    }

    int pid;
    pid = fork();

    if(pid < 0) {
        sleep(5);

        printf("Fork Failed!");
    }

    else if(pid > 0) {
        sleep(5);

        int input;
        printf("Enter an integer from the standart input: ");
        scanf("%d", &input);

        close(fd1[0]);

        write(fd1[1], &input, sizeof(int));
        close(fd1[1]);

        wait(NULL);

        close(fd2[1]);

        read(fd2[0], &child1Result, sizeof(int));
        read(fd2[0], &child2Result, sizeof(int));
        int f = child1Result + child2Result;
        printf("The final result is %d. \n", f);
        close(fd2[0]);

        kill(pid, SIGKILL);
    }

    else if(pid == 0) {
        sleep(5);

        int pid2;
        pid2 = fork();

        if(pid2 < 0) {
            sleep(5);

            printf("Fork Failed!");
        }

        if(pid2 > 0) {
            sleep(5);
            
            close(fd1[1]);
            close(fd3[0]);

            int parentResult = 0;
            read(fd1[0], &parentResult, sizeof(int));

            int x = (parentResult * pid);

            printf("First Child: Input<%d>, Output<%d> \n", parentResult, x);

            write(fd3[1], &x, sizeof(int));
            close(fd3[1]);

            wait(NULL);

            close(fd4[1]);

            read(fd4[0], &child2Result, sizeof(int));
            close(fd4[0]);

            close(fd1[0]);
            close(fd2[0]);

            write(fd2[1], &child2Result, sizeof(int));
            close(fd2[1]);

            kill(pid2, SIGKILL);
        }

        else if(pid2 == 0) {
            sleep(5);
    
            close(fd3[1]);

            int parentResult = 0;
            read(fd3[0], &parentResult, sizeof(int));

            int x = (pid2 / parentResult);

            printf("Second Child: Input<%d>, Output<%d> \n", parentResult, x);

            close(fd3[0]);
            close(fd4[0]);

            write(fd4[1], &x, sizeof(int));
            close(fd4[1]);
        }
    }
}    