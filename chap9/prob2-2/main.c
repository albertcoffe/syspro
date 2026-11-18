#include <sys/types.h>
	

   int main() 
   {
      int pid1, pid2, child, status;
	
      printf("[%d] pps start \n", getpid( ));
     pid1 = fork();
      if (pid1 == 0) {
	 printf("[%d] sps[1] start \n", getpid( ));
	 sleep(1);
	 printf("[%d] sps[1] end \n", getpid( ));
	 exit(1);
     }
	
	 pid2 = fork();
	 if (pid2 == 0) {
	     printf("[%d] sps #2 start \n", getpid( ));
	     sleep(2);
	     printf("[%d] sps #2 end \n", getpid( ));
	     exit(2);
	 }
	
	 child = waitpid(pid1, &status, 0); 
	 printf("[%d] sps #1 %d end \n", getpid( ), child);
	 printf("\t end code %d\n", status>>8);
	}

