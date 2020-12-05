#include "../spacesockets2/SpaceSockets2.hpp"

int main(){
        char recv_buffer[100];
        SpaceSockets2::tcp tcp_client("127.0.0.1",999999,CLIENT_TCP,NO_DEBUG_INFORMATION);

        if(!tcp_client.connect_to_a_server("127.0.0.1")){

            std::cout<<"Connected!"<<std::endl;
            

        }
        else{

            std::cout<<"Waiting for connection!"<<std::endl;


        }

        while(1){

            bzero(recv_buffer,100);
            if(!tcp_client.tcp_receive_data(recv_buffer,tcp_client.get_socket_fd())){
                if(strlen(recv_buffer) > 0){

                    std::cout<<"Server says: "<<recv_buffer<<std::endl;
                    bzero(recv_buffer,100);
                }
                

            }



        }
         


    return 0;
}