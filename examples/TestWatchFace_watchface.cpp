#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// Définition de l'écran e-paper pour Watchy
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=*/ 5, /*DC=*/ 10, /*RST=*/ 9, /*BUSY=*/ 19));

void drawWatchFace() {
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    
    // Votre code ici
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.println("TestWatchFace");
}

void setup() {
    Serial.begin(115200);
    
    // Initialisation de l'écran
    display.init(115200);
    display.setRotation(1);
    
    // Affichage du watch-face
    drawWatchFace();
    
    // Configuration du réveil
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0);
    esp_deep_sleep_start();
}

void loop() {
    // Le code ne repasse jamais ici
}
