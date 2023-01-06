#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());

    } else {
	// creating a loop to make sure the child process prints first without using wait()
	int max = 80000;
	for (int i = 0; i < max; i++) {
            int a = 1;
	}
        // parent goes down this path (original process)
        printf("goodbye, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
	
    }
    return 0;
}
