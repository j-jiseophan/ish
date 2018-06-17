#include <stdio.h>
#include "syntactic.h"
#include "dynarray.h"
#include <string.h>
DynArray_T parseTokens(DynArray_T tokens){
    int bar=0;
    DynArray_T output=DynArray_new(0);
    if(DynArray_getLength(tokens)==0){
        return NULL;
    }
    int commands=0;
    if(strcmp(DynArray_get(tokens,0),"|")==0 || strcmp(DynArray_get(tokens,DynArray_getLength(tokens)-1),"|")==0){
        perror("./sampleish: invalid bar position\n");
        return NULL;
    }
    for(int i=0;i<DynArray_getLength(tokens);i++){
        if(commands>=DynArray_getLength(output)){
            DynArray_add(output,DynArray_new(0));
        }
        if(strcmp(DynArray_get(tokens,i),"|")==0){
            if(bar==1){
                perror("./sampleish: overlaped bars\n");
                return NULL;
            }
            commands++;
            bar=1;
        }
        else{
            
            bar=0;
            DynArray_add(DynArray_get(output,commands),DynArray_get(tokens,i));
        }
        
    }/*this is for debugging
    printf("syntactic below \n");
    for(int j=0;j<DynArray_getLength(output);j++){
        printf("\n#%d th command :",j);
        for(int i=0;i<DynArray_getLength(DynArray_get(output,j));i++){
            
            printf("%s, ",(char*)DynArray_get(DynArray_get(output,j),i));
        }
        
    }*/
    return output;
}