#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
using namespace std;

#define TM_BUF_SIZE 20
//#define TM_PACKETS_TO_SEND 10
//#define TM_DEST_ADDR “10.129.36.52”
#define TM_DEST_PORT 4000

int main()
{
    std::cerr << "web client is not implemented yet" << std::endl;
    // do your stuff here! or not if you don't want to.
    
    int clientSocket;
    struct sockaddr_in destination_address;
    int error;
    char buffer[TM_BUF_SIZE] = {0};
    //family address
    destination_address.sin_family = AF_INET;
    //destination port
    destination_address.sin_port = htons(TM_DEST_PORT);
    //ip address decleration
    destination_address.sin_addr.s_addr = inet_addr("0.0.0.0");
    
    //socket creation
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    //verify?  dont do this, idk how
    if(clientSocket != 0 ){
        perror("socket not created");
        return 1;
    }
    
    //connect to the server not wokring??????????
    error = connect(clientSocket,(struct sockaddr *)&destination_address, sizeof(destination_address));
    
    if(error < 0){
        perror("Socket not connected");
        return 2;
    }
    
    struct sockaddr_in  client_adress;
    socklen_t client_length = sizeof(client_adress);
    int socknamecode = getsockname(clientSocket, (struct sockaddr *)&client_adress, &client_length);
    if(socknamecode < 0){
        perror("get sock name");
        return 3;
    }
    
    char ip_string[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(client_adress.sin_family, & client_adress.sin_addr, ip_string, sizeof(ip_string));
    cout << "Connection set up from: " << ip_string << ntohs(client_adress.sin_port) << "\n";
    
    //seend/receive data
    bool end = false;
    string input;
    
    while(1){
        

    while(!end){
        memset(buffer, '\0', sizeof(buffer));
        
        cout << "send ";
        cin >> input;
        long sendCheck = send(clientSocket, input.c_str(), input.size(), 0);
        
        if(sendCheck < 0){
            perror("send");
            return 4;
        }
    }//end while end
        long recvCheck = recv(clientSocket, buffer, TM_BUF_SIZE, 0);
        if(recvCheck < 0 ){
            perror("receive");
            return 5;
        }
        close(clientSocket);
    }//end while 1
    
    return 0;
    
    
    
}
