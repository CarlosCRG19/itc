#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();
    
    if (pid == 0) {
        printf("Soy el proceso hijo. PID = %d\n", pid);
    } else {
        printf("Soy el proceso padre. PID = %d\n", pid);
    }
    
    return 0;
}