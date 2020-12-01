#include "../spacesockets2/SpaceSockets2.hpp"


int main(){

    SpaceSockets2::udp udp_server("127.0.0.1",WRITE_TO_FILE | WRITE_TO_TERMINAL); //Which means I've created a local UDP server.
    char msg[1000] = "Hello from SpaceSockets2!\n";
    

    while(1){

    if(!udp_server.send_udp_message(msg)){

        std::cout<<"Message has been sent to socket successfully!"<<std::endl;


    }

    }





    return 0;
}
