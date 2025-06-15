// ContactManager.cpp
#include "ContactManager.h"
#include <fstream>              // std::ifstream, std::ofstream
#include <algorithm>            // std::find

void ContactManager::load(const std::string& fileName) {
    std::ifstream file(fileName);        // Otwieramy do odczytu
    if (!file.is_open()) return;         // Je?li brak pliku, nic nie rób
    std::string line;
    while (std::getline(file, line)) {   // Czytaj linia po linii
        if (!line.empty()) {
            contacts.push_back(line);    // Dodaj do wektora
        }
    }
}

void ContactManager::save(const std::string& fileName) {
    std::ofstream file(fileName);        // Otwórz do zapisu
    for (const auto& c : contacts) {
        file << c << "\n";               // Zapisz ka?dy kontakt
    }
}

void ContactManager::add(const std::string& contact) {
    if (std::find(contacts.begin(), contacts.end(), contact) == contacts.end()) {
        contacts.push_back(contact);     // Dodaj tylko, je?li nie ma
    }
}

const std::vector<std::string>& ContactManager::getAll() const {
    return contacts;                     // Zwró? referencj? do wektora
}
