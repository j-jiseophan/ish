#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include "dynarray.h"
#include "lexical.h"
#include "syntactic.h"

int initialization(){
    FILE *fp;
    DynArray_T Tokens,synOutput;
    char buffer[256];
    fp = fopen("/home/.ishrc", "r");
    while(!feof(fp)){
        fgets(buffer, sizeof(buffer), fp);
        printf("%s\n",buffer);
        Tokens=strToTokens(buffer);
        if(Tokens==NULL){
            printf("error : NULL Token\n");
            return -1;
        }
        synOutput=parseTokens(Tokens);
        if(synOutput==NULL){
            printf("error : NULL parsed\n");
            return -1;
        }
        printf("\n--------------------------------\n");
    }
    fclose(fp);
}
int main(void){

    return 0;
}