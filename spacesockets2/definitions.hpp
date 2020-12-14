/*
Definitions for SpaceSockets2

This headers purpose is to declare constant values for SpaceSockets2.

2020, Ali Sancakli <spacecraft.tr@gmail.com>

*/
#ifdef __unix__
#include <netinet/in.h>
#include <arpa/inet.h>
#endif // __unix__
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define WINSOCK_RELATED_ERROR 555
#endif // _WIN32
#include "flags.hpp"

/*Error codes*/

#define SENDTO_ERROR 500
#define RECVFROM_ERROR 501
#define SOCKET_RELATED_ERROR 550
#define BIND_ERROR 551
#define LISTEN_ERROR 600
#define CONNECT_ERROR 601
#define SEND_ERROR 602
#define RECV_ERROR 603
#define ACCEPT_ERROR 604
#define CLOSE_ERROR 605
#define IP_CONVERSION_ERROR 700
#define NO_REPLY 1000
#define PACKAGE_ERROR 1500
#define DNS_ERROR 2000
#define SUCCESS 0


/*Internet Protocol standards*/
#define IPV4 AF_INET
#define IPV6 AF_INET6

/*Standard port number*/
#define PORT 8080

/*TCP modes*/
#define CLIENT_TCP 1<<5
#define SERVER_TCP 1<<4

/*Logging function, can be used for debugging purposes.*/
void process_a_flag(std::string information_text, int flag){

        if(flag & WRITE_TO_TERMINAL){

                std::cout<<"(SpaceSockets 2.0) "<<information_text<<std::endl;

        }
        if(flag & WRITE_TO_FILE){

                std::ofstream output_file("spacesockets2-logs.txt",std::ios::app);
                output_file<<"(SpaceSockets 2.0) "<<information_text<<std::endl;
                output_file.eof();
        }



}
std::string get_ip_address(in_addr valid_ip_address){ //Returns target IP address as a string.

        return inet_ntoa(valid_ip_address);

}
