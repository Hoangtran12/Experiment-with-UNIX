/* This still very simple ls with lstat and stat calls
   for the file information in a directory.

 */

#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char **argv) {

	DIR *dp;
	struct dirent *dirp;

	if (argc != 2) {
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((dp = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "can't open '%s': %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (chdir(argv[1]) == -1) {
		fprintf(stderr, "can't chdir to '%s': %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	//start modifying 

	int fileC = 0;
	int dirC = 0;
	int linkC = 0;
	int otherC = 0;

	while ((dirp = readdir(dp)) != NULL ) {
		struct stat sb;
		if (stat(dirp->d_name, &sb) == -1) {
			fprintf(stderr, "Can't stat %s: %s\n", dirp->d_name,
						strerror(errno));

			if (lstat(dirp->d_name, &sb) == -1) {
				fprintf(stderr,"Can't stat %s: %s\n", dirp->d_name,
						strerror(errno));
				continue;
			}
		}

		printf("%s: ", dirp->d_name);
		if (S_ISREG(sb.st_mode)){
			printf("regular file");
			fileC++;}
		else if (S_ISDIR(sb.st_mode)){
			printf("directory");
			dirC++;}
		else if (S_ISCHR(sb.st_mode))
			printf("character special");
		else if (S_ISBLK(sb.st_mode))
			printf("block special");
		else if (S_ISFIFO(sb.st_mode))
			printf("FIFO");
		else if (S_ISLNK(sb.st_mode)){
			printf("symbolic link");
			linkC++;}
		else if (S_ISSOCK(sb.st_mode))
			printf("socket");
		else
			printf("unknown");
			otherC++;
		printf(" -- with stat\n");

		if (lstat(dirp->d_name, &sb) == -1) {
			fprintf(stderr,"not for stat %s: %s\n", dirp->d_name,
						strerror(errno));
			continue;
		}

		printf("%s: ", dirp->d_name);
		if (S_ISREG(sb.st_mode))
			printf("regular file");
		else if (S_ISDIR(sb.st_mode))
			printf("directory");
		else if (S_ISCHR(sb.st_mode))
			printf("character special");
		else if (S_ISBLK(sb.st_mode))
			printf("block special");
		else if (S_ISFIFO(sb.st_mode))
			printf("FIFO");
		else if (S_ISLNK(sb.st_mode))
			printf("symbolic link");
		else if (S_ISSOCK(sb.st_mode))
			printf("socket");
		else
			printf("unknown");

		printf(" -- with lstat\n\n");
	}
	//display 

	printf("\nTotal counts:\n");
	printf("Regular files: %d\n", fileC);
	printf("Directories: %d\n", dirC);
	printf("Symbolic links: %d\n", linkC);
	printf("Unknown: %d\n", otherC);

	closedir(dp);
	exit(EXIT_SUCCESS);
}