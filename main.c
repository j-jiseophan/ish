#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "lexical.h"

int main(void){
    FILE *fp;
    DynArray_T Tokens,synOutput;
    char buffer[256];
    fp = fopen("/home/.ishrc", "r");
    while(!feof(fp)){
        fgets(buffer, sizeof(buffer), fp);
        printf("%s\n",buffer);
        Tokens=strToTokens(buffer);
        synOutput=lexToSyn(Tokens);
        printf("--------------------------------\n");
    }
    fclose(fp);
    return 0;
}