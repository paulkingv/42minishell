#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    pid_t   pid;
    char    *input;
    char    *args[2];

    input = readline("Enter: ");
    args[0] = input;
    args[1] = NULL;
    pid = fork();

    if (pid == 0)
    {
        execvp(args[0], args);
    }
    else
    {
        waitpid(pid, NULL, 0);
        printf("child is done\n");
    }
    return (0);
}