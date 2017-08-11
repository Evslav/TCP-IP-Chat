#!/bin/bash

echo компиляция серверной части
g++ ./server/Server.cpp ./server/Server.h ./server/server_main.cpp -o sfml-server -lsfml-system -lsfml-network -std=c++14