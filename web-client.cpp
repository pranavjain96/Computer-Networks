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
#include "response.h"
#include "request.h"
#include "request.cpp"
using namespace std;

#define TM_BUF_SIZE 6000
//#define TM_PACKETS_TO_SEND 10
//#define TM_DEST_ADDR “10.129.36.52”
#define TM_DEST_PORT 4000
#define BUFFER_SIZE 5000


int main()
{
    std::cerr << "web client is not implemented yet" << std::endl;
    // do your stuff here! or not if you don't want to.
    //char buffer[TM_BUF_SIZE];
    int clientSocket;
    struct sockaddr_in destination_address;
    int error;
    char buffer[TM_BUF_SIZE] = {0};
    //family address
    destination_address.sin_family = AF_INET;
    //destination port
    destination_address.sin_port = htons(TM_DEST_PORT);
    //ip address decleration
    destination_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    memset(destination_address.sin_zero, '\0', sizeof(destination_address.sin_zero));
    
    //socket creation
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    //verify?  dont do this, idk how
    if(clientSocket == -1 ){
        perror("socket not created");
        return 1;
    }
    
    //connect to the server not wokring??????????
    error = connect(clientSocket,(struct sockaddr *)&destination_address, sizeof(destination_address));
    
    if(error == -1){
        perror("Socket not connected");
        return 2;
    }
    
    struct sockaddr_in  client_adress;
    socklen_t client_length = sizeof(client_adress);
    int socknamecode = getsockname(clientSocket, (struct sockaddr *)&client_adress, &client_length);
    if(socknamecode == -1){
        perror("get sock name");
        return 3;
    }
    
    char ip_string[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(client_adress.sin_family, & client_adress.sin_addr, ip_string, sizeof(ip_string));
    cout << "Connection set up from: " << ip_string << ":" << ntohs(client_adress.sin_port) << "\n";
    
    //seend/receive data
    bool end = false;
    string input;
    Request_HTTP request;
    
    
    while(1){
        

    while(!end){
        memset(buffer, '\0', sizeof(buffer));
        
        cout << "send ";
        cin >> request.url_request;
        request.newMessage();
        
        long sendCheck = send(clientSocket, request.message_request.c_str(), request.message_request.size(), 0);
        
        if(sendCheck < 0){
            perror("send");
            return 4;
        }
        
        
        long recvCheck = recv(clientSocket, buffer, TM_BUF_SIZE, 0);
        if(recvCheck == -1 ){
            perror("receive");
            return 5;
        }
        cout << "Received " << buffer << "\n";
        int i = 0;//where in response string
        int j =0;//where in substring buffer
        char buf_response[TM_BUF_SIZE];
        while(buffer[i] != ' ' && j< TM_BUF_SIZE){
            buf_response[j] = buffer[i];
            i++;
            j++;
        }
        memset(buf_response, '\0', TM_BUF_SIZE);
        j = 0;
        i++;
        while(buffer[i] != '\r' && j<TM_BUF_SIZE){
            buf_response[j] = buffer[i];
            i++;
            j++;
        }
        string responseCode = string(buf_response);
        cout << responseCode << endl;
        //cout << request.htmlBody
        
    }//end while end
        
        close(clientSocket);
    }//end while 1
    
    return 0;
    
    
    
}
