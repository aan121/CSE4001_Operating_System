#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>


#define MSGSZ     128


 /*
 * Declare the message structure.
 */

struct {
    long    mtype;
    int    temperature;
    int    stable;
} ext1, ext2, ext3, ext4, cent;


int main() {
    int ext1id, ext2id, ext3id, ext4id, centid, result;
    key_t key;
    
    cent.temperature = 44;
    cent.mtype = 2;
    cent.stable = 0;

    key = 1000;
    centid = msgget(key, 0666 | IPC_CREAT);

    ext1id = msgget(1, 0666 | IPC_CREAT);
    ext2id = msgget(2, 0666 | IPC_CREAT);
    ext3id = msgget(3, 0666 | IPC_CREAT);
    ext4id = msgget(4, 0666 | IPC_CREAT);
    
    printf("Central Process Starts at Temperature %d \n", cent.temperature);
   
    int check = 0;
    while (cent.stable == 0) {
       int sum = 0;
       
       result = msgrcv(centid, &ext1, MSGSZ, 2, 0);     
       result = msgrcv(centid, &ext2, MSGSZ, 2, 0);
       result = msgrcv(centid, &ext3, MSGSZ, 2, 0);
       result = msgrcv(centid, &ext4, MSGSZ, 2, 0);
       sum = ext1.temperature + ext2.temperature + ext3.temperature + ext4.temperature;
       
       if (cent.temperature==ext1.temperature && cent.temperature==ext2.temperature && cent.temperature==ext3.temperature && cent.temperature==ext4.temperature){
           check++;
       }
	    
       if (check==2){ 
           cent.stable = 1;
	   printf("System is stable.\n");
          
	   result = msgsnd(ext1id, &cent, sizeof(cent)-sizeof(long), 0);
           result = msgsnd(ext2id, &cent, sizeof(cent)-sizeof(long), 0);
           result = msgsnd(ext3id, &cent, sizeof(cent)-sizeof(long), 0);
           result = msgsnd(ext4id, &cent, sizeof(cent)-sizeof(long), 0);
       }
       
       else { 
	   cent.temperature = 2 * cent.temperature;
	   cent.temperature = cent.temperature + sum;
	   cent.temperature = cent.temperature / 6;
	   result = msgsnd(ext1id, &cent, sizeof(cent)-sizeof(long), 0);
           result = msgsnd(ext2id, &cent, sizeof(cent)-sizeof(long), 0);
           result = msgsnd(ext3id, &cent, sizeof(cent)-sizeof(long), 0);
           result = msgsnd(ext4id, &cent, sizeof(cent)-sizeof(long), 0);
       }
    }
    printf("Final Central Temperature is %d\n", cent.temperature);
    printf("Final External 01 Temperature is %d\n", ext1.temperature);
    printf("Final External 02 Temperature is %d\n", ext2.temperature);
    printf("Final External 03 Temperature is %d\n", ext3.temperature);
    printf("Final External 04 Temperature is %d\n", ext4.temperature);
    printf("Ending Central Process. \n");
    result = msgctl(centid, IPC_RMID, 0);
    exit(0);
}
