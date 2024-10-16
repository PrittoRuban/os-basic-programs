#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    switch (pid = fork())
    {
    case -1:
        // Fork failed
        perror("Fork failed");
        exit(-1);
    case 0:
        // Child process
        printf("Child process\n");
        execl("/bin/date", "date", NULL); // Corrected the third argument to NULL
        perror("execl failed");           // In case execl fails
        exit(0);
    default:
        // Parent process
        wait(NULL); // Wait for child to finish
        printf("Child Terminated\n");
        exit(0);
    }

    return 0;
}
