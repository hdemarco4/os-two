#include <signal.h>
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main(int arge, char** argv)
{
    int f;
    int status;

    struct sigaction *action = new (struct sigaction);
    action->sa_handler = handler;
    sigemptyset (&(action->sa_mask));
    assert (sigaction (signum, action, NULL) == 0);

    if ((f = fork()) < 0){
        perror("Error");
    }
    else if (f == 0){
        execl("./child", "child", (char*)NULL);
     
    }
    else{
        waitpid(f, &status, 0);
    }


}


int child()
{
    

}
