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
// REMARK: Kinda ungly, I'd 100% ask you to explain what and how this line does.	
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

char* getAns(char* filename){
    int fd = open(filename, O_RDONLY);
    if(fd == -1){
// REMARK: Leaking grades
// REMARK: leaking tmp
// both defined in autoGrade()
        printf("Cannot open file %s\n", filename);
        close(fd);
        exit(1);
    }
    
// REMARK: missing error handling
    char* temp = malloc(sizeof(char)*50);
    if(temp == NULL){
        printf("Error allocating memory!\n");
        close(fd);
        exit(2);
    }

    if(read(fd, temp, 50) == -1){
        printf("Error writing to file %s\n", filename);
        close(fd);
        free(temp);
        exit(2);
    }
    
// REMARK: missing error handling
    char* Ans = malloc(sizeof(char)*25);
    if(Ans == NULL){
        printf("Error allocating memory!\n");
        close(fd);
        free(temp);
        exit(3);
    }

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
// OPINION: Can be rewritten prettier with a mathematical expression,
// won't affect your grade.
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

//Is this better?
uint8_t grade2(int points){
    return (points >= 22) ? 6 : (points >= 19) ? 5 : (points >= 16) ? 4 : (points >= 13) ? 3 : 2;
}

void writeGrade(char* filename, uint8_t grade){
    char grade_ = grade + 48;
    int fd = open(filename, O_WRONLY);
    if(fd == -1){
        printf("Cannot open file %s\n", filename);
// REMARK: Leaking memory!
        close(fd);
        exit(3);
    }
    if(write(fd, &grade_, 1) == -1){
        printf("Error writing to file %s\n", filename);
// REMARK: leaking memory!
        close(fd);
        exit(4);
    }
    close(fd);
}

void writeGrades(char* dirname, uint8_t* grades){
    char* temp = malloc((strlen(dirname) + 2) * sizeof(char));;

    if(temp == NULL){
        printf("Error allocating memory!\n");
        free(temp);
        exit(5);
    }

    for(uint8_t i = 0; i < 25; i++){
        temp = strdup(dirname);
// REMARK: i is uninitialized, critical error.
// REMARK: no guarantee temp is long enough to hold both strings
        strcat(temp, itoa(i+1, 10));
        writeGrade(temp, grades[i]);
    }

    free(temp);
}

void autoGrade(char* dirname1, char* ansheet, char* dirname2){
// REMARK: missing error handling
    uint8_t* grades = malloc(sizeof(uint8_t)*25);
    char* temp = malloc((strlen(dirname1) + 2) * sizeof(char));

    if(grades == NULL || temp == NULL){
        printf("Error allocating memory!\n");
        free(grades);
        free(temp);
        exit(5);
    }

    for(uint8_t i = 0; i < 25; i++){
        temp = strdup(dirname1);
// REMARK: Using i unitiliazed!!! Critical error! Fix it!
// According to ISO9899 this is unspecified behavior.
// REMARK: no guarantee temp is long enough to hold both strings!
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