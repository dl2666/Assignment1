//
//  main.cpp
//  Assignment1_DianaLevy
//
//  Created by Diana Levy on 9/27/19.
//  Copyright © 2019 Diana Levy. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(int argc, const char * argv[]) {
    pid_t pid;//child process ID
    pid=fork();//child created
    if(pid==0){
        cout<<"In Child process, Child PID = "<<getppid()<<endl;
        cout<<"Enter any command"<<endl;
        char *userCmd = nullptr;
        cin>>userCmd;
        char *args[]={userCmd,NULL};
        execvp(args[0],args);//where new program is run on the newly created child process
        exit(0);
    }
    else if(pid>0){
        wait(NULL);//wait for child process to finish executing
        cout<<"In Parent process, Parent PID = "<<getpid()<<endl;
    }
    else // if a negative PID is returned after the fork, it was not executed correctly 
        cout<<"Fork Error"<<endl;
    return 0;
}
