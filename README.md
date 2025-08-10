# TerminalChat

TerminalChat to konsolowa aplikacja typu peer-to-peer do komunikacji tekstowej, napisana w języku C++.  
Projekt został stworzony w ramach zadania uniwersyteckiego, aby zaprezentować pracę z połączeniami sieciowymi, szyfrowaniem wiadomości oraz zarządzaniem kontaktami.

## Funkcje
- Wymiana wiadomości w trybie peer-to-peer.
- Szyfrowanie wiadomości przy użyciu prostego szyfru XOR.
- Przechowywanie i zarządzanie listą kontaktów.
- Konfigurowalne parametry aplikacji za pomocą pliku ustawień.
- Działanie w trybie konsolowym bez dodatkowych bibliotek graficznych.

## Technologie i cechy języka C++ użyte w projekcie
Projekt jest przykładem wykorzystania nowoczesnych możliwości języka C++:
- Programowanie obiektowe (klasy, dziedziczenie, enkapsulacja)
- Polimorfizm i metody wirtualne
- Programowanie współbieżne (wątki, mutexy)
- Obsługa plików (`std::ifstream`, `std::ofstream`)
- Programowanie sieciowe (gniazda, komunikacja TCP/UDP)
- Szyfrowanie danych (prosty szyfr XOR)

## Struktura projektu
- `main.cpp` — punkt wejścia programu.
- `Chat.cpp / Chat.h` — logika czatu.
- `Peer_to_peer.cpp / Peer_to_peer.h` — implementacja połączenia P2P.
- `Chat_message.cpp / Chat_message.h` — struktura i obsługa wiadomości.
- `ContactManager.cpp / ContactManager.h` — zarządzanie kontaktami.
- `SimpleXorCipher.cpp / SimpleXorCipher.h` — moduł szyfrowania.
- `Configuration.cpp / Configuration.h` — ładowanie i przechowywanie ustawień.
- `Utils.h` — funkcje pomocnicze.

## Kompilacja i uruchamianie
### Wymagania
- Kompilator C++17 lub nowszy (np. g++, clang++, MSVC).
- CMake (opcjonalnie, jeśli chcesz użyć kompilacji wieloplatformowej).

### Kompilacja przy użyciu g++
```bash
g++ -std=c++17 *.cpp -o terminal_chat
./terminal_chat
