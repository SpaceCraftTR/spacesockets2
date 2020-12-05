/*

SpaceSockets2 (a.k.a SpaceSockets 2.0)

Lets you to create sockets and make Internet based applications easily.

2020, Ali Sancakli <spacecraft.tr@gmail.com> <github.com/SpaceCraftTR>

SpaceSockets is licensed under the terms of MIT License.


*/
#ifndef SPACESOCKETS_HPP
#define SPACESOCKETS_HPP

#include <iostream>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>
#include <fstream>
#include <sys/select.h>
#include "definitions.hpp"

namespace SpaceSockets2{
        class tcp{

        public: 
                /*
                Constructor of TCP class. Set the mode for your purpose of use. 
                
                There are 2 modes available in SpaceSockets2:
                        -CLIENT_TCP is to create TCP client applications,
                        -SERVER_TCP is to create TCP server applications.
                 */
                tcp(char ip_address[], int connection_limit, int mode, int flags = WRITE_TO_TERMINAL, int ip_standard = IPV4, in_port_t port_number = PORT){

                        this->flags = flags;
                        if((mode & SERVER_TCP) && (mode & CLIENT_TCP)){ //if both are specified...

                                process_a_flag("Warning: Cannot use client and server functions at the same time! Aborting...",this->flags);
                                exit(-1);

                        }
                        this->mode = mode;
                        this->port_number = port_number;
                        this->connection_limit = connection_limit;
                        if(inet_aton(ip_address,&valid_ip_address) == 0){

                                process_a_flag("Invalid IP address, configuring SpaceSockets2 to local mode.",this->flags);
                                sock_address.sin_addr.s_addr = inet_addr("127.0.0.1");

                        }
                        else{

                                sock_address.sin_addr = valid_ip_address; 

                        }
                        
                        sock_address.sin_family = ip_standard;
                        sock_address.sin_port = htons(port_number);

                        if((socket_fd = socket(ip_standard,SOCK_STREAM,0)) <= 0){

                                process_a_flag("Error "+std::to_string(SOCKET_ERROR)+", a socket error occured. (POSIX error number: "+std::to_string(errno)+")",this->flags);
                                exit(SOCKET_ERROR);

                        }
                        optval = 1;
                        
                           
                        if((setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval)) < 0)){

                                process_a_flag("Error while setting socket option as reusable.",this->flags);

                        }

                       
                        if(mode & SERVER_TCP){ //No need to bind if it is client application.

                        if((bind_fd = bind(socket_fd,(sockaddr*)&sock_address,sizeof(sock_address))) < 0){

                                process_a_flag("Error "+std::to_string(BIND_ERROR)+", socket binding error. (POSIX error number: "+std::to_string(errno)+")",this->flags);
                                exit(BIND_ERROR);

                        }

                        }


                }  
                /*Listens to a spesific socket for incoming connections. Useful for server mode but also available for client applications.*/
                int tcp_listen(int socket_to_listen){

                        if((listen_fd = listen(socket_to_listen,connection_limit))< 0){

                                process_a_flag("Error "+std::to_string(LISTEN_ERROR)+", TCP socket listening error. (POSIX error number: "+std::to_string(errno)+")",this->flags);
                                return LISTEN_ERROR;

                        }

                                return SUCCESS;
                }    
                /*Accepts incoming connections and returns the newly created file descryptor.*/
                int tcp_accept_connection(){
                        
                        if(this->mode & SERVER_TCP){

                        int addr_len = sizeof(sock_address);
                        if((accept_fd = accept(socket_fd,(sockaddr*)&sock_address,(socklen_t*)&addr_len)) == 0){

                                process_a_flag("Error "+std::to_string(ACCEPT_ERROR)+", an error occured while accepting a connection request.",this->flags);
                                return ACCEPT_ERROR;

                        }
                        else{

                        process_a_flag("Successfully accepted connection, returning file desc.",this->flags);
                        return accept_fd;

                        }


                        }
                        if(this->mode & CLIENT_TCP){

                                process_a_flag("Critical: Client application tried to call server function!",this->flags);
                                exit(-1);

                        }

                }
                /*Receives some data that are coming through the socket that had been specified.*/
                template <class tcpType>
                int tcp_receive_data(tcpType &buffer, int file_desc){ 

                                        if(recv(file_desc,&buffer,sizeof(buffer),0) < 0){

                                                process_a_flag("Error "+std::to_string(RECV_ERROR)+", an error occured while receiving data from remote computer, "+inet_ntoa(valid_ip_address),this->flags);
                                                return RECV_ERROR;

                                             }
                                        return SUCCESS;

                }
                /*Sends some data to the socket that had been specified.*/
                template <class tcpSendType>
                int tcp_send_data(tcpSendType &data, int file_desc){
                        
                        if(send(file_desc,&data,sizeof(data),0) < 0){

                                process_a_flag("Error "+std::to_string(SEND_ERROR)+", data couldn't be send. Maybe client is disconnected.",this->flags);
                                return SEND_ERROR;

                        }
                        return SUCCESS;

       

                }
                //Connects to the server that had been specified with constructor.
                int connect_to_a_server(){

                        if(connect(socket_fd,(sockaddr*)&sock_address,sizeof(sock_address)) != 0){

                                process_a_flag("Error "+std::to_string(CONNECT_ERROR)+", couldn't connect to the remote computer,"+inet_ntoa(valid_ip_address),this->flags);
                                return CONNECT_ERROR;

                        }
                        else{

                                return SUCCESS;

                        }
                        

                }
                //Connects to a server that had been specified IP address and port number of. 
                int connect_to_a_server(char ip_address[], int port_number = PORT){

                        if(inet_aton(ip_address,&valid_address2) < 0){

                                process_a_flag("The IP address that was specified is invalid. Switching to local mode.",this->flags);
                                connect_sock_address.sin_addr.s_addr = inet_addr("127.0.0.1");
                        }       
                        else{

                                connect_sock_address.sin_addr = valid_ip_address;

                        }
                        connect_sock_address.sin_port = htons(port_number);
                        connect_sock_address.sin_family = IPV4;
                        
                        if(connect(socket_fd,(sockaddr*)&connect_sock_address,sizeof(connect_sock_address)) < 0){

                                process_a_flag("Error "+std::to_string(CONNECT_ERROR)+", couldn't connect to the remote computer,"+inet_ntoa(valid_address2),this->flags);
                                return CONNECT_ERROR;
                        }
                        else{
                                return SUCCESS;
                        }
                }
                //Closes the connection of the default socket.
                void close_connection(){

                        if(shutdown(socket_fd,SHUT_RDWR) < 0){

                                process_a_flag("Error "+std::to_string(CLOSE_ERROR)+", can't close the connection!",this->flags);
                                socket_fd = 0;
                        }
                        else{

                                if(close(socket_fd) < 0){


                                        process_a_flag("Cannot mark the socket as closed, forcing to close socket...",this->flags);
                                        

                                }
                                

                        }

                }
                //Closes the connection of a spesific socket.
                void close_connection(int &socket_filedesc){

                        if(shutdown(socket_filedesc,SHUT_RDWR) < 0){

                                process_a_flag("Error "+std::to_string(CLOSE_ERROR)+", can't close the connection! Forcely closing the socket...",this->flags);
                                socket_filedesc = 0;
                        }
                        else{

                                if(close(socket_filedesc) < 0){


                                        process_a_flag("Cannot mark the socket as closed! Forcely closing the socket...",this->flags);
                                        socket_filedesc = 0;

                                }
                                

                        }

                }
                //Sets new port for your application.
                void set_port_number(int new_port){

                        sock_address.sin_port = htons(new_port);
                        this->port_number = new_port;

                }
                /*Returns current port number.*/
                int get_port_number(){

                        return this->port_number;

                }
                /*Returns socket file descriptor.*/
                int get_socket_fd(){

                        return this->socket_fd;

                }
                /*Changes the flags.*/
                int set_flags(int new_flags){

                        this->flags = new_flags;

                }
                ~tcp(){ //Destructor of the TCP class.

                        if(shutdown(socket_fd,SHUT_RDWR) < 0){

                                process_a_flag("Error "+std::to_string(CLOSE_ERROR)+", can't close the connection!",this->flags);

                        }
                        else{

                                if(close(socket_fd) < 0){


                                        process_a_flag("Cannot mark the socket as closed, forcing to close socket...",this->flags);
                                        socket_fd = 0;

                                }
                                

                        }

                }
        private:
                int flags, socket_fd, bind_fd, listen_fd, accept_fd, connection_limit, optval, port_number, mode;
                sockaddr_in sock_address, connect_sock_address;
                in_addr valid_ip_address, valid_address2;
        };

        class udp{
        
        public:
                /*
                Constructor of the UDP class.
                
                If no IP address or invalid address has been specified, SpaceSockets2 automatically assigns 127.0.0.1 to IP address, which is not suitable if you want to communicate with a remote computer.
                */
                udp(char ip_address[],int flags = WRITE_TO_TERMINAL, int ip_standard = IPV4, in_port_t port_number = PORT){ 
                        this->flags = flags;
                        this->port_number = port_number;
                        
                        if(inet_aton(ip_address,&valid_ip_address) == 0){
                                
                                process_a_flag("Invalid IP address specified, setting SpaceSockets2 to address of this computer.",this->flags);
                                sock_address.sin_addr.s_addr = inet_addr("127.0.0.1");

                        }
                        else{

                                sock_address.sin_addr = valid_ip_address;

                        }

                        sock_address.sin_family = (sa_family_t)ip_standard;
                        
                        sock_address.sin_port = htons(port_number);

                        
                         

                        socket_fd = socket(ip_standard,SOCK_DGRAM,0);
                        if(socket_fd <= 0){

                                process_a_flag("Error "+std::to_string(SOCKET_ERROR)+", socket creation error! (POSIX error number: "+std::to_string(errno)+")",this->flags);

                        }
                        if((bind_fd = bind(socket_fd,(struct sockaddr*)&sock_address,sizeof(sock_address))) == -1){ 

                                process_a_flag("Error "+std::to_string(BIND_ERROR)+", socket binding error. (POSIX error number: "+std::to_string(errno)+")",this->flags);
                                

                        }
                


                }
                /*Send an UDP package to a remote computer.*/
                template <class T>
                int send_udp_message(T &data_to_send){
                        
                        sender_fd = sendto(socket_fd,data_to_send,sizeof(data_to_send),0,(sockaddr*)&sock_address,sizeof(sock_address));
                        if(sender_fd <=0){
                               process_a_flag("Error while sending data from UDP socket",this->flags);
                                return SENDTO_ERROR;
                        }
                        else{
                                
                                return SUCCESS;

                        }
                }
                /*Receive response from another computer.*/
                template <class T>
                int receive_udp_package(T &receiving_buffer){

                                sock_addr_size = sizeof(sock_address);

                                 if((recv_fd == recvfrom(socket_fd,&receiving_buffer,sizeof(receiving_buffer),0,(sockaddr*)&sock_address,&sock_addr_size) == -1)){
                                        
                                         process_a_flag("No reply from "+get_ip_address(this->valid_ip_address)+"!",this->flags);
                                        return RECVFROM_ERROR;
                                }
                                else{

                                        process_a_flag("Received UDP package from "+get_ip_address(this->valid_ip_address)+"!",this->flags);
                                        return SUCCESS;

                                }

                }
                /*Returns current port number.*/
                int get_port_number(){

                        return this->port_number;

                }
                /*Sets port number to new_port.*/
                int set_port_number(int new_port){

                        sock_address.sin_port = htons(new_port);
                        this->port_number = new_port;

                }
                int get_socket_fd(){

                        return this->socket_fd;

                }
                int set_flags(int new_flags){

                        flags = new_flags;

                }
                void close_connection(int socket){

                        if(shutdown(socket,SHUT_RDWR) < 0){

                                process_a_flag("Error "+std::to_string(CLOSE_ERROR)+", can't close the connection!",this->flags);

                        }
                        else{

                                if(close(socket) < 0){


                                        process_a_flag("Cannot mark the socket as closed, forcing to close socket...",this->flags);
                                        socket = 0;

                                }
                                

                        }


                }
                ~udp(){

                        if(shutdown(socket_fd,SHUT_RDWR) < 0){

                                process_a_flag("Error "+std::to_string(CLOSE_ERROR)+", can't close the connection!",this->flags);

                        }
                        else{

                                if(close(socket_fd) < 0){


                                        process_a_flag("Cannot mark the socket as closed, forcing to close socket...",this->flags);
                                        socket_fd = 0;

                                }
                                

                        }



                }
        private:
                int flags, socket_fd, bind_fd, recv_fd, sender_fd, port_number;
                in_addr valid_ip_address;
                struct sockaddr_in sock_address;
                unsigned int sock_addr_size = 0;
        };
        class icmp{
        public:
                /*
                Constructor of ICMP class.
                
                If no IP address has been specified, SpaceSockets2 automatically exits the process, because pinging current computer is a worthless idea.
                */
                icmp(char ip_address[],  int flags = WRITE_TO_TERMINAL, struct timeval timeout = {3,0}, int af_family = IPV4, int icmp_type = ICMP_ECHO, int id = 1234){ 
                        
                         if((inet_aton(ip_address,&valid_ip_address)) == -1){

                                 process_a_flag("(SpaceSockets 2.0) Error "+std::to_string(IP_CONVERSION_ERROR)+", IP conversion error. (Might be invalid address?)",this->flag);
                                 exit(IP_CONVERSION_ERROR);

                         }
                         
                        if((socket_fd = socket(af_family,SOCK_DGRAM,IPPROTO_ICMP)) <= 0){

                                process_a_flag("(SpaceSockets 2.0) Error "+std::to_string(SOCKET_ERROR)+", socket creation failed!",this->flag);

                        }
                        memset(&addr, 0, sizeof(addr)); //Setting everything to zero.
                        addr.sin_addr = valid_ip_address;
                        addr.sin_family = af_family;

                        memset(&icmp_header, 0, sizeof(icmp_header)); //Setting everything to zero.
                        icmp_header.type = icmp_type;
                        icmp_header.un.echo.id = id;

                        flag = flags;
                        this->timeout = timeout;
                        memset(&read_set,0,sizeof(read_set));
                        
                }
                int send_icmp_message(void* temp_data){ //Send an ICMP message to the remote computer.
                        
                        char message[16] = "spacecraftrocks";
                        
                        memcpy(temp_data,&icmp_header,sizeof(icmp_header));
                        memcpy(temp_data+sizeof(icmp_header),message,strlen(message));
                        sender_fd = sendto(socket_fd,temp_data,sizeof(icmp_header)+strlen(message),0,(struct sockaddr*)&addr,sizeof(addr));
                        if((sender_fd) <= 0){

                                return SENDTO_ERROR;

                        }
                        else{

                                return SUCCESS;

                        }
                        
                }
                int send_icmp_message(void* temp_data, char message[]){ //Send a custom ICMP message to the remote computer.
                        
                        
                        
                        memcpy(temp_data,&icmp_header,sizeof(icmp_header));
                        memcpy(temp_data+sizeof(icmp_header),message,strlen(message));
                        sender_fd = sendto(socket_fd,temp_data,sizeof(icmp_header)+strlen(message),0,(struct sockaddr*)&addr,sizeof(addr));
                        if((sender_fd) <= 0){

                                return SENDTO_ERROR;

                        }
                        else{

                                return SUCCESS;

                        }
                        
                }
                void set_connection_timeout(int new_timeout){ //Sets an ICMP timeout.

                        this->timeout = {new_timeout,0};

                }
                int wait_for_response(void* buffer){ //Waits for response from remote computer.
                        
                        FD_SET(socket_fd,&read_set);
                        if((response_fd = select(socket_fd+1,&read_set,NULL,NULL,&timeout)) == 0){

                                process_a_flag("No reply received from remote server, "+get_ip_address(this->valid_ip_address)+"",flag);
                                return NO_REPLY;

                        }
                        else if(response_fd < 0){

                                process_a_flag("An error occured while receiving an ICMP reply.",flag);
                                return SOCKET_ERROR;

                        }
                        else{

                                process_a_flag("Received a reply from "+get_ip_address(this->valid_ip_address)+"!",flag);
                        recv_id = recvfrom(socket_fd,&buffer,sizeof(buffer),0,nullptr,&sock_length);
                        if(recv_id <= 0){

                                process_a_flag("Error while receiving an ICMP package from remote computer, "+get_ip_address(this->valid_ip_address)+"!",flag);
                                return RECV_ERROR;

                        }
                        else if(recv_id < sizeof(icmp_header)){

                                process_a_flag("Non-compatible data had been received from "+get_ip_address(this->valid_ip_address)+"!",flag);
                                return PACKAGE_ERROR;

                        }


                        memcpy(&receive_header,&buffer,sizeof(receive_header));
                                return SUCCESS;
                        }


                }
                int get_received_info_type(){

                        return receive_header.type;

                }
                in_addr get_valid_address(){ //Get the target IP address in the form of in_addr.

                        return this->valid_ip_address;

                }
                int set_flags(int new_flag){

                        this->flag = new_flag;

                }
                void close_connection(int socket){

                        if(shutdown(socket,SHUT_RDWR) < 0){

                                process_a_flag("Error "+std::to_string(CLOSE_ERROR)+", can't close the connection!",this->flag);

                        }
                        else{

                                if(close(socket) < 0){


                                        process_a_flag("Cannot mark the socket as closed, forcing to close socket...",this->flag);
                                        socket = 0;

                                }
                                

                        }
                  

                }
                ~icmp(){

                        if(shutdown(socket_fd,SHUT_RDWR) < 0){

                                process_a_flag("Error "+std::to_string(CLOSE_ERROR)+", can't close the connection!",this->flag);

                        }
                        else{

                                if(close(socket_fd) < 0){


                                        process_a_flag("Cannot mark the socket as closed, forcing to close socket...",this->flag);
                                        socket_fd = 0;

                                }
                                

                        }


                        
                }
        private:
                in_addr valid_ip_address;
                int socket_fd, sender_fd, response_fd, recv_id;
                int flag = 0;
                sockaddr_in addr;
                struct icmphdr icmp_header, receive_header;
                fd_set read_set;
                struct timeval timeout;
                socklen_t sock_length = 0;
        };


}
#endif
