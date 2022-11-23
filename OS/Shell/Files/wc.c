#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

unsigned int bytes_(int fd){
    unsigned int bytes = lseek(fd, 0, SEEK_END);

    lseek(fd, 0, SEEK_SET);
    
    if(bytes == -1)
        exit(2);

    return bytes;
}

unsigned int lines(int fd){
    unsigned int lines = 1;
    char temp[128];
    unsigned int bytes_left = read(fd, temp, 128);

    while(bytes_left != 0){
        if(bytes_left == -1)
            exit(3);

        for(int i = 0; i < bytes_left; i++)
            if(temp[i] == '\n')
                lines++;
                
        bytes_left = read(fd, temp, 128);
    }

    if(lseek(fd, 0, SEEK_SET) == -1)
        exit(4);

    return lines;

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
        if(!strcmp(argv[i] , "-c")){
            printf("The file contains %d bytes.\n", bytes_(fd));
        }else if(!strcmp(argv[i] , "-l")){
            printf("The file contains %d lines.\n", lines(fd));
        }else{
            printf("Invalid argiment %s!\n", argv[i]);
        }
    }

    if(argc == 2){
        printf("The file contains %d bytes.\n", bytes_(fd));
        printf("The file contains %d lines.\n", lines(fd));
    }

    close(fd);

    return 0;
}