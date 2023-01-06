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
} ext4, cent;

int main() {
    int ext4id, centid, result;
    key_t key;
 
    ext4.temperature = 53;
    ext4.mtype = 2;
    ext4.stable = 0;
  
    key = 4;
    centid = msgget(1000, 0666 | IPC_CREAT);
    ext4id = msgget(key, 0666 | IPC_CREAT);
    
    printf("External 04 Process Starts at Temperature %d \n", ext4.temperature);
  
    while (cent.stable==0) {		
        
        result = msgsnd(centid, &ext4, sizeof(ext4)-sizeof(long), 0);
 
        result = msgrcv(ext4id, &cent, MSGSZ, 2, 0);

        if (cent.stable == 1){
            printf("External 04 Recieved Stabilized Temperature\n");
        }
 
        else { 
            ext4.temperature = 3 * ext4.temperature;
            ext4.temperature = (cent.temperature * 2) + ext4.temperature;
            ext4.temperature = ext4.temperature / 5;
        }
    }
   
    printf("Final External 04 Temperature is %d\n", ext4.temperature);
    printf("Ending External 04 Process.\n");
    result = msgctl(ext4id, IPC_RMID, 0);
    exit(0);
}
