#ifndef NEOPIXELMANAGER_H
#define NEOPIXELMANAGER_H

#include "Adafruit_NeoPixel.h"

class NeoPixelManager {
private:
    Adafruit_NeoPixel strip;  // Objekt NeoPixel
    uint8_t numPixels;        // Počet LED diod

    // Interní privátní funkce pro generování barev
    uint32_t Wheel(byte WheelPos);

public:
    // Konstruktor
    NeoPixelManager(uint8_t pin, uint8_t numPixels);

    // Veřejné metody
    void begin();                      // Inicializace LED
    void rainbowCycle(uint8_t interval);   // Efekt duha
    void setAllColor(uint8_t r, uint8_t g, uint8_t b); // Nastaví všechny LED na stejnou barvu
    void clear();                      // Vypne všechny LED
};

#endif