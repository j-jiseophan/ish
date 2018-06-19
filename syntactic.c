#include <stdio.h>
#include "syntactic.h"
#include "dynarray.h"
#include <string.h>
#include <stdlib.h>
DynArray_T parseTokens(DynArray_T tokens){
    int bar=0;
    DynArray_T output=DynArray_new(0);
    if(DynArray_getLength(tokens)==0){
        DynArray_free(tokens);
        return NULL;
    }
    int commands=0;
    if(strcmp(DynArray_get(tokens,0),"|")==0 || strcmp(DynArray_get(tokens,DynArray_getLength(tokens)-1),"|")==0){
        perror("./ish: invalid bar position\n");
        for(int i=0; i<DynArray_getLength(tokens); i++){
            free(DynArray_get(tokens,i));
        }
        DynArray_free(tokens);
        return NULL;
    }
    for(int i=0;i<DynArray_getLength(tokens);i++){
        if(commands>=DynArray_getLength(output)){
            DynArray_add(output,DynArray_new(0));
        }
        if(strcmp(DynArray_get(tokens,i),"|")==0){
            if(bar==1){
                perror("./ish: overlaped bars\n");
                /*for(int i=0; i<DynArray_getLength(tokens); i++){
                    free(DynArray_get(tokens,i));
                }*/
                DynArray_free(tokens);
                return NULL;
            }
            commands++;
            bar=1;
        }
        else{
            
            bar=0;
            DynArray_add(DynArray_get(output,commands),DynArray_get(tokens,i));
        }
        
    }
    int lts,gts;//redirection processing
    for(int i=0; i<DynArray_getLength(output); i++){
        lts=0;gts=0;
        for(int j=0; j<DynArray_getLength(DynArray_get(output,i));j++){
            if(strchr((DynArray_get(DynArray_get(output,i),j)),'<')){
                if(i>0 || 
                    strchr((DynArray_get(DynArray_get(output,i),j)),'<')!=
                    strrchr((DynArray_get(DynArray_get(output,i),j)),'<')||
                    lts==1){
                    fprintf(stderr,"Invalid: Multiple redirection of standard input\n");
                    return NULL;
                }
                if(j==0){
                    fprintf(stderr, "Invalid: Missing command name\n");
                    return NULL;
                }
                if(DynArray_getLength(DynArray_get(output,i))==j+1){
                    fprintf(stderr, "Invalid: Standard input redirection without file name\n");
                    return NULL;
                }

                lts=1;
            }
            
            if(strchr((DynArray_get(DynArray_get(output,i),j)),'>')){
                if(DynArray_getLength(output)>i+1 || 
                    strchr((DynArray_get(DynArray_get(output,i),j)),'>')!=
                    strrchr((DynArray_get(DynArray_get(output,i),j)),'>')||
                    gts==1){
                    fprintf(stderr,"Invalid: Multiple redirection of standard output\n");
                    return NULL;
                }
                if(j==0){
                    fprintf(stderr, "Invalid: Missing command name\n");
                    return NULL;
                }
                if(DynArray_getLength(DynArray_get(output,i))==j+1){
                    fprintf(stderr, "Invalid: Standard output redirection without file name\n");
                    return NULL;
                }
                gts=1;
            }
           
           
               
        }
    }
    DynArray_free(tokens);
    /*this is for debugging*/
    printf("syntactic below ################33\n");
    for(int j=0;j<DynArray_getLength(output);j++){
        printf("\n#%d th command :",j);
        for(int i=0;i<DynArray_getLength(DynArray_get(output,j));i++){
            
            printf("%s, ",(char*)DynArray_get(DynArray_get(output,j),i));
        }
        
    }
    printf("\n##############\n");
    printf("\n");
    
    return output;
}