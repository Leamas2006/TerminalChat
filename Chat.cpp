// Chat.cpp
#include "Chat.h"               // Definicja klasy Chat
#include "Chat_message.h"       // Potrzebne do tworzenia wiadomo?ci
#include <iostream>             // std::cout, std::cerr
#include <sstream>              // std::ostringstream
#include <ctime>                // std::time
#include <winsock2.h>           // getpeername
#include <ws2tcpip.h>           // sockaddr_in, inet_ntop

// Konstruktor: przypisujemy szyfr i ustawiamy running=false
Chat::Chat(Cipher* c)
    : cipher(c), running(false) {
}

// Start: konfiguracja, wczytanie kontaktów, init po??czenia, flow, stop
void Chat::start() {
    config.configure();        // Pobierz od u?ytkownika ustawienia
    config.showInfo();         // Poka? komunikat o trybie/IP/port

    contacts.load("contacts.txt"); // Wczytaj kontakty z pliku

    if (config.hostMode()) {
        connection.initAsServer(config.getPort());   // Tryb host
    }
    else {
        connection.initAsClient(config.getIp(), config.getPort()); // Tryb klient
    }

    // Dodanie adresu peer’a do kontaktów
    sockaddr_in peerAddr{};
    int addrLen = sizeof(peerAddr);
    if (getpeername(connection.getSocket(),
        reinterpret_cast<sockaddr*>(&peerAddr), &addrLen) == 0) {
        char ipstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &peerAddr.sin_addr, ipstr, sizeof(ipstr)); // Konwersja adresu
        int peerPort = ntohs(peerAddr.sin_port);  // Konwersja portu
        std::ostringstream oss;
        oss << ipstr << ":" << peerPort;           // Format IP:port
        contacts.add(oss.str());                   // Dodaj do listy
    }

    flow();                              // Uruchom g?ówn? p?tl?
    stop();                              // Zako?cz i zapisz kontakty
}

// G?ówna p?tla czatu: odbiór w tle, wysy?ka w g?ównym w?tku
void Chat::flow() {
    running = true;                      // Ustaw flag?

    // W?tek odbioru
    std::thread receiveThread([&]() {
        while (running) {
            try {
                Chat_message msg = connection.receiveData(); // Odbierz
                if (msg.getLength() == 0) continue;          // Pusty ? pomi?
                msg.decrypt(*cipher, config.getPassword());  // Deszyfruj
                if (msg.getContent() == "/quit") {           // Peer wyj?cie
                    std::cout << "Peer has left the chat.\n";
                    running = false;
					connection.closeConnection(); // Zamknij po??czenie
                    break;
                }
                std::cout << msg << std::endl;               // Wypisz wiadomo??
            }
            catch (const std::exception& e) {
                std::cerr << "Receive error: " << e.what() << std::endl;
                running = false;
            }
        }
        });

    // G?ówny w?tek do wysy?ania
    while (running) {
        Chat_message msg;
        if (!input.readNext(msg)) {                           // Wczytaj od u?ytkownika
            msg.setContent("/quit");                          // Twórz komend? quit
            msg.setAuthor(config.getNickname());               // Ustaw nick
            msg.encrypt(*cipher, config.getPassword());       // Zaszyfruj
            try { connection.sendData(msg); }
            catch (...) {}   // Wy?lij
            running = false;                                  // Zako?cz
            break;
        }
        msg.setAuthor(config.getNickname());                   // Ustaw autora
        msg.encrypt(*cipher, config.getPassword());           // Szyfruj
        try {
            connection.sendData(msg);                          // Wysy?ka
        }
        catch (const std::exception& e) {
            std::cerr << "Send error: " << e.what() << std::endl;
            running = false;
            break;
        }
    }

    if (receiveThread.joinable()) {
        receiveThread.join();                                 // Czekaj na w?tek odbioru
    }
}

// Stop: zamknij socket i zapisz kontakty
void Chat::stop() {
    connection.closeConnection();      // Zamkni?cie po??czenia
    contacts.save("contacts.txt");     // Zapis listy kontaktów
    std::cout << "Chat ended. Contacts saved.\n";
}
