#include "../spacesockets2/SpaceSockets2.hpp"

int main(){


std::cout<<"IP address of Google is: "<<SpaceSockets2::dns_resolve("google.com");


return 0;
}
