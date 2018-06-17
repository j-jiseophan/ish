#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include "dynarray.h"
#include "lexical.h"
#include "syntactic.h"
#include "execution.h"
#define BUFFERSIZE 1024

int initialization(){
    FILE *fp;
    DynArray_T tokens;
    char buffer[BUFFERSIZE];
    fp = fopen("/home/.ishrc", "r");
    while(!feof(fp)){
        fgets(buffer, sizeof(buffer), fp);
        printf("%% %s",buffer);
        tokens=strToTokens(buffer);
        if(tokens==NULL){
            continue;
        }
        tokens=parseTokens(tokens);
        if(tokens==NULL){
            continue;
        }
        //printf("\n--------------------------------\n");
    }
    fclose(fp);
    return 0;
}
int main(void){
    DynArray_T tokens;
    initialization();
    while(1){
        pid_t pid1;
        char userInput[BUFFERSIZE];
        printf("%% ");
        fgets(userInput, BUFFERSIZE, stdin);
        printf("usr : %s\n",userInput);
        tokens=strToTokens(userInput);
        if(tokens==NULL){
            printf("error : NULL token\n");
          //  return -1;
        }
        tokens=parseTokens(tokens);
        if(tokens==NULL){
            printf("error : NULL parsed\n");
            //return -1;
        }
        exeAll(tokens);
    }
    
    
    return 0;
}