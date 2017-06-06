#ifndef PECKETTYPE_H
#define PECKETTYPE_H

#include "SFML/System.hpp"

typedef sf::Uint8 PacketType;
const PacketType INITIAL_NAME_DATA=0;
const PacketType GENERAL_MSG=1;
const PacketType SERVER_MSG=2;
const PacketType REQUEST_MSG=3;

#endif
