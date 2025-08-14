#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

int main (){

int fd[2];
char buffer[12]={};
int a,b;

pipe(fd);

if ((a = fork())==0){
    sleep(1);
    read(fd[0],&buffer,3);
    buffer[3] = 'd';
    buffer[4] = 'e';
    buffer[5] = 'f';
    write(fd[1], &buffer,6); 
    exit(0);
} else {
    if ((b = fork())==0){
        sleep(1);
        read(fd[0],&buffer,6);
        buffer[6] = 'f';
        buffer[7] = 'e';
        buffer[8] = 'd';
        buffer[9] = 'c';
        buffer[10] = 'b';
        buffer[11] = 'a';
        write(fd[1],&buffer,12);
        sleep(1);
        exit(0);
    } else {    
        buffer[0] = 'a';
        buffer[1] = 'b';
        buffer[2] = 'c';}
        write(fd[1],&buffer,3);
        waitpid(a, NULL, 0);
        waitpid(b, NULL, 0);
        read(fd[0],&buffer,12);    
        cout<< "P: " << buffer<< endl;
    }
return 0;
}