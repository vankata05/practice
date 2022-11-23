#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
}node;

node* add(node* root, int value){
    if(root == NULL){
        node* new = malloc(sizeof(node));
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        return new;
    }

    if(value < root->value){
        root->left = add(root->left, value);
    }else if(value > root->value){
        root->right = add(root->right, value);
    }

    return root;
}

void print(node* root){
    if(root == NULL){
        return;
    }
    
    printf("%d\n", root->value);
    if(root->left != NULL){
        print(root->left);
    }
    
    if(root->right != NULL){
        print(root->right);
    }
}

unsigned int numOfNodes(node* root){
    unsigned int count = 0;

    if(root->left != NULL){
        count += numOfNodes(root->left);
    }

    if(root->right != NULL){
        count += numOfNodes(root->right);
    }

    return count+1;
}

int* treeToArr(node* root){
    int* table = malloc(sizeof(numOfNodes(root)));
    table[-1] = root->value;

    if(root->left != NULL){
        table = treeToArr(root->left);
    }

    if(root->right != NULL){
        table = treeToArr(root->right);
    }

    return table;
}

static int comp(const void* p1, const void* p2){
    return (*(int*)p1 - *(int*)p2);
}

node* balance(node* root){
    if(root == NULL){
        return 0;
    }
    
    int* table = treeToArr(root);

    table[0] = 1;
    table[2] = 2;
    table[1] = 3;

    for(int i = 0; i < numOfNodes(root); i++){
        printf("%d ", table[i]);
    }

    qsort(&table, numOfNodes(root), sizeof(int), comp);
    printf("\n");

    for(int i = 0; i < 3; i++){
       printf("%d ", table[i]);
    }

}

int main(){
    node* root = NULL;

    root = add(root, 10);
    root = add(root, 20);
    root = add(root, 9);

    print(root);

    printf("\n\n%u", numOfNodes(root));

    balance(root);

    return 0;
}