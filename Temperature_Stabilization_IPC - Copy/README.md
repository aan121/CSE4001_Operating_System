**"""for instructions on how to run these systems please read "readme" on each system folder""""**

an instruction for compiling and running the system is attached in every system folder along with the outputs of each system

----------------------------------------------------

A temperature-stabilization system consists of 5 processes. 
Four external processes that communicate their individual temperatures 
to a central process, which in turn will reply with its own temperature and will indicate whether the entire system has stabilized. 
Each process will receive its initial temperature upon creation and will recalculate a new temperature according to two formulas:


**External processes:**
externalTemp = (3 * externalTemp + 2 * centralTemp) / 5

**Central process:**
centralTemp = (2 * centralTemp + sum) / 6
// when sum is the sum of the external temperatures

**The initial temperatures are hardcoded**

----------------------------------------------------

**In message passing method:**

1- The central will run first and creates the message, then it will wait for external processes to send their messages

2- The external processes will run, create the message and send their temperatures to central

3- central is waiting for external processes messages, when messages are recieved it will start the process of stabilization

4- central will check if system is stable it will reply back to external, print the temperatures and exit, and external will get the message and exit

5- if the system is not stable, it will calculate the new temperatures and send it back to exernal which is waiting for the response

6- external will calculate new temperature and send it back to central which is waiting.

7- as long as the system is not stable this process will repeat it self

// Here I used another variable called cstable which indicates if the system is stable or not, it will get passed with the temperatures

// see readme in /using_message_system for instructions of compiling and running

**The output of message method system:**

![alt text](https://github.com/eribeiroClassroom/fall2022_temperature-stabilization_ipc-aan121/blob/main/using_message_system/message_output.png)

----------------------------------------------------

**In shared memory method:**

1- The central will run first and creates the shared memory segment and attach itself to it, 
then it will wait for external processes to create their segments and attach their self.

2- The external processes will run, create the shared memory segments and attach their self.

3- Now since they all share the same memory it will be hard to send and recieve the data at the same time,
so a while loop is needed to run these processes in order
4- a while loop in central will have the value of 0 and won't break till it beecome 1

5- a while loop in external will have the value of 1 and won't break till it become 0

6- this way central will start checking if the system is stable, if not it will calculate new temperature and change the value to 1 and goes back to the loop

7- external now will break out of loop and calculate new temperature and change the value to 0 and goes back to waiting

8- as long as the system is not stable this process will repeat it self

9- when the system is stable all proceeses will break out of the original loop and print their temperature and exit

// Here I used another variable called econd which indicates if other process is finished or not.

// It will take a couple of seconds for these processes to finish and print their outputs, it's not stuck just wait.

// see readme in /using_shared_memory_system for instructions of compiling and running

**The output of shared memory method system:**

![alt text](https://github.com/eribeiroClassroom/fall2022_temperature-stabilization_ipc-aan121/blob/main/using_shared_memory_system/shared_memory_output.png)

----------------------------------------------------

**In TCP sockets method:**

1- The central will run first and creates the socket, then it will wait for external process to connect and send the data

2- The external process will run, connect to the socket, and send the data to central

3- central is waiting for external process data, when the data are recieved it will start the process of stabilization

4- central will check if system is stable it will reply back to external, print the temperatures and exit, and external will get the message and exit

5- if the system is not stable, it will recalculate the new temperatures and send it back to exernal which is waiting for the response

6- external will recalculate new temperature and send it back to central which is waiting.

7- as long as the system is not stable this process will repeat it self

// Here I used an array to send all the data.

// see readme in /using_sockets_system for instructions of compiling and running

**The output of TCP sockets method system:**

![alt text](https://github.com/eribeiroClassroom/fall2022_temperature-stabilization_ipc-aan121/blob/main/using_sockets_system/sockets_output.png)

----------------------------------------------------

**The general process goes as follows:**

**The process in central:**

central first gets the temperatures of external processes, then it enters a loop till the system is stable.

in the loop it will check if all temperatures are the same.

if they are, it will send to external processes that the system is stable and break out of the loop,
if not it will calculate the new formula and send back the new central temperature.

then it will again gets the new temperature of external processes and check again.

**The process in external:**

external first will send its temperature to central, then it enters a loop till the system is stable.

in the loop it will wait for the central message, when it gets the message it will check if the system is stable or not.

if the system is stable it will break out of the loop,
if not, it will calculate the new temperature and send it back to central and wait again for the response.

when all processes break out of loops they will print their temperatures and exit.
