#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned int size = 10;
 
typedef struct student{
    char* name;
    int* grades;
    float average;
}student;

student** students;

int hash(char* name){
    int lenght = strlen(name);
    int hash_value = 0;
    for(int i = 0; i < lenght; i++){
        hash_value += name[i];
        hash_value = hash_value * name[i] % size;
    }
    
    return hash_value;
}

void init_table(){
	students = malloc(sizeof(student*)*size);
    for(int i = 0; i < size; i++){
        students[i] = NULL;
    }
    
}

void print_students(){
    for(int i = 0; i < size; i++){
        if(students[i] == NULL){
            printf("%i\t---\n", i);
        }else{
            printf("%i\t%s\tAVR:%f\n", i, students[i]->name, students[i]->average);
        }
    }
}

void insert_student(student* s){
    if(s == NULL){
        return;
    }
    int index = hash(s->name);
    
    for(int i = 0; i < size; i++){
        int check = (i + index) % size;
        if(students[check] == NULL){
            students[check] = s;
            students = (student**) realloc(students, sizeof(student*)*size);
    		students[size] = NULL;
    		size++;
            return;
        }
    }
}

student* lookup_student(char* name){
    int index = hash(name);
    for(int i = 0; i < size; i++){
        int check = (index + i) % size;
        if(students[check] != NULL && strcmp(students[check]->name, name) == 0){
            return students[check];
        }
    }
    return NULL;
}


float get_average(char* name, int num){
	student* s;
	float avr;
	int clock;
	s = lookup_student(name);
	
	for(int i = 0; i < num; i++){//napravil sum go statichno za momenta
		avr += s->grades[i];
		clock++;
	}
	//printf("\n\nAverage: %f\n", avr/num);
	return avr/num;
	
}

int main(){

	int n, nog;
	init_table();
	
    printf("Enter number of students: ");
    scanf("%d", &n);
    student* temp = malloc(sizeof(student)*n);
    for(int i = 0; i < n; i++){
    	printf("Enter name of student %d: ", i);
    	scanf("%ms", &temp[i].name);
    	printf("Enter number of grades: ");
    	scanf("%d", &nog);
    	printf("Enter the grades:\n");
    	temp[i].grades = malloc(sizeof(int)*nog);
    	for(int x = 0; x < nog; x++){
    		scanf("%d", &temp[i].grades[x]);
    	} 
    	insert_student(&temp[i]);
    	temp[i].average = get_average(temp[i].name, nog);
    }
    
    print_students();
    
/*
    init_table();
    
    student temp;
    temp.name = "Ivan";
    temp.grades = malloc(sizeof(int)*3);
    temp.grades[0] = 2;
    temp.grades[1] = 2;
    temp.grades[2] = 2;
    
    insert_student(&temp);
    
    student temp2;
    temp2.name = "Vasil";
    temp2.grades = malloc(sizeof(int)*3);
    temp2.grades[0] = 2;
    temp2.grades[1] = 3;
    temp2.grades[2] = 2;
    //for(int i = 0; i < 3; i++){
    insert_student(&temp2);
    //}
    
    print_students();
    
    get_average(temp2.name);
    
    
    
    
	int n, m;
	
	printf("input:\n");
	n = getchar();
	n-=48;
	
	for(int i = 0; i < n; i++){
		student temp;
		scanf("%ms", &temp.name);
		int* x;
		x = malloc(sizeof(int));
		for(int a = 0; x[a] != NULL; a++){
			x = (int*) realloc(x, (a+ 2)*sizeof(int));
			scanf("%d", &x[a]); 
			printf("%d\t", x[a]);
		}
	}*/
    
    
    return 0;
}
















