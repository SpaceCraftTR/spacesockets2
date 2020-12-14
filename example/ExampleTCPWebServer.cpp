/*

Actually, it is a fork of messaging server application, it just sends some HTTP information and makes sense.

Open your browser and visit localhost:8080 (or whichever port that you used to build this server app.)
*/
#include "../spacesockets2/SpaceSockets2.hpp"

int main(){
    
    SpaceSockets2::tcp tcp_server("127.0.0.1",999999,SERVER_TCP,NO_DEBUG_INFORMATION);

    char message[] = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 100\n\n<html><title>SpaceCraft Rocks!</title><body><b>Look at the title of the website! </b></body></html>"; 

          
          if(!tcp_server.tcp_listen(tcp_server.get_socket_fd())){

              std::cout<<"Listening on port "<<tcp_server.get_port_number()<<"."<<std::endl;

          }
          int accept_fd = tcp_server.tcp_accept_connection();
          if(accept_fd > 0){

              std::cout<<"A connection has been accepted successfully!"<<std::endl;

          }
          while(1){
              if(tcp_server.tcp_send_data(message,accept_fd) == SEND_ERROR){

                  std::cout<<"Client disconnected, that means page loaded successfully!"<<std::endl;
                  exit(0);

              }
          }
                
          
          


    return 0;
}
