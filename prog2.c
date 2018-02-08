#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
	printf("Hello, World!\n");
	pid_t pid;



	pid = fork();
	if(pid < 0) { /* error */
		fprintf(stderr, "Fork failed");
		return 1;
	}
	if(pid == 0) { /*child process */
		printf("I'm the child!\n");
		char *argv[] = { "./simple", NULL };
		execv("./simple", argv);
	} else { /* Parent Process */
		/* Parent will wait for the child to complete */
		wait(NULL);
		printf("Child Complete\n");
	}

	return 0;
}