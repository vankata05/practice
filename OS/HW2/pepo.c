#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 256 

void manual_warning(char *message, char *also) {
    printf("\033[35mmanual-warning:\033[m \033[33m%s [\033[m\033[35m-%s\033[m\033[33m]\033[m", message, also); 
} 

void tokenizer(char* line, char** command, char** options) {
    *command = strtok(line, " ");
    *options = strtok(NULL, "");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        manual_warning("only 2 command line arguments are expected", "!Number-of-arguments"); 
        exit(2); 
    }

    int file_name = open(argv[1], O_RDONLY);
    if (file_name == -1) {
        manual_warning("Couldn't open file for reading", "Fatal-error"); 
        exit(3); 
    }

    char line[MAX_LINE_LENGTH];
    int bytes_read;
    while ((bytes_read = read(file_name, line, MAX_LINE_LENGTH)) > 0) {
        line[bytes_read - 1] = '\0';

        char* command;
        char* options;
        tokenizer(line, &command, &options);

        pid_t pid = fork();
        if (pid == -1) {
            manual_warning("fork() failed", "Fatal-error"); 
            close(file_name); 
            exit(4); 
        } else if (pid == 0) {
            execlp(command, command, options, NULL);
            printf("Error: exec failed for command %s\n", command); 
            manual_warning("execclp failed", "Fatal-error"); 
            exit(1);
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                printf("%s succeeded\n", command);
            } else {
                printf("%s failed\n", command);
            }
        }
    }

    close(file_name);
    return 0;
}