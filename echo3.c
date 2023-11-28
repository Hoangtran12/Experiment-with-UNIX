#include <stdio.h>
#include <stdlib.h>

int main()
{
    char msg[100];
    
    printf("Please enter Any String or Message = ");
    fgets(msg, sizeof msg, stdin);

    printf("The string that you entered = %s\n", msg);
    
    return 0;
}