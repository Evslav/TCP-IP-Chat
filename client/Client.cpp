#include "Client.h"
#include "PacketType.h"
#include <iostream>

Client::Client(const std::string & name_):name(name_)
{
	
}


Client::~Client(void)
{
}


sf::Socket::Status Client::connect(const sf::IpAddress & IP, unsigned short port)
{
	//connect to server
	sf::Socket::Status stat= me.connect(IP, port);
	me.setBlocking(false);
	return stat;
}

sf::Socket::Status Client::send (PacketType type, const std::string & msg)
{
	sf::Packet packet;
	packet<<type<<msg;
	return me.send(packet);
}

sf::Socket::Status Client::receive(std::string & msg)
{
	sf::Packet packet;
	sf::Socket::Status status=me.receive(packet);
	PacketType type;
	packet>>type;
	if(status==sf::Socket::Done)
	{
        //std::cout<<msg<<"\n";
        packet>>msg;
	}
	return status;
}
