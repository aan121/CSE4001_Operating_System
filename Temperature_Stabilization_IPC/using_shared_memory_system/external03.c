#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SHMSZ     1

int main() {
    
    int ctempid = shmget(1000, SHMSZ, 0666|IPC_CREAT);
    int etemp3id = shmget(3, SHMSZ, 0666|IPC_CREAT);
    
    int econd3id = shmget(33, SHMSZ, 0666|IPC_CREAT);
    
    int cstableid = shmget(1111, SHMSZ, 0666|IPC_CREAT);
    
    int *econd3 = (int*) shmat(econd3id, NULL, 0);
    
    int *ctemp = (int*) shmat(ctempid, NULL, 0);
    int *etemp3 = (int*) shmat(etemp3id, NULL, 0);
    
    int *cstable = (int*) shmat(cstableid, NULL, 0);
    
    etemp3[0] = 36;
    cstable[0] = 0;
    econd3[0] = 1;

    printf("External 03 Process Starts at Temperature %d \n", etemp3[0]);
  
    while (cstable[0]==0) {		
        while (econd3[0] == 1) {
            sleep(1);    
        }
        if (cstable[0] == 1){
            printf("External 03 Recieved Stabilized Temperature\n");
        }
 
        else { 
            etemp3[0] = 3 * etemp3[0];
            etemp3[0] = (2 * ctemp[0]) + etemp3[0];
            etemp3[0] = etemp3[0] / 5;
            econd3[0] = 1;
        }
    }
    printf("Final External 03 Temperature is %d\n", etemp3[0]);
    printf("Ending External 03 Process.\n");
    shmdt(econd3);
    shmdt(ctemp);
    shmdt(etemp3);
    shmdt(cstable);
    exit(0);
}
