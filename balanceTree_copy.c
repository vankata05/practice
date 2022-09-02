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
/*
int *_treeToArr(node *root, int *values, int index) {
    if (root->left == NULL && root->right == NULL) {
        if(values[index] == 0){
            index++;
        }
        values[index] = root->value;
        return values;
    }

    if (root->left != NULL)
        values = _treeToArr(root->left, values, index+1);
    
    if(values[index] == 0){
        index++;
    }
    values[index] = root->value;
    index++;
    
    if (root->right != NULL)
        values = _treeToArr(root->right, values, index+1);

    return values;
}
*/
int* _treeToArr(node* root, int* arr,int* index){
    if(root == NULL){
        return arr;
    }

    arr[*index] = root->value;
    *index = *index + 1;
    
    if(root->left != NULL){
        arr = _treeToArr(root->left, arr, index);
    }
    
    if(root->right != NULL){
        arr = _treeToArr(root->right, arr, index);
    }

    return arr;
}

int *treeToArr(node *root) {
    int *arr = malloc(numOfNodes(root) * sizeof(int));
    int i = 0;
    return _treeToArr(root, arr, &i);
}

int comp(const void* p1, const void* p2){
    return *(int*)p1 - *(int*)p2;
}

node* arrToTree(node* new, int* arr, unsigned int num){
    if(num == 0){
        return NULL;
    }

    new = add(new, arr[num/2]);

    new = arrToTree(new, arr, num/2);

    new = arrToTree(new, arr + num/2+1 ,num - num/2 - 1);

    print(new);

    return new;
}

node* balance(node* root){ 

    if(root == NULL){
        return 0;
    }
    
    int* table = treeToArr(root);

    for(int i = 0; i < numOfNodes(root); i++){
        printf("%d ", table[i]);
    }

    qsort(table, numOfNodes(root), sizeof(int), comp);
    printf("\n");

    for(int i = 0; i < numOfNodes(root); i++){
        printf("%d ", table[i]);
    }

    node* new = NULL;
    print(arrToTree(new, table, numOfNodes(root)));
    print(new);
    return new;
}

int main(){
    node* root = NULL;

    root = add(root, 10);
    root = add(root, 20);
    root = add(root, 9);
    root = add(root, 15);
    root = add(root, 5);
    root = add(root, 11);

    print(root);

    root = balance(root);

    printf("neshto si");
    print(root);

    return 0;
}