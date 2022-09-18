/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>

void readInput(char *buffer);
void execute(char *buffer);
void childProcess(char *buffer);

int main(){
    char *buffer;
    size_t bufsize = 32;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL){
        perror("Unable to allocate buffer");
        exit(1);
    }

    while (1) {                   /* repeat until done ....         */
        printf("Type something: ");
        characters = getline(&buffer,&bufsize,stdin);
        printf("\nYou typed: %s",buffer);
        
        if(strcmp(buffer,"exit\n")==0){
            break;
        }
        
        readInput(buffer);
        
        printf("\n");
        
     }
    printf("exiting");
    return(0);
}

void readInput(char *buffer){
    char* token = strtok(buffer, "|");
    while (token!= NULL){
        printf ("readInput: %s\n",token);
        execute(token);
        token = strtok (NULL, "|");
  }
}

void execute(char *token){
    printf("execute running with token: %s\n", token);
    pid_t childPid;  // the child process that the execution will soon run inside of. 
    childPid = fork();
    
    if(childPid == 0)  // fork succeeded 
    {   
       // Do something
       childProcess(token);
       exit(0); 
    }
    
    else if(childPid < 0)  // fork failed 
    {    
        printf("Some error happened.\n");    // log the error
       
    }
    
    else  // Main (parent) process after fork succeeds 
    {    
        int returnStatus;    
        waitpid(childPid, &returnStatus, 0);  // Parent process waits here for child to terminate.
    
        if (returnStatus == 0)  // Verify child process terminated without error.  
        {
           printf("The child process terminated normally.\n");    
        }
    
        if (returnStatus == 1)      
        {
           printf("The child process terminated with an error!.\n");    
        }
    }
}

void childProcess(char *token){
    printf("childProcess running execvp %s\n", token);
    sleep(2);
}
