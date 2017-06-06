#include <signal.h>
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int arge, char** argv)
{
    int f;
    int status;

    if ((f = fork()) < 0){
        perror("Error");
    }
    else if (f == 0){
        
    }
    else{
        waitpid(f, &status, 0);
    }


}
