#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

char* head(int fd, unsigned int n){
    char* temp = malloc(sizeof(char)*128);
    char* out = malloc(sizeof(char)*128);
    unsigned int bytes_read = read(fd, temp, 128);
    if(bytes_read == -1){
        exit(2);
    }
    unsigned int lines = 0;

    for(int a = 0; lines != n; a++){
        for(int b = 0; b < bytes_read; b++){
            if(temp[b] == '\n')
                lines++;

            if(lines == n){
                out[(a*128)+b] = 0;
                free(temp);
                return out;
            }

            out[(a*128)+b] = temp[b];
        }
        if(lines != n){
            bytes_read = read(fd, temp, 128);
            if(bytes_read == -1){
                exit(3);
            }
            if(bytes_read == 0){
                out[(a+1)*128] = 0;
                free(temp);
                return out;
            }
            out = (char*) realloc(out, sizeof(char)*(((a+1)*128)+bytes_read+1));
        }
    }
    free(temp);
    return out;
}

int main(int argc, char **argv){
    if(argc == 1){
        printf("Misiing arguments!\n");
        exit(0);
    }

    char* filename = argv[1];
    int fd = open(filename, O_RDONLY);

    if(fd == -1){
        printf("Unable to open file!\n");
        exit(1);
    }

    for (int i = 2; i < argc; ++i){
        if(!strcmp(argv[i] , "-n")){
            printf("%s\n", head(fd, atoi(argv[i+1])));
        }
    }

    if(argc == 2){
        printf("%s\n", head(fd, 10));
    }

    close(fd);

    return 0;
}