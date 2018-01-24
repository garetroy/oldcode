/*
    client.c
    Author: Garett Roberts

    A basic self updating client that will do various things.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORT 4659
#define VERSION "0.6"

void
getUpdate(int sock)
{
    FILE *fp;
    int  bytesreceived = 0;
    int  left          = 0;
    int  len           = 1;
    char recvbuff[256] = {'\0'};

    fp = fopen("clientNew.c","w+");
    if(fp == NULL)
    {
        perror("Failed to open client.c");
        exit(1);
    }

    //Get Filesize
    recv(sock, &bytesreceived, 4, 0);
    left = (int) bytesreceived;

    //Keep getting info from file, until there is no more to get
    while(((left > 0) && (len = recv(sock,recvbuff, 1, 0)) > 0))
    {
        fwrite(recvbuff, sizeof(char), len, fp);
        left -= len;
    }

    if(bytesreceived < 0)
    {
        perror("Read failure");
        fclose(fp);
        exit(1);
    }
    fclose(fp);
}

void
applyUpdate(void)
{
    if(system("./patch") < 0)
    {
        perror("System call failed");
        exit(1);
    }
}

void
recieveMessage(int sock, char *out)
{
    if(recv(sock, out, 2000, 0) < 0)
    {
        perror("Recieve failed");
        exit(1);
    }
}

void
sendMessage(int sock, char *in)
{
    if(send(sock, in, strlen(in), 0) < 0)
    {
        perror("Failed sending");
        exit(1);
    }
}

int
main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char   *message;
    char   server_reply[2000];
    size_t buffsize = 2000;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Connection failed");
        exit(1);
    }

    fprintf(stdout,"Socket created\n");
        
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family      = AF_INET;
    server.sin_port        = htons(PORT);

    if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connection failed");
        exit(1);
    }

    fprintf(stdout,"Connected\n");

    //Checking for updates, apply patch as needed
    recieveMessage(sock,server_reply);
    if(strcmp(server_reply,VERSION) != 0)
    {
        char* message = strdup("yes\0");
        sendMessage(sock,message);
        free(message);

        fprintf(stdout,"Updating...\n");
        fprintf(stdout,"\tDownloading patch...\n");
        getUpdate(sock);
        fprintf(stdout,"\tDone downloading\n");
        
        fprintf(stdout,"\tApplying patch...\n"); 
        applyUpdate();
        fprintf(stdout,"\tDone applying\n");

        fprintf(stdout,"Patch applied. Please re-run the script\n");
        exit(0);
        
    }else{
        fprintf(stdout,"Up to date\n");
        char* message = strdup("no\0");
        sendMessage(sock,message);
        free(message);
    }

    int characters = 0;

    message = (char *)malloc(buffsize * sizeof(char));
    
    //Commands to server
    while(1){
        fprintf(stdout,"Enter command: ");
        if((characters = getline(&message,&buffsize,stdin)) < 0)
        {
            perror("Getline faild");
            break;
        }
        
        //Get rid of newline character from getline, then send to server
        message[characters-1] = '\0';
        sendMessage(sock,message);
    }

    close(sock);
    free(message);
    return 0;
}
