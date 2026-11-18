#include <sys/types.h> 

int main() 
{
   int pid, child, status;
   printf("[%d] pps \n", getpid( ));
   pid = fork();
   if (pid == 0) {
      printf("[%d] sps \n", getpid( ));
      exit(1);
   }
   child = wait(&status); 
   printf("[%d] sps %d end \n", getpid(), child);
   printf("\t end %d\n", status>>8);
}

