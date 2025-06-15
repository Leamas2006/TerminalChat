#pragma once

#include <string>             // std::string
#include <ostream>            // std::ostream
#include "Cipher.h"           // Interfejs Cipher do metod encrypt/decrypt

class Chat_message {
private:
    
    bool encrypted;          // Flaga, czy wiadomo?? jest zaszyfrowana
    std::string author;      // Autor wiadomo?ci

public:
    Chat_message();                                      // Konstruktor domy?lny
    Chat_message(const Chat_message& other);             // Konstruktor kopiuj?cy
    Chat_message& operator=(const Chat_message& other);  // Operator przypisania
    ~Chat_message();                                     // Destruktor

    void setContent(const std::string& text);            // Ustawia tre?? (kopiuje do buffer)
    std::string getContent() const;                      // Zwraca zawarto?? jako std::string

    void setAuthor(const std::string& a);                // Ustawia autora
    std::string getAuthor() const;                       // Zwraca autora

    void setEncrypted(bool e);                           // Ustawia flag? encrypted
    bool isEncrypted() const;                            // Sprawdza, czy zaszyfrowane

    char* getBuffer() const;                             // Zwraca surowy bufor
    std::size_t getLength() const;                       // Zwraca d?ugo?? bufora

    void encrypt(Cipher& cipher, const std::string& key);// Szyfruje przez Cipher
    void decrypt(Cipher& cipher, const std::string& key);// Deszyfruje przez Cipher

    Chat_message operator+(const Chat_message& other) const;            // ??czy dwie wiadomo?ci
    friend std::ostream& operator<<(std::ostream& os, const Chat_message& msg); // Wypisuje wiadomo??
};
