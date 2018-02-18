//
//  web-server.cpp
//  Networks
//
//  Created by Sophie Hegarty on 8/2/2018.
//  Copyright © 2017 Sophie Hegarty. All rights reserved.
//

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
//#define DEST_PORT 4000
using namespace std;

/*struct sockaddr_in
 {
 short          sin_family;
 u_short        sin_port;
 struct in_addr sin_addr;
 char           sin_zero[8];
 };*/

/* struct data{
 add everything in here for the threading 
 }
 */

int main(int argc, char *argv[])
{
    if ( argc != 4){
        cout << "usage: " << argc[0] << "<host> <port> <directory>\n";
    }else{
        char host[BUFFER_SIZE] = argc[1];
        int DEST_PORT = argc[2];
        char dir[BUFFER_SIZE] = argc[3];
    }
    /*NEED TO APPLY ARGUMENTS TO THE SERVER, EG HOW TO ADD HOST TO THE MESSAGE?
     HOW TO ADD PORT TO CLIENT ALSO? IS NECESSARY? 
     HOW TO ADD DIRECTORY TO THE URL THING
     */
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
               ifstream file;
               file.open(directory);
               
               
               
               if(!file){
                   cout << "File does not exsist 🙃\n";
                   response.newerrorCode("404 File Not Found ");
                   
                   
               }else{
                   string fileLine;
                   string fileContents;
                   while(!file.eof()){
                       getline(file,fileLine);
                       //cout << fileLine << "\n";
                       fileContents= fileContents + fileLine + "\n";
                       
                   }
                   cout << "Size of file is: " << fileContents.length() << endl;
                   file.close();
                    response.newhtmlBody(fileContents);
                   //response.newhtmlBody(file)
                   //cout << "Contents:" << fileContents << endl;
                   
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
               //memset(responseMessage, '\0', sizeof(responseMessage);
               
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
