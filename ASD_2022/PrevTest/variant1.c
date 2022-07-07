//TODO:https://docs.google.com/document/d/1Xfk5gqXyPoLp2AaQd8c4C7B-iXnu0EPMxfoiHQDoy94/edit

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct warrior_t{
    float damage, defence, health;
    char name[32];
} warrior_t;

//randomly selects wich warrior to start the fight
warrior_t row_a_dice(struct warrior_t first, struct warrior_t second){
    int r = rand();
    if(r % 2 == 0){
        return first;
    }else{
        return second;
    }
}

//implementation of the fight
int fight(warrior_t first, warrior_t second){
    if(strcmp(first.name, row_a_dice(first, second).name)){
        while(first.health > 0 && second.health > 0){
            printf("%s %.1fhp : %s %.1fhp\n", first.name, first.health, second.name, second.health);
            printf("%s attacks\n", first.name);
            if(second.defence >= first.damage){
                second.health-=1;
            }else{
                second.health+=second.defence-first.damage;
            }
            printf("%s %.1fhp : %s %.1fhp\n", first.name, first.health, second.name, second.health);
            printf("%s attacks\n", second.name);
            if(first.defence >= second.damage){
                first.health-=1;
            }else{
                first.health+=first.defence-second.damage;
            }
        }
        if(first.health <= 0){
            printf("%s wins", second.name);
            return 1;
        }else{
            printf("%s wins", first.name);
            return 0;
        }
    }
}

int main(){
    warrior_t first;
    warrior_t second;

    printf("Enter the name of the first warrior:");
    scanf("%s", &first.name);
    printf("Enter the damage of the first warrior:");
    scanf("%f", &first.damage);
    printf("Enter the defence of the first warrior:");
    scanf("%f", &first.defence);
    printf("Enter the health of the first warrior:");
    scanf("%f", &first.health);

    printf("Enter the name of the second warrior:");
    scanf("%s", &second.name);
    printf("Enter the damage of the second warrior:");
    scanf("%f", &second.damage);
    printf("Enter the defence of the second warrior:");
    scanf("%f", &second.defence);
    printf("Enter the health of the second warrior:");
    scanf("%f", &second.health);

    fight(first, second);

    return 0;
}