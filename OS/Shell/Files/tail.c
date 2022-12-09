#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

char* reverse(char* str){
    unsigned int len = strlen(str);
    char* temp = malloc(sizeof(char)*len);
    strcpy(temp, str);

    for(int i = 1; i < len; i++)
        str[i-1] = temp[len-i-1];
    
    str[len-1] = 0;

    free(temp);
    return str;
}

char* tail(int fd, unsigned int n){
    char* out = malloc(sizeof(char)*128);
    unsigned int size_out = 128;
    unsigned int lines = 0;

    if(lseek(fd, -1, SEEK_END) == -1)
        exit(2);

    for(int i = 0; lines != n; i++){
        char temp[1];
        int check;
        
        if(i == size_out){
            size_out*=2;
            out = (char*) realloc(out, size_out);
        }

        check = read(fd, temp, 1);
        if(check == -1)
            exit(2);
        if(check != 1)
            return reverse(out);
        
        out[i] = temp[0];

        if(lseek(fd, -2, SEEK_CUR) == -1){
            printf("lseek failed!");
            exit(3);
        }

        if(out[i] == '\n')
            lines++;
    }

    return reverse(out);
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
            printf("%s\n", tail(fd, atoi(argv[i+1])));
            printf("Hello");
        }
    }

    if(argc == 2){
        printf("%s\n", tail(fd, 10));
    }

    close(fd);

    return 0;
}