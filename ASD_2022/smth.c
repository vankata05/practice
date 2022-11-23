#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct student_t{
    char* name;
    float* grades;
}student_t;

typedef struct table{
    student_t** students;
    int table_len;
}table;

void init_table(table* t, int len){
    t->students = malloc(len*sizeof(student_t));

    for (int i = 0; i < len; i++){
        t->students[i] = NULL;
    } 

    t->table_len = len;
}

unsigned int hash(student_t student, int table_len){
    int index = 0;
    int len = strlen(student.name);

    for (int i = 0; i < len; i++){
        index+= student.name[i];
    }

    return index % table_len;
}

//lipsva proverka dali student e prazno i dali veche sushtestvuva
void add_student(student_t* student, table* t){
    int index = hash(*student, t->table_len);
    while(1){
        if (t->students[index] == NULL){
            t->students[index] = student;
            // printf("%s", t->students[index]->name);
            return;
        }else if(index == t->table_len){
            return;
        }
        index++;
    }
}

void print_table(table t){
    for(int i = 0; i < t.table_len; i++){
        if(t.students[i] != NULL){
            printf("%d:\t%s\n", i, t.students[i]->name);
        }
    }
}

int main(){
    table dnevnik;

    // int n, m;

    // scanf("%d", n);
    init_table(&dnevnik, 2);
    // for(int i = 0; i < dnevnik.table_len; i++){
    //     student_t temp;
        
    //     scanf("%s" &temp.name);
    //     printf("Endter number of grades:\n")
    //     scanf("%d[^32}", );
        
        
    // }
    student_t student = (student_t){.name = "Stoqn"};
    student_t student1 = (student_t){.name = "Ivan"};\

    add_student(&student, &dnevnik);
    add_student(&student1, &dnevnik);
    
    
    
    // printf("%d:\t%s", 0, dnevnik.students[0]->name);

    // for(int i = 0; i < dnevnik.table_len; i++){
    //     if(dnevnik.students[i] != NULL){
    //         printf("%d:\t%s\n", i, dnevnik.students[i]->name);
    //     }
    // }

    print_table(dnevnik);



    return 0;
}