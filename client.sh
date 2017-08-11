#!/bin/bash

echo компиляция клиентской части
g++ ./client/Client.cpp ./client/Client.h ./client/PacketType.h ./client/client_main.cpp -o sfml-client -lsfml-system -lsfml-network -std=c++14