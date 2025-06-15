#pragma once
// Peer_to_peer.h
//#ifndef PEER_TO_PEER_H        // Include-guard
//#define PEER_TO_PEER_H

#include "Chat_message.h"    // Potrzebne do sendData/receiveData
#include <winsock2.h>         // SOCKET, funkcje Winsock
#include <ws2tcpip.h>         // inet_pton, sockaddr_in
#include <stdexcept>          // std::runtime_error
#include <string>             // std::string

#pragma comment(lib, "Ws2_32.lib") // Linkowanie z bibliotek? Winsock

class Peer_to_peer {
private:
    SOCKET sock;             // G?ówny socket po??czenia

public:
    Peer_to_peer();          // Konstruktor: ustawia INVALID_SOCKET
    ~Peer_to_peer();         // Destruktor: zamyka socket

    void initAsServer(int port);           // Inicjalizacja w trybie serwera
    void initAsClient(const std::string& ip, int port); // Inicjalizacja klienta

    void sendData(const Chat_message& msg);   // Wysy?a wiadomo??
    Chat_message receiveData();                // Odbiera wiadomo??

    void closeConnection();                // Zamyka po??czenie

    SOCKET getSocket() const;              // Zwraca SOCKET
};

//#endif // PEER_TO_PEER_H
