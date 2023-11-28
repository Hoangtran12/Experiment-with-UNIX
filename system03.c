/* fork */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[ ])
{
    int pid0, pid1;
    int i;

    for (i = 1; i < argc; i++){   /* get each argment */
        printf(" ** command = argv[%d]: %s\n", i, argv[i]);
  	   pid0 = fork();

	   if (pid0 == 0) {   // child
		printf(" I am child. rc = pid0 = %d \n", pid0); 
		pid1 = getpid();
		printf(" I am child pid1 = %d \n\n", pid1); 
 		system(argv[i]);		
           return 0;
	   }

         if (pid0 > 0) {   // parent
		pid1 = getpid();
		printf(" ** parent pid1 = %d \n", pid1);
           printf(" ** child  pid0 = %d \n", pid0);
           printf(" ** to loop \n\n"); 
		// back to loop for next command
	    }
	} 
  return 0;
} 

