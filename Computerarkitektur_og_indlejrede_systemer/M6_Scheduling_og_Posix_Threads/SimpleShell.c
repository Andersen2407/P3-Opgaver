#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){
    int status, pid;
    char kommando[80];
    while (1) {
        printf("ppmshell>");
        scanf("%s",kommando);
        pid = fork();

        if (pid != 0){
            printf("\n");
            printf("%d", pid); // <- PID
            printf("\n");

            while(wait(&status) != pid);
        }
        else{
            execlp(kommando, (char *)NULL);
        } 
    }
}
