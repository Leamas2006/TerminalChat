#include <iostream>             // std::cout, std::cerr
#include <winsock2.h>           // WSAStartup, WSACleanup
#include <ws2tcpip.h>           // Niektóre definicje Winsock2
#include <stdexcept>            // std::exception
#include "Chat.h"               // Klasa Chat
#include "SimpleXorCipher.h"    // Implementacja Cipher

#pragma comment(lib, "Ws2_32.lib")   // Linkowanie z Winsock2

int main() {
    WSADATA wsaData;
    // Inicjalizacja Winsock2 (wersja 2.2)
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n"; // Błąd inicjalizacji
        return 1;
    }

    try {
        SimpleXorCipher cipher;  // Tworzymy obiekt szyfrujący
        Chat chat(&cipher);      // Przekazujemy go do czatu
        chat.start();            // Startujemy aplikację czatu
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Obsługa wyjątków
        WSACleanup();           // Sprzątanie Winsock
        return 1;
    }

    WSACleanup();               // Zwolnienie zasobów Winsock
    return 0;                   // Zakończenie programu
}
