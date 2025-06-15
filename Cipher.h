#pragma once
// Cipher.h
//#ifndef CIPHER_H            // Je?li nie zdefiniowano CIPHER_H, unikamy wielokrotnego do??czania pliku
//#define CIPHER_H            // Definiujemy CIPHER_H, by kolejne include’y go pomin??y

#include <cstddef>          // std::size_t
#include <string>           // std::string

// Abstrakcyjny interfejs szyfruj?cy
class Cipher {
public:
    // Metoda czysto wirtualna: szyfruje dane w buforze o podanej d?ugo?ci i kluczu
    virtual void encrypt(char* data, std::size_t len, const std::string& key) = 0;
    // Metoda czysto wirtualna: deszyfruje
    virtual void decrypt(char* data, std::size_t len, const std::string& key) = 0;
    virtual ~Cipher() {}       // Wirtualny destruktor, by poprawnie zwolni? zasoby pochodnych
};

//#endif // CIPHER_H          // Koniec include-guarda
