#include "dynarray.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexical.h"
#define FALSE 0
#define TRUE 1
enum cases{
    START=0,
    IN_NUMBER,
    IN_WORD,
    IN_QUOTION,
    IN_BAR,
    ERROR,
    EXIT
};

//int i;
//int state;

DynArray_T tokens;
DynArray_T strToTokens(char *input){
    int i=0;
    int state=0;
    char c;
    char curToken[256]={0};
    int tokenLength=0;
    int quotionBegin=0;
    int quotionEnd=0;
    tokens=DynArray_new(0);
    
    while(input[i]!='\n' && input[i]!='\r' && input[i]!='\000'){  
        c=input[i];
        switch(state){
            case START:
                if(c=='|'){
                    state=IN_BAR;
                }
                else if(c=='"'){
                    quotionBegin=i;
                    quotionEnd=quotionBegin;
                    i++;
                    for(;input[i]!='\n'&&input[i]!='\000';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                            break;
                        }
                    }
                    if (input[i]=='\n' || input[i]=='\000'){
                        state=ERROR;
                        break;
                    }
                    if(quotionEnd==quotionBegin){
                        state=ERROR;
                        break;
                    }
                    else if(quotionEnd-quotionBegin>1){
                        strncat(curToken,input+quotionBegin+1,quotionEnd-quotionBegin-1);
                        tokenLength+=quotionEnd-quotionBegin-1;
                    }
                    state=IN_QUOTION;
                    break;
                }
                else if(isdigit(c)){
                    curToken[tokenLength]=c;
                    tokenLength++;
                    state=IN_NUMBER;
                }
                else if(isspace(c)){
                    break;
                }
                else{
                    curToken[tokenLength]=c;
                    tokenLength++;
                    state=IN_WORD;
                }
                break;
            case IN_NUMBER:
                if(c=='|'){
                    DynArray_add(tokens,strdup(curToken));
                    memset(curToken,0,sizeof(curToken));
                    tokenLength=0;
                    state=IN_BAR;
                }
                else if(c=='"'){
                    quotionBegin=i;
                    quotionEnd=quotionBegin;
                    i++;
                    for(;input[i]!='\n'&&input[i]!='\000';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                            break;
                        }
                    }
                    if (input[i]=='\n' || input[i]=='\000'){
                        state=ERROR;
                        break;
                    }
                    if(quotionEnd==quotionBegin){
                        state=ERROR;
                        break;
                    }
                    else if(quotionEnd-quotionBegin>1){
                        strncat(curToken,input+quotionBegin+1,quotionEnd-quotionBegin-1);
                        tokenLength+=quotionEnd-quotionBegin-1;
                    }
                    state=IN_QUOTION;
                    break;
                }
                else if(isdigit(c)){
                    curToken[tokenLength]=c;
                    tokenLength++;
                    break;
                }
                else if(isspace(c)){
                    DynArray_add(tokens,strdup(curToken));
                    memset(curToken,0,sizeof(curToken));
                    tokenLength=0;
                    state=START;
                }
                else{
                    curToken[tokenLength]=c;
                    tokenLength++;
                    state=IN_WORD;
                }
                break;
            case IN_WORD:
                if(c=='|'){
                    DynArray_add(tokens,strdup(curToken));
                    memset(curToken,0,sizeof(curToken));
                    tokenLength=0;
                    state=IN_BAR;
                }
                else if(c=='"'){
                    quotionBegin=i;
                    quotionEnd=quotionBegin;
                    i++;
                    for(;input[i]!='\n'&&input[i]!='\000';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                            break;
                        }
                    }
                    if (input[i]=='\n' || input[i]=='\000'){
                        state=ERROR;
                        break;
                    }
                    if(quotionEnd==quotionBegin){
                        state=ERROR;
                        break;
                    }
                    else if(quotionEnd-quotionBegin>1){
                        strncat(curToken,input+quotionBegin+1,quotionEnd-quotionBegin-1);
                        tokenLength+=quotionEnd-quotionBegin-1;
                    }
                    state=IN_QUOTION;
                    break;
                }
                else if(isdigit(c)){
                    curToken[tokenLength]=c;
                    tokenLength++;
                    state=IN_NUMBER;
                }
                else if(isspace(c)){
                    DynArray_add(tokens,strdup(curToken));
                    memset(curToken,0,sizeof(curToken));
                    tokenLength=0;
                    state=START;
                }
                else{
                    curToken[tokenLength]=c;
                    tokenLength++;
                    break;
                }
                break;
            case IN_BAR:
                DynArray_add(tokens,"|");
                if(c=='|'){
                    break;
                }
                else if(c=='"'){
                    quotionBegin=i;
                    quotionEnd=quotionBegin;
                    i++;
                    for(;input[i]!='\n'&&input[i]!='\000';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                            break;
                        }
                    }
                    if (input[i]=='\n' || input[i]=='\000'){
                        state=ERROR;
                        break;
                    }
                    if(quotionEnd==quotionBegin){
                        state=ERROR;
                        break;
                    }
                    else if(quotionEnd-quotionBegin>1){
                        strncat(curToken,input+quotionBegin+1,quotionEnd-quotionBegin-1);
                        tokenLength+=quotionEnd-quotionBegin-1;
                    }
                    state=IN_QUOTION;
                    break;
                }
                else if(isdigit(c)){
                    curToken[tokenLength]=c;
                    tokenLength++;
                    state=IN_NUMBER;
                }
                else if(isspace(c)){
                    state=START;
                }
                else{
                    curToken[tokenLength]=c;
                    tokenLength++;
                    state=IN_WORD;
                }
                break;
            case IN_QUOTION:
                if(c=='|'){
                    DynArray_add(tokens,strdup(curToken));
                    memset(curToken,0,sizeof(curToken));
                    tokenLength=0;
                    state=IN_BAR;
                }
                else if(c=='"'){
                    quotionBegin=i;
                    quotionEnd=quotionBegin;
                    i++;
                    for(;input[i]!='\n'&&input[i]!='\000';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                            break;
                        }
                    }
                    if (input[i]=='\n' || input[i]=='\000'){
                        state=ERROR;
                        break;
                    }
                    if(quotionEnd==quotionBegin){
                        state=ERROR;
                        break;
                    }
                    else if(quotionEnd-quotionBegin>1){
                        strncat(curToken,input+quotionBegin+1,quotionEnd-quotionBegin-1);
                        tokenLength+=quotionEnd-quotionBegin-1;
                    }
                    break;
                }
                else if(isdigit(c)){
                    curToken[tokenLength]=c;
                    tokenLength++;
                    state=IN_NUMBER;
                }
                else if(isspace(c)){
                    DynArray_add(tokens,strdup(curToken));
                    memset(curToken,0,sizeof(curToken));
                    tokenLength=0;
                    state=START;
                }
                else{
                    curToken[tokenLength]=c;
                    tokenLength++;
                    state=IN_WORD;
                }
                break;
        }
        i++;
    }
    if(state==ERROR){
            printf("./ish: Could not find quote pair\n");
            for(int i=0; i<DynArray_getLength(tokens); i++){
                free(DynArray_get(tokens,i));
            }
            DynArray_free(tokens);
            return NULL;
        }
    if(curToken!='\000'&&curToken[0]!=0){ //i think it is not needed
        DynArray_add(tokens,strdup(curToken));
        }
    /*this is for debug
    for(int i=0;i<DynArray_getLength(tokens);i++){
        printf("%dth: %s\n",i,(char*)DynArray_get(tokens,i));
    }
    printf("length : %d\n",DynArray_getLength(tokens));*/
    return tokens;
}/*
int main(){
    char*input="ps -A | grep sshd | sed -e '1,10d'";
    printf("intput is : %s\n",input);
    strToTokens(input);
    return 0;
}*/