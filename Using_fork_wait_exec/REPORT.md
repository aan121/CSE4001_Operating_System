Q1. Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?

A1. Changing the variable in Parent does not affect the variable in Child and vice versa, they both have seperate copies.

see answer1.c for code and outputanswer1.png for output.

-------------------------------------------------------------

Q2. Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?

A2. Both share the same discriptor and can write to the file but in random order.

see answer2.c for code, outputanswer2.png for output and output2.txt for the text file.

-------------------------------------------------------------

Q3. Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

A3. It can be done using wait() but I used a long for loop as an alternative way to make sure the child prints first.

see answer3.c for code and outputanswer3.png for output.

-------------------------------------------------------------

Q4. Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?

A4. Because execv and execl can excute commands given a path, execvp and execlp can excute commands given the name of command within a path, and execvpe and execle can excute commands within a specific enviroment.

see answer4.c for code and outputanswer4.png for output.

-------------------------------------------------------------

Q5. Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?

A5. wait() returns -1 when used in parent and returns the PID of the child when used in child.

see answer5_1.c and answer5_2.c for codes and outputanswer5.png for output.

-------------------------------------------------------------

Q6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?

A6. waitpid() is useful when we want to wait for a specific process of child.

see answer6.c for code and outputanswer6.png for output.

-------------------------------------------------------------

Q7. Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?

A7. Theere would be no output if we don't open a file in order to send the output there.

see answer7.c for code, outputanswer7.png for output and output7.txt for the text file.
