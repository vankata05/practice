#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person{
    char name[MAX_NAME];
    int age;
    //other stuff
}person;

//use pointers so i would be able to delete just by setting the pointer to NULL
person* hash_table[TABLE_SIZE];

unsigned int hash(char* name){
    int lenght = strlen(name);
    unsigned int hash_value = 0;
    for(int i = 0; i < lenght; i++){
        hash_value += name[i];
        hash_value = hash_value * name[i] % TABLE_SIZE;//to randomize it more we multiply and we use % so the output can fit in the table
    }
    
    return hash_value;
}

bool init_hash_table(){
    for(int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
    // initialize empty table
}

void print_table(){
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hash_table[i] == NULL){
            printf("%i\t---\n", i);
        }else{
            printf("%i\t%s\n", i, hash_table[i]->name);
        }
    }
}

bool hash_table_insert(person *p){
    if(p == NULL){
        return false;
    }
    int index = hash(p->name);
    // the loop is to prevent collisions
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try] == NULL){
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

//find a person in the hash table
person* hash_table_lookup(char* name){
    int index = hash(name);
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (index + i) % TABLE_SIZE;
        if(hash_table[try] != NULL && strcmp(hash_table[try]->name, name) == 0){
            return hash_table[try];
        }
    }
    return NULL;
}

person* hash_table_delete(char* name){
    int index = hash(name);
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (index + i) % TABLE_SIZE;
        if(hash_table[try] != NULL && strcmp(hash_table[try]->name, name) == 0){
            person* tmp = hash_table[index];
            hash_table[index] = NULL;
            return tmp;
        }
    }
    return NULL;
}

int main(){
    init_hash_table();

    person ivan = {.name = "Ivan", .age = 17};
    person ivan1 = {.name = "Ivan1", .age = 17};
    person ivan2 = {.name = "Ivan2", .age = 17};
    person ivan3 = {.name = "Ivan3", .age = 17};
    person ivan4 = {.name = "Ivan4", .age = 17};
    person ivan5 = {.name = "Ivan5", .age = 17};
    person ivan6 = {.name = "Ivan6", .age = 17};
    person ivan7 = {.name = "Ivan7", .age = 17};
    person ivan8 = {.name = "Ivan8", .age = 17};
    person ivan9 = {.name = "Ivan9", .age = 17};

    person kaloqn = {.name = "Kaloqn", .age = 18};

    hash_table_insert(&ivan);
    hash_table_insert(&ivan1);
    hash_table_insert(&ivan2);
    hash_table_insert(&ivan3);
    hash_table_insert(&ivan4);
    hash_table_insert(&ivan5);
    hash_table_insert(&ivan6);
    hash_table_insert(&ivan7);
    hash_table_insert(&ivan8);
    hash_table_insert(&ivan9);

    hash_table_insert(&kaloqn);

    hash_table_delete("Kaloqn");

    print_table();

    person* tmp = hash_table_lookup("Petyo"); 
    if(tmp == NULL){
        printf("NotFound!!!\n");
    }else{
        printf("Found!!!\n");
    }
    tmp = hash_table_lookup("Ivan"); 
    if(tmp == NULL){
        printf("NotFound!!!\n");
    }else{
        printf("Found!!!\n");
    }
    
    return 0;
}