#!/bin/sh

mkdir build
g++ example/ExampleUDPServer.cpp -o build/linux/udp_server_application 
if [ $? -eq 0 ]
then
    echo "\n\n\n\nExample UDP Server application has been built successfully!\n\n" 
else
    echo "\n\n\n\nBuild of Example UDP Server application has failed!\n\n"
fi
g++ example/ExampleUDPClient.cpp -o build/linux/udp_client_application
if [ $? -eq 0 ]
then
    echo "\n\n\n\nExample UDP Client app has been built successfully!"
else
    echo "\n\n\n\nBuild of Example UDP Client application has failed!\n\n"
fi

g++ example/SpacePing.cpp -o build/linux/spaceping
if [ $? -eq 0 ]
then
    echo "\n\n\n\nSpacePing has been built successfully!"
else
    echo "\n\n\n\nBuild of SpacePing application has failed!\n\n"
fi
g++ example/ExampleTCPMessagingClient.cpp -o build/linux/example_tcp_messaging_client
if [ $? -eq 0 ]
then
    echo "\n\n\n\nExample TCP Messaging Client app has been built successfully!"
else
    echo "\n\n\n\nBuild of Example TCP Messaging Client application has failed!\n\n"
fi
g++ example/ExampleTCPMessagingServer.cpp -o build/linux/example_tcp_messaging_server
if [ $? -eq 0 ]
then
    echo "\n\n\n\nExample TCP Messaging Server app has been built successfully!"
else
    echo "\n\n\n\nBuild of Example TCP Messaging Server application has failed!\n\n"
fi
g++ example/ExampleTCPWebClient.cpp -o build/linux/example_web_client
if [ $? -eq 0 ]
then
    echo "\n\n\n\nExample TCP WebClient app has been built successfully!"
else
    echo "\n\n\n\nBuild of Example TCP WebClient application has failed!\n\n"
fi
g++ example/ExampleTCPWebServer.cpp -o build/linux/example_tcp_webserver
if [ $? -eq 0 ]
then
    echo "\n\n\n\nExample TCP Webserver has been built successfully!\n\nDo not forget to give an eye to other SpaceCraft projects!\n\nwww.github.com/SpaceCraftTR" 
else
    echo "\n\n\n\nBuild of Example TCP Webserver failed!\n\n"
fi
g++ example/SpaceScanner.cpp -o build/linux/spacescanner
if [ $? -eq 0 ]
then
    echo "\n\n\n\nSpaceSockets 2.0 has been built successfully!\n\nDo not forget to give an eye to other SpaceCraft projects!\n\nwww.github.com/SpaceCraftTR" 
else
    echo "\n\n\n\nBuild failed!\n\n"
fi
