#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

char* getAns(char* filename){
    int fd = open(filename, O_RDONLY);
    if(fd == -1)
        exit(1);
    
    char* temp = malloc(sizeof(char)*50);
    if(read(fd, temp, 50) == -1)
        exit(2);
    
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

//cuz the one that came with stdlib wasntworking ('_')
char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

void writeGrades(char*filename, uint8_t* grades){
    char* temp = malloc(sizeof(uint8_t)*50);
    printf("Hewwo");
    for(int i = 0; i < 50; i+=2){
        temp[i] = grades[i/2] + 48;
        temp[i+1] = '\n';
    }
    printf("%s", temp);
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

    free(temp);
}

int main(int argc, char* argv[]){
    //printf("%d\n", compFiles(argv[1], "./answers/1"));
    autoGrade("./answers/", "./answers_sheet/correct_answers", "./results/");
    
    return 0;
}