// Peer_to_peer.cpp
#include "Peer_to_peer.h"
#include <iostream>            // std::cout, std::cerr

// Konstruktor: ustawiamy na INVALID_SOCKET
Peer_to_peer::Peer_to_peer() : sock(INVALID_SOCKET) {}

// Destruktor: je?li socket otwarty, zamknij
Peer_to_peer::~Peer_to_peer() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }
}

// Inicjalizacja jako serwer TCP
void Peer_to_peer::initAsServer(int port) {
    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Tworzymy socket
    if (listenSock == INVALID_SOCKET) throw std::runtime_error("Failed to create socket");

    sockaddr_in service{};                  // Struktura adresowa
    service.sin_family = AF_INET;           // IPv4
    service.sin_addr.s_addr = INADDR_ANY;   // Dowolny interfejs
    service.sin_port = htons(port);         // Port z konwersj?

    if (bind(listenSock, reinterpret_cast<sockaddr*>(&service), sizeof(service)) == SOCKET_ERROR) {
        closesocket(listenSock);
        throw std::runtime_error("Bind failed");
    }

    if (listen(listenSock, 1) == SOCKET_ERROR) { // Nas?uchujemy (kolejka 1)
        closesocket(listenSock);
        throw std::runtime_error("Listen failed");
    }

    std::cout << "Server listening on port " << port << "...\n";
    SOCKET clientSock = accept(listenSock, nullptr, nullptr); // Akceptujemy jedno po??czenie
    if (clientSock == INVALID_SOCKET) {
        closesocket(listenSock);
        throw std::runtime_error("Accept failed");
    }

    closesocket(listenSock);                // Zamykamy socket nas?uchuj?cy
    sock = clientSock;                      // Przypisujemy dzia?aj?cy socket
    std::cout << "Client connected.\n";
}

// Inicjalizacja jako klient TCP
void Peer_to_peer::initAsClient(const std::string& ip, int port) {
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Tworzymy socket
    if (sock == INVALID_SOCKET) throw std::runtime_error("Failed to create socket");

    sockaddr_in serverAddr{};                // Struktura adresowa serwera
    serverAddr.sin_family = AF_INET;         // IPv4
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr); // Konwersja IP
    serverAddr.sin_port = htons(port);       // Port w sieciowym porz?dku bajtów

    if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(sock);
        throw std::runtime_error("Connection failed");
    }
    std::cout << "Connected to server.\n";
}

// Wysy?a Chat_message: najpierw d?ugo??, potem dane
void Peer_to_peer::sendData(const Chat_message& msg) {
    uint32_t len = htonl(static_cast<uint32_t>(msg.getLength())); // Konwersja D? na sie?
    if (::send(sock, reinterpret_cast<const char*>(&len), sizeof(len), 0) == SOCKET_ERROR)
        throw std::runtime_error("Send length failed");

    size_t total = 0;
    while (total < msg.getLength()) {       // Wysy?amy do ko?ca bufora
        int s = ::send(sock, msg.getBuffer() + total,
            static_cast<int>(msg.getLength() - total), 0);
        if (s == SOCKET_ERROR) throw std::runtime_error("Send data failed");
        total += s;
    }
}

// Odbiera Chat_message: czyta najpierw d?ugo??, potem dane
Chat_message Peer_to_peer::receiveData() {
    uint32_t len_net = 0;
    int received = ::recv(sock, reinterpret_cast<char*>(&len_net), sizeof(len_net), 0);
    if (received == 0) {
        return Chat_message();               // Po??czenie zamkni?te ? pusty msg
    }
    if (received < 0) throw std::runtime_error("Receive length failed");

    uint32_t len = ntohl(len_net);          // Konwersja na host
    Chat_message msg;
    if (len > 0) {
        char* buffer = new char[len];       // Bufor pomocniczy
        size_t total = 0;
        while (total < len) {
            int r = ::recv(sock, buffer + total, static_cast<int>(len - total), 0);
            if (r <= 0) {
                delete[] buffer;
                throw std::runtime_error("Receive data failed");
            }
            total += r;
        }
        msg.setContent(std::string(buffer, len)); // Ustaw tre??
        msg.setEncrypted(true);               // Flaga szyfrowania
        delete[] buffer;                      // Zwolnij pomocniczy bufor
    }
    return msg;
}

// Zamyka po??czenie
void Peer_to_peer::closeConnection() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
}

SOCKET Peer_to_peer::getSocket() const {
    return sock;                             // Zwraca aktywny socket
}
