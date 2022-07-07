#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    void* data;
    struct Node *next;
} Node;
//push to the front of the list
struct Node* push(struct Node* head, void* data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = head;
    return new_node;
}
int main(){
    Node* list = NULL;
    //remember to set the list after push
    list = push(list, "!");
    list = push(list, "World ");
    list = push(list, "Middle ");
    list = push(list, "Hello ");
    //print out the elements
    Node* crnt = list;
    while(crnt != NULL){
        printf("%s", crnt->data);
        crnt = crnt->next;
    }
    return 0;
}