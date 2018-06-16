#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    FILE *fp;
    char buffer[256];
    fp = fopen("/home/.ishrc", "r");
    while(!feof(fp)){
        fgets(buffer, sizeof(buffer), fp);
        //lexical analize
        printf("%% %s",buffer);

    }
    fclose(fp);
    return 0;
}