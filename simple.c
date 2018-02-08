#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
	printf("Hello, World!\n");
	pid_t pid;

	sleep(1);
	printf("My PID is %d. My parent's PID is %d.\n",getpid(),getppid());
	return 0;
}