#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main( ) 
{
   printf("pps start\n");
   if (fork( ) == 0) {
      execl("/bin/echo", "echo", "hello", NULL);
      fprintf(stderr,"first x"); 
      exit(1);
   }
   printf("pps end\n");
}

