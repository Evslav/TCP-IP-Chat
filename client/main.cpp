#include <iostream>
#include <SFML/Network.hpp>
#include <thread>

#include "Server.h"


#include "Client.h"
#include "PacketType.h"

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

int getClient()
{
    std::string name;
        std::cout<<"What's your name: ";
        std::getline(std::cin, name);
        std::cout<<"\n";
        Client client(name);

        unsigned short port;
        std::cout<<"What port? ";
        std::cin>>port;
        std::cin.get();


        std::cout<<"What Ip Address?"<<std::endl;

        std::string IP = "127.0.0.1";
        std::getline(std::cin, IP);

        sf::Socket::Status status;
        
        status=client.connect(sf::IpAddress(IP), port);

        if(status!=sf::Socket::Done)
        {
            std::cout<<"Sorry we couldn't connect\n";
            return -1;
        }
        std::cout<<"Connection established"<<std::endl;
        client.send(INITIAL_NAME_DATA, name);

        sf::Thread thread([&]()
        {
            while(1)
            {
                std::string s;
                std::getline(std::cin, s);
                if(s=="!"){
                 client.send(REQUEST_MSG,"");
                } else {
                    client.send(GENERAL_MSG, s);
                }
            }
        });
        thread.launch();

        const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
        sf::Clock clock;
        clock.restart();

        while(1)
        {
            std::string toBePushed;

            sf::Socket::Status status=client.receive(toBePushed);
            if(status==sf::Socket::Done)
            {
                std::cout<<toBePushed<<std::endl;
            }
            else if(status==sf::Socket::Disconnected)
            {
                std::cout << "You have been disconnected\n";
                sf::sleep(sf::seconds(2));
                return -1;
            }

            sf::Time time = clock.getElapsedTime();
            //только при условии что принял какой либо пакет ,
            sf::sleep(TimePerFrame - time);
            clock.restart();

        }
}

int main()
{
    std::string who;
    std::cout << "Do you want to be a server (s) or a client (c) ? ";
    std::getline(std::cin, who);
    std::cout<<"\n";

    if(who == "s")
        getServer();
    else
        getClient();
    return 0;
}
