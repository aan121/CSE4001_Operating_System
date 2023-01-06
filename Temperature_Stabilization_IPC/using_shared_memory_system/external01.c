#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SHMSZ     1

int main() {
    
    int ctempid = shmget(1000, SHMSZ, 0666|IPC_CREAT);
    int etemp1id = shmget(1, SHMSZ, 0666|IPC_CREAT);
    
    int econd1id = shmget(11, SHMSZ, 0666|IPC_CREAT);
    
    int cstableid = shmget(1111, SHMSZ, 0666|IPC_CREAT);
    
    int *econd1 = (int*) shmat(econd1id, NULL, 0);
    
    int *ctemp = (int*) shmat(ctempid, NULL, 0);
    int *etemp1 = (int*) shmat(etemp1id, NULL, 0);
    
    int *cstable = (int*) shmat(cstableid, NULL, 0);
    
    etemp1[0] = 88;
    cstable[0] = 0;
    econd1[0] = 1;

    printf("External 01 Process Starts at Temperature %d \n", etemp1[0]);
  
    while (cstable[0]==0) {		
        while (econd1[0] == 1) {
            sleep(1);    
        }
        if (cstable[0] == 1){
            printf("External 01 Recieved Stabilized Temperature\n");
        }
 
        else { 
            etemp1[0] = 3 * etemp1[0];
            etemp1[0] = (2 * ctemp[0]) + etemp1[0];
            etemp1[0] = etemp1[0] / 5;
            econd1[0] = 1;
        }
    }
    printf("Final External 01 Temperature is %d\n", etemp1[0]);
    printf("Ending External 01 Process.\n");
    shmdt(econd1);
    shmdt(ctemp);
    shmdt(etemp1);
    shmdt(cstable);
    exit(0);
}
