#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

int main(){

    int x,y,z, fd[2],fd_1[2],fd_2[2], ph, ph2, ph3;

    pipe(fd);
    pipe(fd_1);
    pipe(fd_2);

    cout << "Dame el valor de x: ";
    cin >> x;
    cout << "Dame el valor de y: ";
    cin >> y;
    cout << "Dame el valor de z: ";
    cin >> z;

    if((ph = fork()) == 0){
        int suma;
        sleep(1);
        suma=x+y+z;
        write(fd[1],&suma,sizeof(suma));
        exit(0);
    } else { 
        if((ph2 = fork()) == 0){
            int multi;
            sleep(1);
            multi= (x+y)*z;
            write(fd_1[1],&multi,sizeof(multi));
            exit(0);
        } else {
            if((ph3 = fork()) == 0){
                int div;
                sleep(1);
                div=(x+y)/z;
                write(fd_2[1],&div,sizeof(div));
                exit (0);
            } else {
                int res1,res2,res3;
                read(fd[0],&res1,sizeof(res1));
                read(fd_1[0],&res2,sizeof(res2));
                read(fd_2[0],&res3,sizeof(res3));
                waitpid(ph,NULL,0);
                waitpid(ph2,NULL,0);
                waitpid(ph3,NULL,0);
                write(fd[1],&res1,sizeof(res1));
                write(fd_1[1],&res2,sizeof(res2));
                write(fd_2[1],&res3,sizeof(res3));

                cout << "Suma: "<< res1<< endl;
                cout << "Multiplicacion: "<< res2<< endl;
                cout << "Division: "<< res3<< endl;
                
            }
        }
    }
    return 0;
}