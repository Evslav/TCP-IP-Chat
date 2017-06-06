#ifndef CLIENT_H
#define CLIENT_H
#include "SFML/Network.hpp"
#include "PacketType.h"

class Client
{
private:
	std::string name;
	sf::TcpSocket me;
public:
	Client(const std::string & name);
	~Client();


	sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port);
	sf::Socket::Status send (PacketType type, const std::string & msg);
	sf::Socket::Status receive(std::string & msg);
};

#endif
