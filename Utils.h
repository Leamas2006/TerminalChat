#pragma once
// Utils.h
//#ifndef UTILS_H              // Include-guard
//#define UTILS_H

#include <string>             // std::string
#include <iostream>           // std::cout, std::getline
#include <sstream>            // std::istringstream
#include <stdexcept>          // std::runtime_error
#include <winsock2.h>         // SOCKET, gethostname
#include <ws2tcpip.h>         // inet_ntop, addrinfo, getaddrinfo, freeaddrinfo

// Szablonowa funkcja pobierania i konwersji typu T z konsoli
template<typename T>
T getUserInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;                    // Wy?wietl podpowied?
        std::string line;
        if (!std::getline(std::cin, line)) {   // Wczytaj lini?
            throw std::runtime_error("Input error"); // B??d wej?cia
        }
        std::istringstream iss(line);           // Strumie? do parsowania
        if (iss >> value) {                    // Je?li parsowanie OK
            return value;                      // Zwró? warto??
        }
        std::cout << "Invalid input. Please try again.\n"; // Ponów
    }
}

// Funkcja inline do uzyskania lokalnego adresu IPv4
inline std::string getLocalIPAddress() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        return "127.0.0.1";                   // Je?li b??d, fallback
    }
    addrinfo hints = {}, * info = nullptr;
    hints.ai_family = AF_INET;                // Tylko IPv4
    if (getaddrinfo(hostname, nullptr, &hints, &info) != 0) {
        return "127.0.0.1";
    }
    char ipstr[INET_ADDRSTRLEN];
    sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(info->ai_addr);
    inet_ntop(AF_INET, &addr->sin_addr, ipstr, sizeof(ipstr)); // Konwersja
    freeaddrinfo(info);
    return std::string(ipstr);                // Zwraca adres jako string
}

//#endif // UTILS_H
