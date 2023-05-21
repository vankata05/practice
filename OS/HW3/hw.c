#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int p1[2], p2[2], p3[2], p4[2];
    pipe(p1);
    pipe(p2);
    pipe(p3);
    pipe(p4);

    if (fork() == 0) 
    { 
        //cut -d : -f 7 /etc/passwd
        dup2(p1[1], STDOUT_FILENO); 
        close(p1[0]); 
        close(p1[1]);

        execlp("cut", "cut", "-d :", "-f 7", "/etc/passwd", NULL);
    }
    else if (fork() == 0) 
    { 
        //sort 
        dup2(p1[0], STDIN_FILENO); 
        dup2(p2[1], STDOUT_FILENO); 
        close(p1[0]); 
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("sort", "sort", NULL); 
    }
    else if (fork() == 0) 
    { 
        //uniq
        dup2(p2[0], STDIN_FILENO); 
        dup2(p3[1], STDOUT_FILENO); 
        close(p2[0]); 
        close(p2[1]);
        close(p3[0]);
        close(p3[1]);
        
        execlp("uniq", "uniq", NULL); 
    }
    else if (fork() == 0) 
    { 
        //wc -l
        dup2(p3[0], STDIN_FILENO); 
        dup2(p4[1], STDOUT_FILENO); 
        close(p3[0]); 
        close(p3[1]);
        close(p4[0]);
        close(p4[1]);
        
        execlp("wc", "wc", "-l", NULL); 
    }
    else 
    { 
        // parent 
        dup2(p4[0], STDIN_FILENO); 
        char result[1000];
        read(p4[0], result, sizeof(result)); 
        printf("Count of unique shell users: %s\n", result);
        
        wait(NULL); 
        wait(NULL); 
        wait(NULL); 
        wait(NULL);
    } 
    exit(0);
    return 0;
}