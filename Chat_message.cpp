#include "Chat_message.h"
#include <cstring>             // std::memcpy
#include <stdexcept>           // std::runtime_error

// Konstruktor domy?lny: brak bufora, d?ugo?? 0, niezabezpieczony
Chat_message::Chat_message()
    : buffer(nullptr), length(0), encrypted(false),
    author("") {
}

// Konstruktor kopiuj?cy: g??bokie kopiowanie bufora
Chat_message::Chat_message(const Chat_message& other)
    : buffer(nullptr), length(other.length), encrypted(other.encrypted),
    author(other.author)
{
    if (other.buffer && other.length > 0) {             // Je?li jest co kopiowa?
        buffer = new char[other.length];                // Alokujemy nowy bufor
        std::memcpy(buffer, other.buffer, other.length);// Kopiujemy zawarto??
    }
}

// Operator przypisania: usu? stary bufor, skopiuj z drugiego obiektu
Chat_message& Chat_message::operator=(const Chat_message& other) {
    if (this != &other) {
        delete[] buffer;                                 // Zwolnij poprzedni bufor
        length = other.length;
        encrypted = other.encrypted;
        author = other.author;
        buffer = nullptr;
        if (other.buffer && other.length > 0) {
            buffer = new char[other.length];             // Alokacja nowego
            std::memcpy(buffer, other.buffer, other.length);
        }
    }
    return *this;
}

// Destruktor: zwolnij bufor, je?li istnieje
Chat_message::~Chat_message() {
    delete[] buffer;
}

// Ustawia tre?? wiadomo?ci: alokuje nowy bufor, kopiuje dane
void Chat_message::setContent(const std::string& text) {
    delete[] buffer;                                     // Usu? poprzedni
    length = text.size();                                // Nowa d?ugo??
    if (length > 0) {
        buffer = new char[length];                       // Alokacja
        std::memcpy(buffer, text.data(), length);        // Kopiowanie
    }
    else {
        buffer = nullptr;
    }
    encrypted = false;                                   // Zawsze niezaszyfrowane
}

// Zwraca zawarto?? jako std::string
std::string Chat_message::getContent() const {
    return std::string(buffer, length);
}

// Setter autora
void Chat_message::setAuthor(const std::string& a) {
    author = a;
}
// Getter autora
std::string Chat_message::getAuthor() const {
    return author;
}

// Setter flagi szyfrowania
void Chat_message::setEncrypted(bool e) {
    encrypted = e;
}
// Getter flagi szyfrowania
bool Chat_message::isEncrypted() const {
    return encrypted;
}

// Zwraca wska?nik do surowego bufora
char* Chat_message::getBuffer() const {
    return buffer;
}
// Zwraca d?ugo?? bufora
std::size_t Chat_message::getLength() const {
    return length;
}

// Szyfruje, je?li istnieje bufor i jest niepusty
void Chat_message::encrypt(Cipher& cipher, const std::string& key) {
    if (buffer && length > 0) {
        cipher.encrypt(buffer, length, key);             // Wywo?anie implementacji
        encrypted = true;                                // Ustaw flag?
    }
}

// Deszyfruje, je?li zaszyfrowane
void Chat_message::decrypt(Cipher& cipher, const std::string& key) {
    if (buffer && length > 0 && encrypted) {
        cipher.decrypt(buffer, length, key);
        encrypted = false;
    }
}

// ??czenie wiadomo?ci: konkatenacja tre?ci, nowy autor + timestamp
Chat_message Chat_message::operator+(const Chat_message& other) const {
    Chat_message result;                                // Obiekt wynikowy
    std::string combined = getContent() + "\n" + other.getContent(); // Sklejamy tekst
    result.setContent(combined);                        // Ustawiamy tre??
    result.setAuthor(getAuthor() + " & " + other.getAuthor()); // ??czymy autorów
    result.setEncrypted(false);                         // Niezaszyfrowane
    return result;
}

// Wypisuje w formacie [autor]: tre??
std::ostream& operator<<(std::ostream& os, const Chat_message& msg) {
    os << "[" << msg.getAuthor() << "]: "
        << msg.getContent();
    return os;
}
