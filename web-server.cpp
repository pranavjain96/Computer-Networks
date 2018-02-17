#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include "response.h"
#include "response.cpp"


#include <iostream>
#include <fstream>
#include <sstream>

#define BUFFER_SIZE 60
#define DEST_PORT 4001
using namespace std;

/*struct sockaddr_in
 {
 short          sin_family;
 u_short        sin_port;
 struct in_addr sin_addr;
 char           sin_zero[8];
 };*/

int main()
{
    //std::cerr << "web server is not implemented yet" << std::endl;
    // do your stuff here! or not if you don't want to.
    int listen_socket, client_socket;
    struct sockaddr_in source_address;
    struct sockaddr_in dest_address;
    int error = -1;
    

    //address family
    dest_address.sin_family = AF_INET;
    
    //port
    dest_address.sin_port = htons(DEST_PORT);
    
    //IP adress, change to automatically get it
    dest_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    //create a socket
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    
    
    //error check -- this migt not be right
    /*if(listen_socket != 0){
     cout >> "ERROR"
     error = 1;
     return error;
     }*/
    
    //bind socket
    bind(listen_socket, (struct sockaddr*)&dest_address, sizeof(dest_address));
    /*if(bind(listen_socket, (struct sockaddr*)&dest_address, sizeof(dest_address)) == -1){
        perror("bind");
        error = 2;
        return error;
    };*/
    
    int listenCheck = listen(listen_socket, 1);
    
    if(listenCheck != -1){
        cout << "Listening on port " << DEST_PORT << "\n";
    }
    
       //source addressis is  client address
       //accept connection
       while(1){//until end
           
           
           socklen_t client_size = sizeof(source_address);
           
           client_socket = accept(listen_socket, (struct sockaddr*)&source_address, &client_size);
           //error checking
           if (client_socket == -1) {
               perror("accept");
               error = 4;
               return error;
           }
           
           char ip_string[INET_ADDRSTRLEN] = {'\0'};
           //inet_ntoa instead of inet_ntop
           inet_ntop(source_address.sin_family, &source_address.sin_addr, ip_string, sizeof(ip_string));
           cout <<" Connection being accepted from " << ip_string << ":"  << ntohs(source_address.sin_port) << "\n";
           
           //read/write
           ResponseHTTP response;
           
           bool end = false;
           char buffer[BUFFER_SIZE] = {0};
           //string stringstream;
           
           while(!end){
               memset(buffer, '\0', sizeof(buffer));
               
               
               if(recv(client_socket, buffer, BUFFER_SIZE, 0) == -1){
                   perror("recv");
                   error = 5;
                   return error;
               }
               
               cout << buffer << "\n";
               response.requestMessage(string(buffer));
               response.decodeMessage();
               response.decodeURL();
               
               const char *directory = response.directory.c_str();
               FILE * File = fopen(directory, "r");
               
               if(File == NULL){
                   cout << "File does not exsist 🙃\n";
                   response.newerrorCode("404 File Not Found ");
                   
                   
               }else{
                   cout << "File does exsist\n";
                   response.newerrorCode("200 OK ");
               }
               response.newMessage();
               const char *responseMessage = response.message_response.c_str();
               if(send(client_socket, responseMessage , strlen(responseMessage), 0) == -1){
                   perror("send");
                   error = 6;
                   return error;
               }
               
           }
           close(client_socket);
           
           
           //int port = 4000;
           //char ip_address = "127.0.0.1";
           
           
           //int sockfd = socket(AF_INET, SOCK_STREAM, 0);
           
           /*struct sockaddr_in address;
            address.sin_family = AF_INET;
            adress.sin_port = htons(port);
            //change below to get IP address automatically
            adress.sin_addr.s_addr = inet_addr(ip_address);
            memset(address.sin_zero, '\0', sizeof(address.sin_zero));*/
           
           
           
           
           
           //create socket
           
           
           
       }
       }
