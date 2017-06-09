#include <signal.h>
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

void handler(int signum)
{
    cout << "Signal " << signum;    
}

int main(int arge, char** argv)
{
    int f;
    int status;
    int pidp = getpid();
    int pidc;
    int signum;

    struct sigaction *a1 = new (struct sigaction);
    a1->sa_handler = handler;
    sigemptyset (&(a1->sa_mask));
    assert (sigaction (signum, a1, NULL) == 0);
    sigaction(SIGHUP, a1);

    struct sigaction *a2 = new (struct sigaction);
    a2->sa_handler = handler;
    sigemptyset (&(a2->sa_mask));
    assert (sigaction (signum, a2, NULL) == 0);
    sigaction(SIGUSR1, a2);

    struct sigaction *a3 = new (struct sigaction);
    a3->sa_handler = handler;
    sigemptyset (&(a3->sa_mask));
    assert (sigaction (signum, a3, NULL) == 0);
    sigaction(SIGIO, a3);

    if ((f = fork()) < 0){
        perror("Error");
    }
    else if (f == 0){
        pidc = getpid;

        kill(pidc, 1);
        kill(pidc, 10);
        kill(pidc, 29);
        kill(pidc, 29);
        kill(pidc, 29);
 
    }
    else{
        
        waitpid(f, &status, 0);
    }


}
