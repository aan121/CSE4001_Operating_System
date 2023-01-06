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
    int etemp2id = shmget(2, SHMSZ, 0666|IPC_CREAT);
    int etemp3id = shmget(3, SHMSZ, 0666|IPC_CREAT);
    int etemp4id = shmget(4, SHMSZ, 0666|IPC_CREAT);

    int econd1id = shmget(11, SHMSZ, 0666|IPC_CREAT);
    int econd2id = shmget(22, SHMSZ, 0666|IPC_CREAT);
    int econd3id = shmget(33, SHMSZ, 0666|IPC_CREAT);
    int econd4id = shmget(44, SHMSZ, 0666|IPC_CREAT);

    int cstableid = shmget(1111, SHMSZ, 0666|IPC_CREAT);

    int *econd1 = (int*) shmat(econd1id, NULL, 0);
    int *econd2 = (int*) shmat(econd2id, NULL, 0);
    int *econd3 = (int*) shmat(econd3id, NULL, 0);
    int *econd4 = (int*) shmat(econd4id, NULL, 0);

    int *etemp1 = (int*) shmat(etemp1id, NULL, 0);
    int *etemp2 = (int*) shmat(etemp2id, NULL, 0);
    int *etemp3 = (int*) shmat(etemp3id, NULL, 0);
    int *etemp4 = (int*) shmat(etemp4id, NULL, 0);
    int *ctemp = (int*) shmat(ctempid, NULL, 0);

    int *cstable = (int*) shmat(cstableid, NULL, 0);


    ctemp[0] = 44;

    econd1[0] = 0;
    econd2[0] = 0;
    econd3[0] = 0;
    econd4[0] = 0;

    cstable[0] = 0;

    printf("Central Process Starts at Temperature %d \n", ctemp[0]);

    int check = 0;
    while (cstable[0] == 0) {
       // while loop that waits for the external processes to finish
       while ((econd1[0] == 0) || (econd2[0] == 0) || (econd3[0] == 0) || (econd4[0] == 0)) {
           sleep(1);
       }
       int sum = 0;

       sum = etemp1[0] + etemp2[0] + etemp3[0] + etemp4[0];
	    
       if (ctemp[0]==etemp1[0] && ctemp[0]==etemp2[0] && ctemp[0]==etemp3[0] && ctemp[0]==etemp4[0]){
           check++;
       }
 
       if (check==2){
           cstable[0] = 1;
           econd1[0] = 0;
           econd2[0] = 0;
           econd3[0] = 0;
           econd4[0] = 0;
	   printf("System is stable.\n");
       }

       else {
	   ctemp[0] = 2 * ctemp[0];
	   ctemp[0] = ctemp[0] + sum;
	   ctemp[0] = ctemp[0] / 6;
           econd1[0] = 0;
           econd2[0] = 0;
           econd3[0] = 0;
           econd4[0] = 0;
       }
    }
    printf("Final Central Temperature is %d\n", ctemp[0]);
    printf("Final External 01 Temperature is %d\n", etemp1[0]);
    printf("Final External 02 Temperature is %d\n", etemp2[0]);
    printf("Final External 03 Temperature is %d\n", etemp3[0]);
    printf("Final External 04 Temperature is %d\n", etemp4[0]);
    printf("Ending Central Process. \n");
    shmdt(econd1);
    shmdt(econd2);
    shmdt(econd3);
    shmdt(econd4);
    shmdt(etemp1);
    shmdt(etemp2);
    shmdt(etemp3);
    shmdt(etemp4);
    shmdt(ctemp);
    shmdt(cstable);
    shmctl(ctempid, IPC_RMID, NULL);
    shmctl(etemp1id, IPC_RMID, NULL);
    shmctl(etemp2id, IPC_RMID, NULL);
    shmctl(etemp3id, IPC_RMID, NULL);
    shmctl(etemp4id, IPC_RMID, NULL);
    shmctl(econd1id, IPC_RMID, NULL);
    shmctl(econd2id, IPC_RMID, NULL);
    shmctl(econd3id, IPC_RMID, NULL);
    shmctl(econd4id, IPC_RMID, NULL);
    shmctl(cstableid, IPC_RMID, NULL);
    exit(0);
}
