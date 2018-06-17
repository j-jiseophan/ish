#include <stdio.h>
#include "syntactic.h"
#include "dynarray.h"
#include <string.h>
DynArray_T parseTokens(DynArray_T Tokens){
    int bar=0;
    DynArray_T output=DynArray_new(0);
    if(DynArray_getLength(Tokens)==0){
        return NULL;
    }
    int commands=0;
    if(strcmp(DynArray_get(Tokens,0),"|")==0 || strcmp(DynArray_get(Tokens,DynArray_getLength(Tokens)-1),"|")==0){
        perror("syntctic error : invalid bar position\n");
        return NULL;
    }
    for(int i=0;i<DynArray_getLength(Tokens);i++){
        if(commands>=DynArray_getLength(output)){
            DynArray_add(output,DynArray_new(0));
        }
        if(strcmp(DynArray_get(Tokens,i),"|")==0){
            if(bar==1){
                perror("syntactic error : overlaped bars\n");
                return NULL;
            }
            commands++;
            bar=1;
        }
        else{
            
            bar=0;
            DynArray_add(DynArray_get(output,commands),DynArray_get(Tokens,i));
        }
        
    }
    printf("syntactic below \n");
    for(int j=0;j<DynArray_getLength(output);j++){
        printf("\n#%d th command :",j);
        for(int i=0;i<DynArray_getLength(DynArray_get(output,j));i++){
            
            printf("%s, ",(char*)DynArray_get(DynArray_get(output,j),i));
        }
        
    }
    return output;
}