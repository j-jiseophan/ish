#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "dynarray.h"
#include "execution.h"
#define MAXARGSIZE 1024

int exeOne(DynArray_T oneCommand){
    pid_t pid;
    int status;
    char **argv;
    argv=(char**)malloc(sizeof(char*)*DynArray_getLength(oneCommand));
    for(int i=1; i<DynArray_getLength(oneCommand); i++){
        argv[i]=DynArray_get(oneCommand,i);
        argv[DynArray_getLength(oneCommand)-1]=NULL;
    }
    
    pid=fork();
    if(pid==0){//in child
        execvp(DynArray_get(oneCommand,0),argv);
        fprintf(stderr, "exec failed\n");
        exit(EXIT_FAILURE);
    }
    //in parent
    wait(&status);
    return 0;
}

int exeAll(DynArray_T allCommands){
    for(int i=0; i<DynArray_getLength(allCommands); i++){
       exeOne(DynArray_get(allCommands,i));
    }
    return 0;
}

