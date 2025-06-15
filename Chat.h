#pragma once
// Chat.h
//#ifndef CHAT_H                  // Include-guard
//#define CHAT_H

#include "Configuration.h"      // Konfiguracja (mode, IP, port, password, nick)
#include "Peer_to_peer.h"       // Klasa po??czenia
#include "Input_processing.h"   // Wczytywanie wej?cia
#include "ContactManager.h"     // Zarz?dzanie kontaktami
#include "Cipher.h"             // Interfejs szyfru
#include <atomic>               // std::atomic<bool>
#include <thread>               // std::thread

class Chat {
private:
    Configuration config;      // Obiekt konfiguracji
    Peer_to_peer connection;   // Po??czenie P2P
    Input_processing input;    // Przetwarzanie wej?cia
    ContactManager contacts;   // Mened?er kontaktów
    Cipher* cipher;            // Wska?nik na szyfr (polimorficznie)
    std::atomic<bool> running; // Flaga p?tli

public:
    Chat(Cipher* c);           // Konstruktor: przekazujemy szyfr
    void start();              // Konfiguracja + nawi?zanie + flow
    void flow();               // G?ówna p?tla: odbiór i wysy?ka
    void stop();               // Zako?czenie: zamkni?cie + zapis kontaktów
};

//#endif // CHAT_H
