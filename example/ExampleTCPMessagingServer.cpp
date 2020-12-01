#include "../spacesockets2/SpaceSockets2.hpp"

int main(){
    
    SpaceSockets2::tcp tcp_server("127.0.0.1",999999,SERVER_TCP,WRITE_TO_FILE | WRITE_TO_TERMINAL);

    char message[140] = "hello world!\n\n"; //SMS limit. :P

          
          std::cout<<tcp_server.tcp_listen(tcp_server.get_socket_fd());
          int accept_fd = tcp_server.tcp_accept_connection();
          std::cout<<accept_fd<<std::endl;
          while(1){
            tcp_server.tcp_send_data(message,accept_fd);    
          }
          


    return 0;
}