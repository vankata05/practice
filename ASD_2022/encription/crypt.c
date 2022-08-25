#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* encypt(char* in){
    unsigned int len = strlen(in);
    char* out = malloc(len*sizeof(char));
    out[len] = '\0';
    for (int i = 0; i < len; i++){
        if(in[i]%2 == 0){
            out[i] = in[i] + 2;
        }else{
            out[i] = in[i] + 4;
        }
        printf("%d\t%d\n", in[i], out[i]);
    }

    return out;
}

char* decrypt(char* in){
    unsigned int len = strlen(in);
    char* out = malloc(len-1*sizeof(char));
    out[len] = '\0';
    for (int i = 0; i < len; i++){
        if(in[i]%2 == 0){
            out[i] = in[i] - 2;
        }else{
            out[i] = in[i] - 4;
        }
        printf("%d\t%d\n", in[i], out[i]);
    }

    return out;
}

int main(){
    char* str = "efghijk";

    char* out = encypt(str);
    printf("Encrypted: %s\n", out);
    printf("Decrypted: %s\n", decrypt(out));
    return 0;
}