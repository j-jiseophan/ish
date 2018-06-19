#include "sighandler.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handleSIGQUIT(int signo){
    printf("Type Ctrl-\\ again within seconds to exit.\n");
    printf("%% ");
    fflush(NULL);
    alarm(5);
    signal(SIGQUIT,SIG_DFL);
    return;

}
void handleSIGALRM(int signo){
    signal(SIGQUIT,handleSIGQUIT);
}