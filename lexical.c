#include "dynarray.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

int i;
int state;
char c;
char curToken[256];
int tokenLength;
int quitionOpen=FALSE;
int quotionBegin;
int quotionEnd;
DynArray_T tokens;
DynArray_T strToTokens(char *input){
    tokens=DynArray_new(0);
    while(input[i]!='\n'){
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
                    for(i;input[i]!='\n';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                        }
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
                    for(i;input[i]!='\n';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                        }
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
                    for(i;input[i]!='\n';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                        }
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
                    for(i;input[i]!='\n';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                        }
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
                    for(i;input[i]!='\n';i++){
                        if (input[i]=='"'){
                            quotionEnd=i;
                        }
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
                    DynArray_add(tokens,curToken);
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
            case ERROR:
                printf("error");
                return 0;
        }
        i++;
    }
    for(int i=0;i<=DynArray_getLength(tokens);i++){
        printf("%s\n",(char*)DynArray_get(tokens,i));
    }
    return tokens;
}
int main(){
    strToTokens("hi my name is jiseop\n");
    return 0;
}