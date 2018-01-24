#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <pthread.h>
#include <string.h>

int PORT = 4659;

void * connThread(void *socketId) {
    char msg[1024];
    int client_descriptor, recv_len;
    client_descriptor = (uintptr_t) socketId;
    printf("NEw Connection Thread on [%d]\n", client_descriptor);
    send(client_descriptor, "0.6", 3, MSG_DONTWAIT); 
    if ((recv_len = recv(client_descriptor, msg, 1024, 0)) < 0) { 
        perror("failed to recv"); 
    } else { 
        if (recv_len <= 0){
            pthread_exit(NULL);
        }
        msg[recv_len] = '\0'; 
        printf("[%d] %s\n", recv_len, msg); 
        if (strcmp("yes", msg) == 0){
            printf("CLIENT OUTDATED, UPDATING\n");
            FILE *f = fopen("client.c", "rb");
            fseek(f, 0, SEEK_END);
            int fsize = ftell(f);
            fseek(f, 0, SEEK_SET);  //same as rewind(f);

            char *string = malloc(fsize + 1);
            fread(string, fsize, 1, f);
            fclose(f);
            
            send(client_descriptor, &fsize, 4, MSG_DONTWAIT);
            send(client_descriptor, string, fsize, 0);
        }
    } 
    while (1){ 
        if ((recv_len = recv(client_descriptor, msg, 1024, 0)) < 0) { 
            perror("failed to recv"); 
        } else { 
            if (recv_len <= 0){
                pthread_exit(NULL);
            }
            msg[recv_len] = '\0'; 
            printf("[%d] %s\n", recv_len, msg); 
        } 
    }

}

int main(){
    int counter = 0;
    int main_socket, recv_len;
    struct sockaddr_in server_address; 
    pthread_t threads[40];
    if ((main_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror("FAILED TO OPEN MAIN SOCKET");

    int option = 1;
    setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    bzero((char *) &server_address, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    int potatoe = bind(main_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr_in));

    if (potatoe < 0)
        perror("FAILED TO BIND");

    if ((listen(main_socket, 40)) < 0)
        perror("FAILED TO LISTEN");

    int client_descriptor;
    struct sockaddr_in client_address;
    socklen_t client_address_size;
    while(counter+1){
        if ((client_descriptor = accept(main_socket, (struct sockaddr *) &client_address, &client_address_size)) < 0){
            perror("Could not accept");
        } else {
            printf("received connection [%d]\n", client_descriptor);
            if (pthread_create(&threads[counter], NULL, connThread, (void *) client_descriptor) > 0)
                perror("FAILED TO CREATE THREAD");
            counter++;
        }
    
    }
}
