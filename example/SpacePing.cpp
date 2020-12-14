/*

SpacePing

SpacePing is a ping clone that is built with SpaceSockets2 library.

2020, Ali Sancakli <spacecraft.tr@gmail.com>

*/
#include "../spacesockets2/SpaceSockets2.hpp"

void ping_req(char ip_address[], int pkg_amount = 5){

    int success_count = 0, failed_count = 0;
    unsigned char data[2048];
    SpaceSockets2::icmp spaceping(SpaceSockets2::dns_resolve(ip_address),WRITE_TO_FILE); //The IP address that is specified might be a domain address.
    spaceping.set_connection_timeout(5);
    std::cout<<"Starting to send ICMP echo request to following address : "<<get_ip_address(spaceping.get_valid_address())<<"\n";
        for(int i = 0; i < pkg_amount; i++){
                

            spaceping.send_icmp_message(&data);
            if(spaceping.wait_for_response(&data) == NO_REPLY){
                
                std::cout<<"No reply received from "<<get_ip_address(spaceping.get_valid_address())<<std::endl;
                exit(0);

            }
            
                if(!spaceping.get_received_info_type()){

                    success_count++;
                    std::cout<<"Pong from "<<get_ip_address(spaceping.get_valid_address())<<"!"<<std::endl;

                }
                else{

                    failed_count++;
                    std::cout<<"No ICMP packages received from "<<get_ip_address(spaceping.get_valid_address())<<"!"<<std::endl;
                    
                }


                

                }
    std::cout<<"Finished ping request, "<<(success_count+failed_count)<<" packages sent, "<<success_count<<" package(s) resulted with success, "<<failed_count<<" package(s) failed."<<std::endl;
}
int main(int argc, char* argv[]){


    if(argc >= 2){

        char ip_addr[20];
        strcpy(ip_addr,argv[argc-1]);
        ping_req(ip_addr);
    }
    else{
        char ip_address[20];
        int amount = 1;
        std::cout<<"Please enter the IP address that you want to send ping request to, or enter -1 to terminate SpacePing."<<std::endl;
        std::cin>>ip_address;
        std::cout<<"Please enter the amount of packages that will be send to "<<ip_address<<std::endl;
        std::cin>>amount;
        if(strcmp(ip_address,"-1") == 0){

                std::cout<<"Aborting."<<std::endl;
                return -1;

        }
        else{
                ping_req(ip_address, amount);

        }



    }
    


    return 0;
}