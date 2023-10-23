#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
using namespace std;
int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        for(int i = 0; i< 5; i++)
        {
            sleep(1);
            printf("this is child\n");
        }
        printf("child is going to die\n");
    }
    else if(pid > 0)
    {   
        int status = -1;
        pid_t pid_c;
        do
        {   
            pid_c = waitpid(pid, &status, WNOHANG);
            printf("father is waiting for child\n");
            if(WIFEXITED(status))
            {
                printf("status %d", status);
            }
            sleep(2);
        }while(pid_c == 0);
    }
    return 1;
}