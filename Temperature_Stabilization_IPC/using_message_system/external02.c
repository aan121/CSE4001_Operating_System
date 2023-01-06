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
} ext2, cent;

int main() {
    int ext2id, centid, result;
    key_t key;
 
    ext2.temperature = 30;
    ext2.mtype = 2;
    ext2.stable = 0;
  
    key = 2;
    centid = msgget(1000, 0666 | IPC_CREAT);
    ext2id = msgget(key, 0666 | IPC_CREAT);
    
    printf("External 02 Process Starts at Temperature %d \n", ext2.temperature);
  
    while (cent.stable==0) {		
        
        result = msgsnd(centid, &ext2, sizeof(ext2)-sizeof(long), 0);
 
        result = msgrcv(ext2id, &cent, MSGSZ, 2, 0);

        if (cent.stable == 1){
            printf("External 02 Recieved Stabilized Temperature\n");
        }
 
        else { 
            ext2.temperature = 3 * ext2.temperature;
            ext2.temperature = (cent.temperature * 2) + ext2.temperature;
            ext2.temperature = ext2.temperature / 5;
        }
    }
   
    printf("Final External 02 Temperature is %d\n", ext2.temperature);
    printf("Ending External 02 Process.\n");
    result = msgctl(ext2id, IPC_RMID, 0);
    exit(0);
}
