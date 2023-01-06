#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SHMSZ     1

int main() {
    
    int ctempid = shmget(1000, SHMSZ, 0666|IPC_CREAT);
    int etemp4id = shmget(4, SHMSZ, 0666|IPC_CREAT);
    
    int econd4id = shmget(44, SHMSZ, 0666|IPC_CREAT);
    
    int cstableid = shmget(1111, SHMSZ, 0666|IPC_CREAT);
    
    int *econd4 = (int*) shmat(econd4id, NULL, 0);
    
    int *ctemp = (int*) shmat(ctempid, NULL, 0);
    int *etemp4 = (int*) shmat(etemp4id, NULL, 0);
    
    int *cstable = (int*) shmat(cstableid, NULL, 0);
    
    etemp4[0] = 53;
    cstable[0] = 0;
    econd4[0] = 1;

    printf("External 04 Process Starts at Temperature %d \n", etemp4[0]);
  
    while (cstable[0]==0) {		
        while (econd4[0] == 1) {
            sleep(1);    
        }
        if (cstable[0] == 1){
            printf("External 04 Recieved Stabilized Temperature\n");
        }
 
        else { 
            etemp4[0] = 3 * etemp4[0];
            etemp4[0] = (2 * ctemp[0]) + etemp4[0];
            etemp4[0] = etemp4[0] / 5;
            econd4[0] = 1;
        }
    }
    printf("Final External 04 Temperature is %d\n", etemp4[0]);
    printf("Ending External 04 Process.\n");
    shmdt(econd4);
    shmdt(ctemp);
    shmdt(etemp4);
    shmdt(cstable);
    exit(0);
}
