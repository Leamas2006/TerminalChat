#pragma once
// ContactManager.h
//#ifndef CONTACT_MANAGER_H       // Include-guard
//#define CONTACT_MANAGER_H

#include <vector>               // std::vector
#include <string>               // std::string

class ContactManager {
private:
    std::vector<std::string> contacts; // Lista kontaktów (IP:port)

public:
    void load(const std::string& fileName);  // Wczytaj z pliku
    void save(const std::string& fileName);  // Zapisz do pliku
    void add(const std::string& contact);    // Dodaj, je?li nowy
    const std::vector<std::string>& getAll() const; // Pobierz wszystkie
};

//#endif // CONTACT_MANAGER_H
