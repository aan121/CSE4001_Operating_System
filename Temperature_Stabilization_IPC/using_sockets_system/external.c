#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#define SIZE 6
#define PORT 8080

int main() {
    
    int external_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int stat = connect(external_socket, (struct sockaddr *) & server_address, sizeof(server_address));
    
    int edata[SIZE]; 
    int data[SIZE];
    edata[0] = 44;
    edata[1] = 88;
    edata[2] = 30;
    edata[3] = 36;
    edata[4] = 53;
    edata[5] = 0;
    int x;
    
    printf("External 01 Process Starts at Temperature %d \n", edata[1]);
    printf("External 02 Process Starts at Temperature %d \n", edata[2]);
    printf("External 03 Process Starts at Temperature %d \n", edata[3]);
    printf("External 04 Process Starts at Temperature %d \n", edata[4]);
  
    while (edata[5]==0) {		
        for (int i = 0; i < 6; i++) {
            data[i] = edata[i];
        }
        send(external_socket, data, sizeof(data), 0);
 
        recv(external_socket, &data, sizeof(data), 0);
        for (int j = 0; j < 6; j++) {
            edata[j] = data[j];
        }

        if (edata[5] == 1){
            printf("External 01 Recieved Stabilized Temperature\n");
            printf("External 02 Recieved Stabilized Temperature\n");
            printf("External 03 Recieved Stabilized Temperature\n");
            printf("External 04 Recieved Stabilized Temperature\n");
        }
 
        else { 
            edata[1] = 3 * edata[1];
            edata[1] = (edata[0] * 2) + edata[1];
            edata[1] = edata[1] / 5;
            
            edata[2] = 3 * edata[2];
            edata[2] = (edata[0] * 2) + edata[2];
            edata[2] = edata[2] / 5;
            
            edata[3] = 3 * edata[3];
            edata[3] = (edata[0] * 2) + edata[3];
            edata[3] = edata[3] / 5;
            
            edata[4] = 3 * edata[4];
            edata[4] = (edata[0] * 2) + edata[4];
            edata[4] = edata[4] / 5;
        }
    }
    printf("Final External 01 Temperature is %d\n", edata[1]);
    printf("Final External 02 Temperature is %d\n", edata[2]);
    printf("Final External 03 Temperature is %d\n", edata[3]);
    printf("Final External 04 Temperature is %d\n", edata[4]);
    printf("Ending External 01 Process.\n");
    printf("Ending External 02 Process.\n");
    printf("Ending External 03 Process.\n");
    printf("Ending External 04 Process.\n");
    close(external_socket);
    exit(0);
}
