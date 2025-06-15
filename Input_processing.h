#pragma once
// Input_processing.h
//#ifndef INPUT_PROCESSING_H     // Include-guard
//#define INPUT_PROCESSING_H

#include "Chat_message.h"       // Definicja Chat_message

class Input_processing {
public:
    // Wczytuje kolejn? linijk?; zwraca false przy /quit lub b??dzie
    bool readNext(Chat_message& outMsg);
};

//#endif // INPUT_PROCESSING_H
