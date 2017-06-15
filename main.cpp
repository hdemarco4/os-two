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

    struct sigaction *a1 = new (struct sigaction);
    a1->sa_handler = handler;
    sigemptyset (&(a1->sa_mask));
    a1->sa_flags = 0;
    assert (sigaction (SIGHUP, a1, NULL) == 0);
    sigaction(SIGHUP, a1, NULL);

    struct sigaction *a2 = new (struct sigaction);
    a2->sa_handler = handler;
    sigemptyset (&(a2->sa_mask));
    a2->sa_flags = 0;
    assert (sigaction (SIGUSR1, a2, NULL) == 0);
    sigaction(SIGUSR1, a2, NULL);

    struct sigaction *a3 = new (struct sigaction);
    a3->sa_handler = handler;
    sigemptyset (&(a3->sa_mask));
    a3->sa_flags = 0;
    assert (sigaction (SIGIO, a3, NULL) == 0);
    sigaction(SIGIO, a3, NULL);

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

    delete a1;
    delete a2;
    delete a3;

    return 0;
}
