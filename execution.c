#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "dynarray.h"
#include "execution.h"
#define MAXARGSIZE 1024

int exeOne(DynArray_T oneCommand){
    pid_t pid;
    int status;
    char **argv;
    char *commandName;
    argv=(char**)calloc(sizeof(char*),1+DynArray_getLength(oneCommand));
    for(int i=0; i<DynArray_getLength(oneCommand); i++){
        argv[i]=DynArray_get(oneCommand,i);
    }
    argv[DynArray_getLength(oneCommand)]=NULL;
    commandName=DynArray_get(oneCommand,0);
    if(!strcmp(commandName,"setenv")){//four built-in commands
        
        if((argv[2]!=NULL&&argv[3]!=NULL) || argv[1]==NULL){ //invalid number of argument
            perror("./sampleish: setenv takes one or two parameters\n");
            return 0;
        }
        if(argv[2]!=NULL){//ordinary case
            if(setenv(argv[1],argv[2],1)!=0){
                perror("error occured in setenv command\n");
            }
        }
        else{
            if(setenv(argv[1],"",1)==-1){
                perror("error occured in setenv command\n");
            }
        }
    }
    else if(!strcmp(commandName,"unsetenv")){
        if(argv[2]!=NULL || argv[1]==NULL){ //invalid number of argument
            perror("./sampleish: unsetenv takes one parameter\n");
            return 0;
        }
        if(unsetenv(argv[1])!=0){
            perror("error occured in unsetenv command\n");
        }
    }
    else if(!strcmp(commandName,"cd")){
        if(argv[2]!=NULL || argv[1]==NULL){ //invalid number of argument
            perror("./sampleish: cd takes one parameter\n");
            return 0;
        }
        if(chdir(argv[1])!=0){
            perror("error occured in cd command\n");
        }
    }
    else if(!strcmp(commandName,"exit")){
        if(argv[1]!=NULL){ //invalid number of argument
            perror("./sampleish: exit does not take any parameters\n");
            return 0;
        }
        exit(0);
    }
    else{//not built-in command
        fflush(NULL);
        pid=fork();
        if(pid==0){//in child
            signal(SIGINT,SIG_DFL);
            signal(SIGQUIT, SIG_IGN);
            //printf("i will run : %s\n",commandName);
            execvp(commandName,argv);
            fprintf(stderr,"%s: No such file or directory\n",commandName);
            exit(EXIT_FAILURE);
        }
        //in parent
        wait(&status);
    }
    free(argv);
    argv=NULL;
    return 0;
}

int exeAll(DynArray_T allCommands){
    for(int i=0; i<DynArray_getLength(allCommands); i++){
       exeOne(DynArray_get(allCommands,i));
    }

    for(int i=0; i<DynArray_getLength(allCommands); i++){
       for(int j=0; j<DynArray_getLength(DynArray_get(allCommands,i));j++){
           free(DynArray_get(DynArray_get(allCommands,i),j));
       }
       DynArray_free(DynArray_get(allCommands,i));
    }
    DynArray_free(allCommands);
    return 0;
}

