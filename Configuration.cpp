// Configuration.cpp
#include "Configuration.h"    // Deklaracja klasy Configuration
#include "Utils.h"            // getUserInput, getLocalIPAddress
#include <iostream>           // std::cout

void Configuration::configure() {
    std::cout << "Select mode:\n1) Host (wait for connection)\n2) Client (connect to host)\n";
    int choice = getUserInput<int>("Enter choice (1 or 2): "); // Pobranie wyboru
    isHost = (choice == 1);                     // Ustawiamy tryb

    if (isHost) {
        port = getUserInput<int>("Enter port to listen on: "); // Port serwera
        ip = getLocalIPAddress();               // Uzyskaj lokalne IP
        std::cout << "Your local IP address is " << ip << "\n";
    }
    else {
        ip = getUserInput<std::string>("Enter host IP to connect: "); // IP serwera
        port = getUserInput<int>("Enter host port: ");               // Port serwera
    }

    nickname = getUserInput<std::string>("Enter your nickname: ");   // Nick
    password = getUserInput<std::string>("Enter chat password: ");   // Has?o
}

void Configuration::showInfo() const {
    if (isHost) {
        std::cout << "Waiting for connection on " << ip << ":" << port << "...\n";
    }
    else {
        std::cout << "Connecting to " << ip << ":" << port << "...\n";
    }
}

bool Configuration::hostMode() const {
    return isHost;       // Zwró? tryb hosta
}

const std::string& Configuration::getIp() const {
    return ip;           // Zwró? IP
}

int Configuration::getPort() const {
    return port;         // Zwró? port
}

const std::string& Configuration::getPassword() const {
    return password;     // Zwró? has?o
}

const std::string& Configuration::getNickname() const {
    return nickname;     // Zwró? nick
}
