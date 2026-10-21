#include <stdio.h> 
#include "book.h"
int main(int argc, char* argv[]) 
{ 
   struct student rec;
   FILE *fp;
   if (argc != 2) {
      fprintf(stderr, "How to use: %s FileName\n", argv[0]);
      return 1; 
   }
   fp = fopen(argv[1], "w");
   printf("%-9s %-7s %-4s\n", "id", "bookname", "autohor","year","numofborrow","borrow"); 
   fclose(fp);
   return 0;
} 

