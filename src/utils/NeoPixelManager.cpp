#include "NeoPixelManager.h"

// Konstruktor
NeoPixelManager::NeoPixelManager(uint8_t pin, uint8_t numPixels)
        : strip(numPixels, pin, NEO_GRB + NEO_KHZ800), numPixels(numPixels) {}

// Inicializace LED
void NeoPixelManager::begin() {
    strip.begin(); // Inicializace NeoPixel
    strip.show();  // Zajistí, že všechny LED budou vypnuté
}

// Efekt "Duha"
void NeoPixelManager::rainbowCycle(uint8_t interval) {
    static unsigned long previousMillis = 0;
    static uint16_t j = 0; // Sleduje aktuální pozici duhového efektu

    unsigned long currentMillis = millis();

    // Kontrolujeme, zda je čas na další krok
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Generování barev pro aktuální krok
        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel((i * 256 / strip.numPixels() + j) & 255));
        }

        strip.show(); // Zobrazit aktualizovanou barvu

        j++; // Posun v efektu duhy
        if (j >= 256 * 5) { // Po 5 cyklech resetujeme efekt
            j = 0;
        }
    }
}

// Nastavení jedné barvy pro všechny LED
void NeoPixelManager::setAllColor(uint8_t r, uint8_t g, uint8_t b) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
}

// Vypnutí všech LED
void NeoPixelManager::clear() {
    setAllColor(0, 0, 0);
}

// Generování RGB barev na základě pozice na kole
uint32_t NeoPixelManager::Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}