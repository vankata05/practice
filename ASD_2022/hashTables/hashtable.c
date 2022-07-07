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
    if(hash_table[index] != NULL){
        return false;
    }
    hash_table[index] = p;
    return true;
}

//find a person in the hash table
person* hash_table_lookup(char* name){
    int index = hash(name);
    if(hash_table[index] != NULL && strcmp(hash_table[index]->name, name) == 0){
        return hash_table[index];
    }else{
        return NULL;
    }
}

person* hash_table_delete(char* name){
    int index = hash(name);
    if(hash_table[index] != NULL && strcmp(hash_table[index]->name, name) == 0){
        person* tmp = hash_table[index];
        hash_table[index] = NULL;
        return tmp;
    }else{
        return NULL;
    }
}

int main(){
    init_hash_table();

    person ivan = {.name = "Ivan", .age = 17};
    person kaloqn = {.name = "Kaloqn", .age = 18};

    hash_table_insert(&ivan);

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