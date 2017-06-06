#include <iostream>
#include <SFML/Network.hpp>
#include <thread>

#include <iostream>
#include "Server.h"

void getServer()
{
    unsigned short port = 1234;
    std::cout<<"What port? ";
    std::cin>>port;
    std::cout<<"\n";


    std::cout<<"Local host:"<<sf::IpAddress::LocalHost<<"\n"
        <<"Local: "<<sf::IpAddress::getLocalAddress()<<"\n"
        <<"Public: "<<sf::IpAddress::getPublicAddress()<<"\n";
    std::cin.get();

    Server server(port);
    server.run();
    std::cin.get();
    
}

int main()
{
	getServer();
}
