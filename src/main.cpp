#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// D2 (GIPO4)
DHT my_sensor(4, DHT22);

Adafruit_SSD1306 *display = nullptr; // Použijeme ukazatel, původní objekt neexistuje na globální úrovni
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float humidity, temperature;

void setup() {
    // Wire.begin(4,5);
    // Nastavení I2C sběrnice na D1 (GPIO5) pro SCL a D3 (GPIO0) pro SDA
    Wire.begin(0, 5);
    display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
    display->begin(SSD1306_SWITCHCAPVCC, 0x3C);

    // zapnutí senzoru
    my_sensor.begin();
}

void loop() {
    // reaguji každou sekundu
    if (millis() % 1000 == 0) {
        humidity = my_sensor.readHumidity();
        temperature = my_sensor.readTemperature();

        // vyčistím display
        display->clearDisplay();
        //display->setTextSize(1);
        //display->setFont(&FreeSans9pt7b);
        // display->setCursor(10, 15 + 10); // 15 je baseline
        display->setFont();
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(5, 10);
        display->println("Humidity: " + String(humidity, 2) + "%");
        display->setCursor(5, 20);
        display->println("Temperature: " + String(temperature, 2) + "C");

        // vytvořím čtverec kolem celého displaye
        display->drawRect(0, 0, 128, 64, SSD1306_WHITE);

        display->setFont();
        display->setCursor(5, 35);

        unsigned long sec = millis() / 1000;
        unsigned int days = sec / 86400; // 1 den = 86400 sekund
        unsigned int hours = (sec % 86400) / 3600; // Zbytek po dnech, přepočítat na hodiny
        unsigned int minutes = (sec % 3600) / 60;  // Zbytek po hodinách, přepočítat na minuty
        unsigned int seconds = sec % 60;

        String timeString = String(days) + ":" +
                            String(hours) + ":" +
                            String(minutes) + ":" +
                            String(seconds);

        display->println("Active: " + timeString);
        display->display();
    }
}