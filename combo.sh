#!/bin/bash

echo компиляция комбинорлванного приложения
g++ ./client/Client.cpp ./client/Client.h ./client/PacketType.h ./main.cpp ./server/Server.cpp ./server/Server.h -o sfml-project -lsfml-system -lsfml-network -std=c++14