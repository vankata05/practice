#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void close_pipes(int fd1[], int fd2[], int fd3[]) {
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    close(fd3[0]);
    close(fd3[1]);
}

int main() {
    int fd1[2];
    int fd2[2];
    int fd3[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1) {
        perror("pipe1");
        exit(1);
    }

    int pid1 = fork();
    if (pid1 == -1) {
        perror("fork1");
        exit(2);
    } else if (pid1 == 0) {
        // child1
        dup2(fd1[1], STDOUT_FILENO);
        close_pipes(fd1, fd2, fd3);
        execlp("cut", "cut", "-d", ":", "-f", "7", "/etc/passwd", NULL);
    }

    int pid2 = fork();
    if (pid2 == -1) {
        perror("fork2");
        exit(3);
    } else if (pid2 == 0) {
        // child2
        dup2(fd1[0], STDIN_FILENO);
        dup2(fd2[1], STDOUT_FILENO);
        close_pipes(fd1, fd2, fd3);
        execlp("sort", "sort", NULL);
    }

    int pid3 = fork();
    if (pid3 == -1) {
        perror("fork3");
        exit(4);
    } else if (pid3 == 0) {
        // child3
        dup2(fd2[0], STDIN_FILENO);
        dup2(fd3[1], STDOUT_FILENO);
        close_pipes(fd1, fd2, fd3);
        execlp("uniq", "uniq", NULL);
    }

    int pid4 = fork();
    if (pid4 == -1) {
        perror("fork4");
        exit(5);
    } else if (pid4 == 0) {
        // child4
        dup2(fd3[0], STDIN_FILENO);
        close_pipes(fd1, fd2, fd3);
        execlp("wc", "wc", "-l", NULL);
    }

    // parent
    close_pipes(fd1, fd2, fd3);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    waitpid(pid4, NULL, 0);

    return 0;
}
