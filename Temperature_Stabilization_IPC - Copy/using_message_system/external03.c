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
} ext3, cent;

int main() {
    int ext3id, centid, result;
    key_t key;
 
    ext3.temperature = 36;
    ext3.mtype = 2;
    ext3.stable = 0;
  
    key = 3;
    centid = msgget(1000, 0666 | IPC_CREAT);
    ext3id = msgget(key, 0666 | IPC_CREAT);
    
    printf("External 03 Process Starts at Temperature %d \n", ext3.temperature);
  
    while (cent.stable==0) {		
        
        result = msgsnd(centid, &ext3, sizeof(ext3)-sizeof(long), 0);
 
        result = msgrcv(ext3id, &cent, MSGSZ, 2, 0);

        if (cent.stable == 1){
            printf("External 03 Recieved Stabilized Temperature\n");
        }
 
        else { 
            ext3.temperature = 3 * ext3.temperature;
            ext3.temperature = (cent.temperature * 2) + ext3.temperature;
            ext3.temperature = ext3.temperature / 5;
        }
    }
   
    printf("Final External 03 Temperature is %d\n", ext3.temperature);
    printf("Ending External 03 Process.\n");
    result = msgctl(ext3id, IPC_RMID, 0);
    exit(0);
}
