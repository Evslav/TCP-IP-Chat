#include "Server.h"
#include "PacketType.h"
#include <iostream>

Server::Server(unsigned short port)
{
    listner.listen(port);
	listner.setBlocking(false);

}


Server::~Server()
{
}

void Server::handlePackets()
{
	//handle incoming data
	for(Clients::iterator it=clients.begin(); it!=clients.end();)
	{
		sf::Packet packet;
		sf::Socket::Status status=it->first->receive(packet);
		
		switch (status)
		{
		case sf::Socket::Done:
			PacketType type;
			packet>>type;
			if(type==INITIAL_NAME_DATA)
			{
				//store the name
				packet>>it->second;
				std::cout<<it->second<<" has joined\n";
                broadCast(INITIAL_NAME_DATA, it->second," has joined");
			}
			else if(type==GENERAL_MSG)
			{
				std::string msg;
				packet>>msg;
                //std::cout<<it->second<<": "<<msg<<"\n";
                broadCast(GENERAL_MSG, it->second,msg);
			}
            else if(type==REQUEST_MSG){
                std::string message;
                message+="Online: "+std::to_string(clients.size())+" - ";
                for(auto i : clients){
                    message+= i.second+";";
                }
                sf::Packet pack;
                pack<<type<<std::string(message);
                it->first->send(pack);
            }
			++it;
			break;

		case sf::Socket::Disconnected:
            std::cout<<it->second<<" has been disconnected\n";
            broadCast(GENERAL_MSG, it->second," has been disconnected");
			it=clients.erase(it);
			break;

		default:
			++it;
		}
	//	std::cout<<"wtf\n";
	}
}

void Server::broadCast(PacketType type,const std::string & name, const std::string & msg)
{
	for(Clients::iterator it=clients.begin(); it!=clients.end(); ++it)
	{
        if (it->second != name)
        {
            sf::Packet pack;
            pack<<type<<std::string(name + ": " + msg);
            it->first->send(pack);
        }
	}
}



void Server::run()
{

    //std::cout << "Server start" << std::endl;

    //sf::Thread thread([&]()
    //{
    //	while(1)
    //	{
    //	std::string s;
    //	std::getline(std::cin, s);
    //    broadCast(SERVER_MSG, "SERVER",s);
    //	}
    //});
    //thread.launch();
    sf::Clock clock;
    clock.restart();
    size_t old_size_client = 0;
	sf::TcpSocket * nextClient=nullptr;
	while(1)
	{
		//Handle newcoming clients
		if(nextClient==nullptr)
		{
			nextClient=new sf::TcpSocket;
			nextClient->setBlocking(false);
		}
		if(listner.accept(*nextClient) == sf::Socket::Done)
		{
			clients.insert(std::make_pair(nextClient, ""));
			nextClient=nullptr;
		}
		handlePackets();

        if(old_size_client != clients.size()){
            old_size_client=clients.size();

            //for linux
            //system("clear");

            //for windows
            system("cls");
            std::cout<<"Local host:"<<sf::IpAddress::LocalHost<<"\n"
                <<"Local: "<<sf::IpAddress::getLocalAddress()<<"\n"
                <<"Public: "<<sf::IpAddress::getPublicAddress()<<"\n";
            std::cout << "Online: "<< std::to_string(clients.size())<<":"<<std::endl;

            for(auto i : clients){
                std::cout << i.second << std::endl;
            }
        }


        sf::Time time = clock.getElapsedTime();
        //только при условии что принял какой либо пакет ,
        sf::sleep(TimePerFrame - time);
        clock.restart();
        //std::cout << time.asMilliseconds() << "\n";
	
	}
}

