#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	/*printf("Hello, World!\n");*/
	int i = 0;
	int c = 0;
	opterr = 0;
	int pauses = 0;
	int children = 1;
	int levels = 1;
	int stime = -1;
	char *end;

	/* Check for a usage string option */
	for(i=0;i<argc;i++) {
		if(strstr(argv[i],"-u") != NULL) {
			fprintf(stderr, "This program demonstrates creating child processes of N recursive levels and M children per level\n");
			fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\n");
			return(1);
		}
	}

	/* Argument Parsing */
	while((c = getopt(argc, argv, "uN:M:ps:")) != -1) {
		switch(c)
		{
			case 'u':
				/* printf("You said u. But technically we should have exited by now. Whoops.\n"); */
				break;
			case 'N':
				/* printf("Levels: %s \n", optarg); */
				levels = (int)strtol(optarg, &end, 10);
				if(*end) {
					fprintf(stderr, "Bad input detected. ASCII value: %d. Try again.\n", (int)(*end));
					fprintf(stderr, "This program demonstrates creating child processes of N recursive levels and M children per level\n");
					fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\n");
					exit(1);
				}
				break;
			case 'M':
				/* printf("Children: %s \n", optarg); */
				children = (int)strtol(optarg, &end, 10);
				if(*end) {
					fprintf(stderr, "Bad input detected. ASCII value: %d. Try again.\n", (int)(*end));
					fprintf(stderr, "This program demonstrates creating child processes of N recursive levels and M children per level\n");
					fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\n");
					exit(1);
				}
				break;
			case 'p':
				/* printf("Pausing Requested\n"); */
				pauses = 1;
				break;
			case 's':
				/* printf("Sleep Time (s): %s\n", optarg); */
				stime = (int)strtol(optarg, &end, 10);
				if(*end) {
					fprintf(stderr, "Bad input detected. ASCII value: %d. Try again.\n", (int)(*end));
					fprintf(stderr, "This program demonstrates creating child processes of N recursive levels and M children per level\n");
					fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\n");
					exit(1);
				}
				break;
			case '?':
				fprintf(stderr, "Missing argument. Try again.\n");
				fprintf(stderr, "This program demonstrates creating child processes of N recursive levels and M children per level\n");
				fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\n");
				exit(1);
				break;
		}
	}

	/* Input Checking */
	if(pauses) {
		if(stime != -1) {
			fprintf(stderr, "Cannot use -p and -s simultaneously.\n");
			fprintf(stderr, "This program demonstrates creating child processes of N recursive levels and M children per level\n");
			fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\n");
			exit(1);
		}
	} else if(stime == -1) {
		stime = 1;
	}
	if(levels > 4) {
		fprintf(stderr, "Cannot have more than 4 levels\n");
		fprintf(stderr, "This program demonstrates creating child processes of N recursive levels and M children per level\n");
		fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\n");
		exit(1);
	}
	if(children > 3) {
		fprintf(stderr, "Cannot have more than 3 children\n");
		fprintf(stderr, "This program demonstrates creating child processes of N recursive levels and M children per level\n");
		fprintf(stderr, "prog2tree [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]\n");
		exit(1);
	}

	char levelBuffer [8];
	sprintf(levelBuffer, "%d", levels);
	char childBuffer [8];
	sprintf(childBuffer, "%d", children);
	char stimeBuffer [8];
	sprintf(stimeBuffer, "%d", stime);

	/* Recursive Execution */
	printf("ALIVE: Level %d process with pid=%d, child of ppid=%d\n", levels, getpid(), getppid());
	pid_t spid = getpid();
	if(levels>1) {
		pid_t pid;
		for(i=0;i<children;i++) {
			if(getpid() == spid) {
				pid = fork();
			}
		}
		if(pid < 0) { /* error */
			fprintf(stderr, "Fork failed");
			return 1;
		}
		if(pid == 0) { /*child process */
			/* printf("I'm the child!\n"); */
			levels = levels - 1;
			sprintf(levelBuffer, "%d", levels);

			if(pauses) {
				char *argv2[] = { "./prog2tree", "-M", childBuffer, "-N", levelBuffer, "-p", NULL };
				levels = levels + 1;
				execv("./prog2tree", argv2);
			} else {
				char *argv2[] = { "./prog2tree", "-M", childBuffer, "-N", levelBuffer, "-s", stimeBuffer, NULL };
				levels = levels + 1;
				execv("./prog2tree", argv2);
			}
		} else { /* Parent Process */
			/* Parent will wait for the child to complete */
			for(i=0;i < levels*children-1;i++) {
				wait(NULL);
			}
			/* printf("Child Complete\n"); */
		}
	} else {
		if(stime != -1) {
			sleep(stime);
		} else {
			pause();
		}
	}
	printf("EXITING: Level %d process with pid=%d, child of ppid=%d\n", levels, getpid(), getppid());
	
	return 0;
}