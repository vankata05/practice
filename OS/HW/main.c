#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

//cuz the one that came with stdlib wasn't working for some reason ('_')
char* itoa(uint8_t val, uint8_t base){
	
	static char buf[32] = {0};
	
	uint8_t i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

char* getAns(char* filename){
    int fd = open(filename, O_RDONLY);
    if(fd == -1){
        printf("Cannot open file %s\n", filename);
        exit(1);
    }
    
    char* temp = malloc(sizeof(char)*50);
    if(read(fd, temp, 50) == -1){
        printf("Error writing to file %s\n", filename);
        exit(2);
    }
    
    char* Ans = malloc(sizeof(char)*25);
    uint8_t next = 0;
    for(uint8_t i = 0; i < 50; i++){
        if(temp[i] == '\n')
            i++;
        Ans[next] = temp[i];
        next++;
    }

    free(temp);
    close(fd);
    return Ans;
}

uint8_t compFiles(char* filename1, char* filename2){
    char* file1 = getAns(filename1);
    char* file2 = getAns(filename2);
    uint8_t right = 0;

    for(uint8_t i = 0; i < 25; i++){
        if(file1[i] == file2[i]){
            right++;
        }
    }

    free(file1);
    free(file2);
    return right;
}

uint8_t grade(int points){
    if(points >= 22){
        return 6;
    }else if(points >= 19){
        return 5;
    }else if(points >= 16){
        return 4;
    }else if(points >= 13){
        return 3;
    }else{
        return 2;
    }
}

void writeGrade(char* filename, uint8_t grade){
    char grade_ = grade + 48;
    int fd = open(filename, O_WRONLY);
    if(fd == -1){
        printf("Cannot open file %s\n", filename);
        exit(3);
    }
    if(write(fd, &grade_, 1) == -1){
        printf("Error writing to file %s\n", filename);
        exit(4);
    }
}

void writeGrades(char* dirname, uint8_t* grades){
    char* temp;

    for(uint8_t i; i < 25; i++){
        temp = strdup(dirname);
        strcat(temp, itoa(i+1, 10));
        writeGrade(temp, grades[i]);
    }

    free(temp);
}

void autoGrade(char* dirname1, char* ansheet, char* dirname2){
    uint8_t* grades = malloc(sizeof(uint8_t)*25);
    char* temp;
    char integer[2];

    for(uint8_t i; i < 25; i++){
        temp = strdup(dirname1);
        strcat(temp, itoa(i+1, 10));
        grades[i] = grade(compFiles(ansheet, temp));
    }

    writeGrades(dirname2, grades);

    free(grades);
    free(temp);
}

int main(int argc, char* argv[]){
    // autoGrade("./answers/", "./answers_sheet/correct_answers", "./results/");
    if(argc < 4){
        printf("Not enought parameters!\n");
        exit(4);
    }else{
        autoGrade(argv[1], argv[2], argv[3]);
    }
    return 0;
}