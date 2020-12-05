#include "../spacesockets2/SpaceSockets2.hpp"

int main(){
    
    SpaceSockets2::tcp tcp_server("127.0.0.1",999999,SERVER_TCP,WRITE_TO_FILE | WRITE_TO_TERMINAL);

    char message[100] = "hello world!\n\n"; //SMS limit. :P
   
          
          if(!tcp_server.tcp_listen(tcp_server.get_socket_fd())){

              std::cout<<"Port "<<tcp_server.get_port_number()<<" portunu dinliyorum."<<std::endl;

          }
          int accept_fd = tcp_server.tcp_accept_connection();
          
          
          
          while(1){
              tcp_server.tcp_send_data(message,accept_fd);  
          }
          


    return 0;
}