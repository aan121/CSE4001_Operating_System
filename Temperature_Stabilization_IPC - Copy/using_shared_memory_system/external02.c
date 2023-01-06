#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SHMSZ     1

int main() {
    
    int ctempid = shmget(1000, SHMSZ, 0666|IPC_CREAT);
    int etemp2id = shmget(2, SHMSZ, 0666|IPC_CREAT);
    
    int econd2id = shmget(22, SHMSZ, 0666|IPC_CREAT);
    
    int cstableid = shmget(1111, SHMSZ, 0666|IPC_CREAT);
    
    int *econd2 = (int*) shmat(econd2id, NULL, 0);
    
    int *ctemp = (int*) shmat(ctempid, NULL, 0);
    int *etemp2 = (int*) shmat(etemp2id, NULL, 0);
    
    int *cstable = (int*) shmat(cstableid, NULL, 0);
    
    etemp2[0] = 30;
    cstable[0] = 0;
    econd2[0] = 1;

    printf("External 02 Process Starts at Temperature %d \n", etemp2[0]);
  
    while (cstable[0]==0) {		
        while (econd2[0] == 1) {
            sleep(1);    
        }
        if (cstable[0] == 1){
            printf("External 02 Recieved Stabilized Temperature\n");
        }
 
        else { 
            etemp2[0] = 3 * etemp2[0];
            etemp2[0] = (2 * ctemp[0]) + etemp2[0];
            etemp2[0] = etemp2[0] / 5;
            econd2[0] = 1;
        }
    }
    printf("Final External 02 Temperature is %d\n", etemp2[0]);
    printf("Ending External 02 Process.\n");
    shmdt(econd2);
    shmdt(ctemp);
    shmdt(etemp2);
    shmdt(cstable);
    exit(0);
}
