#include <stdio.h>
#include <unistd.h>

int main()
{ 
   int pid;
   printf("[%d] ps start \n", getpid());
   pid = fork();
   printf("[%d] ps : re %d\n", getpid(), pid);
}

