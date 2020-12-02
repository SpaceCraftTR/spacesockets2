#include "../spacesockets2/SpaceSockets2.hpp"
#include <vector>
int main(){

    char req[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
    SpaceSockets2::tcp web_req("93.184.216.34",99999,CLIENT_TCP);
    char buffer[2000];
    web_req.connect_to_a_server("93.184.216.34",80);
    if(!web_req.tcp_send_data(req,web_req.get_socket_fd())){

        web_req.tcp_receive_data(buffer,web_req.get_socket_fd());
        std::cout<<buffer;
    }


    return 0;
}