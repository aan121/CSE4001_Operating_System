
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#define SIZE 6
#define PORT 8080

int main() {
    	
    int central_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(central_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(central_socket, 5);
    int external_socket = accept(central_socket, NULL, NULL);

    int cdata[SIZE]; 
    int data[SIZE];
	
    cdata[0] = 44;
    cdata[5] = 0;
    int x;
    
    printf("Central Process Starts at Temperature %d \n", cdata[0]);
   
    int check = 0;
    while (cdata[5] == 0) {
       int sum = 0;
       
       recv(external_socket, &data, sizeof(data), 0);
       for (int i = 0; i < 6; i++) {
           cdata[i] = data[i];
       }
	    
       sum = cdata[1] + cdata[2] + cdata[3] + cdata[4];
       if (cdata[0]==cdata[1] && cdata[0]==cdata[2] && cdata[0]==cdata[3] && cdata[0]==cdata[4]){
           check++;
       }

       if (check==2){ 
           cdata[5] = 1;
	   printf("System is stable.\n");
	   for (int j = 0; j < 6; j++) {
               data[j] = cdata[j];
	   }
	   send(external_socket, data, sizeof(data), 0);
       }
       
       else { 
	   cdata[0] = 2 * cdata[0];
	   cdata[0] = cdata[0] + sum;
	   cdata[0] = cdata[0] / 6;
	   for (int a = 0; a < 6; a++) {
               data[a] = cdata[a];
	   }
	   send(external_socket, data, sizeof(data), 0);
       }
    }
    printf("Final Central Temperature is %d\n", cdata[0]);
    printf("Final External 01 Temperature is %d\n", cdata[1]);
    printf("Final External 02 Temperature is %d\n", cdata[2]);
    printf("Final External 03 Temperature is %d\n", cdata[3]);
    printf("Final External 04 Temperature is %d\n", cdata[4]);
    printf("Ending Central Process. \n");
    close(central_socket);
    exit(0);
}
