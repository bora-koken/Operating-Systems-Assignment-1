#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

int main() {

    int pid;

    struct timeval time;

    pid = fork();

    if(pid == 0) { //Child process
        while(1) {
            gettimeofday(&time, NULL);
            printf("Time is: %ld === Child's PID: %d\n" , time.tv_sec , getpid());
            sleep(1);
        }
    }

    else if (pid > 0) { //Parent process
        printf("Parent's PID: %d\n" , getpid());
        sleep(5);
        kill(pid, SIGTERM);
        printf("Child <%d> killed. \n" , pid);
    }

    else if (pid < 0) { //Fork failed process
        printf("Fork Failed!\n");
    }
}