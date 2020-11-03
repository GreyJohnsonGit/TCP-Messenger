//
// Created by renne_000 on 10/26/2020.
//

#define UNNECESSARY_INCLUDES "To Show that compilation works"

#ifdef UNNECESSARY_INCLUDES
#include "HandshakeMessage.h"
#include "Message.h"
#include "Utility.h"
#include "IMessage.h"
#include "Utility.h"
#endif

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define PORT 8888

void initalizeSockets(int maxClients, int clientSockets[30], int *masterSocket, int index);

int main(int argc , char *argv[])
{
    int masterSocket , addressLength , newSocket , clientSocket[30] , maxClients = 30 , activity, currentIndex , valread , sd;
    int max_sd;
    struct sockaddr_in address;
    char dataBuffer[1025];

    //set of socket descriptors
    fd_set socketDescriptorSet;

    //a message
    char *message = "Connected to client \r\n";

    initalizeSockets(maxClients, clientSocket, &masterSocket, currentIndex);

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to PORT
    if (bind(masterSocket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //specify maximum of 3 pending connections for the master socket
    if (listen(masterSocket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addressLength = sizeof(address);
    puts("Waiting for connections ...");

    while(true)
    {
        //clear the socket set
        FD_ZERO(&socketDescriptorSet);

        //add master socket to set
        FD_SET(masterSocket, &socketDescriptorSet);
        max_sd = masterSocket;

        //add child sockets to set
        for (currentIndex = 0 ; currentIndex < maxClients ; currentIndex++)
        {
            //socket descriptor
            sd = clientSocket[currentIndex];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &socketDescriptorSet);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL
        activity = select( max_sd + 1 , &socketDescriptorSet , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket
        if (FD_ISSET(masterSocket, &socketDescriptorSet))
        {
            if ((newSocket = accept(masterSocket, (struct sockaddr *)&address, (socklen_t*)&addressLength)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , newSocket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

            //send new connection greeting message
            if(send(newSocket, message, strlen(message), 0) != strlen(message) )
            {
                perror("send");
            }

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (currentIndex = 0; currentIndex < maxClients; currentIndex++)
            {
                //if position is empty
                if(clientSocket[currentIndex] == 0 )
                {
                    clientSocket[currentIndex] = newSocket;
                    printf("Adding to list of sockets as %d\n" , currentIndex);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (currentIndex = 0; currentIndex < maxClients; currentIndex++)
        {
            sd = clientSocket[currentIndex];

            if (FD_ISSET( sd , &socketDescriptorSet))
            {
                //Check if it was for closing , and also read the
                if ((valread = read(sd , dataBuffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address, (socklen_t*)&addressLength);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    clientSocket[currentIndex] = 0;
                }

                else
                {
                    //set the string terminating NULL byte on the end
                    dataBuffer[valread] = '\0';
                    send(sd , dataBuffer , strlen(dataBuffer) , 0 );
                }
            }
        }
    }

    return 0;
}

void initalizeSockets(int maxClients, int clientSockets[30],int *masterSocket, int index) {
    //initialize all clientSocket[] to 0 so not checked
    for (index = 0; index < maxClients; index++)
    {
        clientSockets[index] = 0;
    }

    //create a master socket
    if((*masterSocket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections
    int opt = 1;
    if( setsockopt(*masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(int)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}