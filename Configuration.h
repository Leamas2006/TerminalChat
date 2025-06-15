#pragma once
// Configuration.h
//#ifndef CONFIGURATION_H      // Include-guard
//#define CONFIGURATION_H

#include <string>             // std::string

class Configuration {
private:
    bool isHost;              // Tryb: host (true) lub client (false)
    std::string ip;           // Adres IP
    int port;                 // Port
    std::string password;     // Has?o czatu
    std::string nickname;     // Nick u?ytkownika

public:
    void configure();         // Metoda do pobrania ustawie? od u?ytkownika
    void showInfo() const;    // Wy?wietla informacje o trybie

    bool hostMode() const;            // Getter isHost
    const std::string& getIp() const; // Getter ip
    int getPort() const;              // Getter port
    const std::string& getPassword() const; // Getter password
    const std::string& getNickname() const; // Getter nickname
};

//#endif // CONFIGURATION_H
