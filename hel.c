#include<stdio.h>
#include<unistd.h>
int main(){
    printf("df\n");
    fork();
    return 0;
}