#include <stdio.h>
 #include <unistd.h>

 int main()
 {    
     printf("number: [%d] \n", getpid());
     printf("pnumber: [%d] \n", getppid());
 }

