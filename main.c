#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <assert.h>
#include "dynarray.h"
#include "lexical.h"
#include "syntactic.h"
#include "execution.h"
#include "sighandler.h"
#define BUFFERSIZE 1024

int initialization(){
    FILE *fp;
    DynArray_T tokens;
    char buffer[BUFFERSIZE];
    //chdir("/mnt/home/20170726");
    fp = fopen("/mnt/home/20170726/.ishrc","r");
    //fp = fopen("/home/.ishrc", "r");//my pc : /home/.ishrc, labmachine : /mnt/home/20170726
    while(!feof(fp)){
        fgets(buffer, sizeof(buffer), fp);
        printf("%% %s",buffer);
        if (buffer[0]==4){
            continue;
        }
        tokens=strToTokens(buffer);
        if(tokens==NULL){
            printf("error : NULL token\n");
            continue;
        }
        tokens=parseTokens(tokens);
        if(tokens==NULL){
            printf("error : NULL parsed\n");
            continue;
        }
        exeAll(tokens);
        //printf("\n--------------------------------\n");
    }
    fclose(fp);
    return 0;
}
int main(void){
    DynArray_T tokens;
    void (*pfSig1)(int);
    void (*pfSig2)(int);
    void (*pfSig3)(int);
    pfSig1 = signal(SIGINT, SIG_IGN);
    pfSig2 = signal(SIGQUIT, handleSIGQUIT);
    pfSig3 = signal(SIGALRM, handleSIGALRM);
    assert(pfSig1 != SIG_ERR);
    assert(pfSig2 != SIG_ERR);
    assert(pfSig3 != SIG_ERR);
   // initialization();
    while(1){
        pid_t pid1;
        char userInput[BUFFERSIZE];
        
        printf("%% ");
        fgets(userInput, BUFFERSIZE, stdin);
        //printf("usr : %s\n",userInput);
        tokens=strToTokens(userInput);
        if(tokens==NULL){
            printf("error : NULL token\n");
            continue;
          //  return -1;
        }
        tokens=parseTokens(tokens);
        if(tokens==NULL){
            printf("error : NULL parsed\n");
            continue;
            //return -1;
        }
        exeAll(tokens);
    }
    
    
    return 0;
}