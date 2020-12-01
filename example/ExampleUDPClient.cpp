#include "../spacesockets2/SpaceSockets2.hpp"



int main(){

        SpaceSockets2::udp udp_client("",NO_DEBUG_INFORMATION); /*
        If you type the same IP address as server to our client, you'll get a nice little binding error with error number 98, which means "socket already in use".
        Leave IP address field empty if you want to use those two applications (both server and client) locally.
        */
        char receiving_buf[1000];
        int return_val;
        while(1){
            return_val = udp_client.receive_udp_package(receiving_buf);
        if(!return_val){

            std::cout<<"Other application says : "<<receiving_buf<<std::endl;


        }



        }

    return 0;
}