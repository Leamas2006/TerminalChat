// Input_processing.cpp
#include "Input_processing.h"
#include <iostream>              // std::getline, std::cout
#include <string>                // std::string

bool Input_processing::readNext(Chat_message& outMsg) {
    std::string line;
    if (!std::getline(std::cin, line)) { // Wczytaj ca?? linijk?
        return false;                     // B??d wej?cia ? koniec
    }
    if (line == "/quit") {               // Je?li polecenie wyj?cia
        return false;                    // Zako?cz czytanie
    }
    outMsg.setContent(line);             // Ustaw tre?? w Chat_message
    return true;                         // Kontynuuj
}
