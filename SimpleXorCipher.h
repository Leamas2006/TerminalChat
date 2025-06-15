#pragma once
// SimpleXorCipher.h
//#ifndef SIMPLEXORCIPHER_H    // Include-guard
//#define SIMPLEXORCIPHER_H

#include "Cipher.h"           // Do??czamy interfejs Cipher

// Prosta implementacja XOR jako symetrycznego szyfru
class SimpleXorCipher : public Cipher {
public:
    void encrypt(char* data, std::size_t len, const std::string& key) override; // Nadpisanie encrypt
    void decrypt(char* data, std::size_t len, const std::string& key) override; // Nadpisanie decrypt
};

//#endif // SIMPLEXORCIPHER_H
