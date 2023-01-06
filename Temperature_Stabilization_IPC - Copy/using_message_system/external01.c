#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MSGSZ     128


/*
 * Declare the message structure.
 */
struct {
    long    mtype;
    int    temperature;
    int    stable;
} ext1, cent;

int main() {
    int ext1id, centid, result;
    key_t key;
 
    ext1.temperature = 88;
    ext1.mtype = 2;
    ext1.stable = 0;
  
    key = 1;
    centid = msgget(1000, 0666 | IPC_CREAT);
    ext1id = msgget(key, 0666 | IPC_CREAT);
    
    printf("External 01 Process Starts at Temperature %d \n", ext1.temperature);
  
    while (cent.stable==0) {		
        
        result = msgsnd(centid, &ext1, sizeof(ext1)-sizeof(long), 0);
 
        result = msgrcv(ext1id, &cent, MSGSZ, 2, 0);

        if (cent.stable == 1){
            printf("External 01 Recieved Stabilized Temperature\n");
        }
 
        else { 
            ext1.temperature = 3 * ext1.temperature;
            ext1.temperature = (cent.temperature * 2) + ext1.temperature;
            ext1.temperature = ext1.temperature / 5;
        }
    }
    printf("Final External 01 Temperature is %d\n", ext1.temperature);
    printf("Ending External 01 Process.\n");
    result = msgctl(ext1id, IPC_RMID, 0);
    exit(0);
}
