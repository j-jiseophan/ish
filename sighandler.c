#include "sighandler.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handleSIGQUIT(int signo){
    printf("Type Ctrl-\\ again within seconds to exit.\n");
    fflush(NULL);
    printf("helloworld\n");
    alarm(5);
    signal(SIGQUIT,SIG_DFL);

}
void handleSIGALRM(int signo){
    signal(SIGQUIT,handleSIGQUIT);
}