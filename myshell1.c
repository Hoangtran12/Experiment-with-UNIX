#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char comm[100];
    char netID[] = "htt190001";
    char newComm[100];

    while (1) {
        printf("Enter a command: ");
        fgets(comm, sizeof(comm), stdin);
        comm[strcspn(comm, "\n")] = '\0';
        
        if (strcmp(comm, "exit") == 0) {
            printf("Exit\n");
            break;
        } else if (strcmp(comm, "listall") == 0) {
            strcpy(newComm, "ls -la");
        } else if (strcmp(comm, "showme") == 0) {
            sprintf(newComm, "w | grep %.3s", netID);
        } else {
            strcpy(newComm, comm);
        }
        
        system(newComm);
    }
    
    return 0;
}
