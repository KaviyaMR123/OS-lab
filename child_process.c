#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid < 0) 
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } 
    else if (pid == 0) 
    {
        printf("Child process: PID = %d\n", getpid());
        sleep(3); 
        printf("Child process exiting\n");
        return 0;
    } 
    else 
    {
        printf("Parent process: PID = %d\n", getpid());
        printf("Parent process waiting for child to exit...\n");
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) 
        {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
        else 
        {
            printf("Child process exited abnormally\n");
        }
    }
    return 0;
}
