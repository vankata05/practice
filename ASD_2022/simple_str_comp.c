#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* compress(char* str){
    char *out = (char*)calloc(strlen(str), sizeof(char));

    int next = 0;
    for(int i = 0; i < strlen(str); i++){
        int a = 0;
        while(str[i] == str[i+a]){
            a++;
        }
        out[next] = str[i];
        next++;
        if(a > 1){
            out[next] = a  + '0';
            next++;
        }
        i += a-1;
    }
    return out;
}

int main(){
    char* str = "hello";
    char* out = compress(str);
    printf("%s\n", out);
    
    free(out);

    return 0;
}
