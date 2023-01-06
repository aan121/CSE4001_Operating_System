#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int value = 100;
    printf("hello world (pid:%d)\n", (int) getpid());
    printf("The value of the variable before the process is %d\n", value);
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
	printf("The value of the variable in the child is %d\n", value);
	printf("Changing the value in the child to 150\n");
	value = 150;
	printf("New value of the variable in the child is %d\n", value);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
	printf("The value of the variable in the parent is %d\n", value);
	printf("Changing the value in the parent to 200\n");
	value = 200;
	printf("New value of the variable in the parent is %d\n", value);
    }
    return 0;
}
