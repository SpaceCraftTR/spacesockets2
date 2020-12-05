#include <iostream>
#include "../spacesockets2/SpaceSockets2.hpp"


void check_ports(int starting_port, int ending_port, char ip_buffer[]){

        SpaceSockets2::tcp space_netcat(ip_buffer,999999,CLIENT_TCP,NO_DEBUG_INFORMATION,IPV4);

        for(int i = starting_port; i <= ending_port; i++){

        
        if(space_netcat.connect_to_a_server(ip_buffer,i)){

            //std::cout<<"Port "<<i<<" is not available for connections on "<<ip_buffer<<"!\n";

        }
        else{

            std::cout<<"Port "<<i<<" is available for connections on "<<ip_buffer<<"!\n\n\n\n\n";
            check_ports(i+1,ending_port,ip_buffer);

        }

    }


}
int main(int argc, char* argv[]){

    std::ofstream output_netcat("netcat-log.txt");
    char ip_buffer[20];
    unsigned short int starting_port, ending_port;    
    std::cout<<"Please enter the target IP address that will be checked for opened ports."<<std::endl;
    std::cin>>ip_buffer;
    std::cout<<"Please enter the starting port. (0-65535)"<<std::endl;
    std::cin>>starting_port;
    std::cout<<"Please enter the ending port. (0-65535)"<<std::endl;
    std::cin>>ending_port;
    
    check_ports(starting_port,ending_port,ip_buffer);



    return 0;
}