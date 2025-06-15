// SimpleXorCipher.cpp
#include "SimpleXorCipher.h"   // Definicje metod SimpleXorCipher

// Szyfruje bufor XOR-em: ka?dy bajt zale?ny od klucza
void SimpleXorCipher::encrypt(char* data, std::size_t len, const std::string& key) {
    std::size_t keyLen = key.size();           // D?ugo?? klucza
    for (std::size_t i = 0; i < len; ++i) {     // Iterujemy po ka?dym bajcie
        data[i] ^= key[i % keyLen];            // XOR z odpowiednim znakiem klucza
    }
}

// Deszyfracja identyczna jak szyfracja w XOR
void SimpleXorCipher::decrypt(char* data, std::size_t len, const std::string& key) {
    encrypt(data, len, key);                   // Ponowne wywo?anie encrypt odwraca XOR
}
