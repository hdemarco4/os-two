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
    if(signum == 1){
        cout << "Signal SIGHUP arrived" << '\n';
    }
    else if(signum == 10){
        cout << "Signal SIGUSR1 arrived" << '\n';
    }   
    else if(signum == 29){
        cout << "Signal SIGIO arrived" << '\n';
    }
    else{
        cout << "I don't know this signal" << '\n';
    }
}

int main(int arge, char** argv)
{
    int f;
    int status;
    int pidp = getpid();
    int pidc;

    struct sigaction *act = new (struct sigaction);
    act->sa_handler = handler;
    sigemptyset (&(act->sa_mask));
    act->sa_flags = 0;
    assert (sigaction (SIGHUP, act, NULL) == 0);

    act->sa_handler = handler;
    sigemptyset (&(act->sa_mask));
    act->sa_flags = 0;
    assert (sigaction (SIGUSR1, act, NULL) == 0);

    act->sa_handler = handler;
    sigemptyset (&(act->sa_mask));
    act->sa_flags = 0;
    assert (sigaction (SIGIO, act, NULL) == 0);


    if ((f = fork()) < 0){
        perror("Error");
    }
    else if (f == 0){
        pidc = getpid();

        kill(pidc, SIGHUP);
        kill(pidc, SIGUSR1);
        kill(pidc, SIGIO);
        kill(pidc, SIGIO);
        kill(pidc, SIGIO);

    }
    else{
        
        waitpid(f, &status, 0);
        
        if(WIFEXITED(status))
            cout << "Process " << f << " exited with status: " << WEXITSTATUS(status) << '\n';
        else
            cout << "Child didn't exit\n";
    }

    delete act;

    return 0;
}
