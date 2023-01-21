#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int find(char* str, char c){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == c){
            return i;
        }
        i++;
    }
    return i;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file name>\n", argv[0]);
        return 1;
    }

    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        perror("Could not open file");
        return 1;
    }

    int move = 0;
    int rd = 1;

    char* line = malloc(sizeof(char)*257);
    if(line == NULL){
        printf("Could not allocate memory");
        return 1;
    }
    
    while (rd > 0) {
        rd = read(file,line, 256);
        if(rd == -1){
            printf("Could not read file");
            return 1;
        }

        while(move < rd){
            
            int temp = find(line, '\n')+1;;
            move += temp;
            line[temp-1] = '\0';

            char *command = strtok(line, " ");
            char *options[64];
            int option_count = 0;

            while (command != NULL) {
                options[option_count++] = command;
                command = strtok(NULL, " ");
            }

            int pid = fork();

            if (pid == 0) {
                execvp(options[0], options);
                exit(1);
            } else {
                int status;
                wait(&status);
                if (WIFEXITED(status)) {
                    printf("Command %s exited with status %d\n\n", options[0], WEXITSTATUS(status));
                } else {
                    printf("Command %s did not exit normally\n\n", options[0]);
                }
            }
            if(temp < rd)
                line += temp;
        }
    }

    close(file);
    return 0;
}