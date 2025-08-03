#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// Définition de l'écran e-paper pour Watchy
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=*/ 5, /*DC=*/ 10, /*RST=*/ 9, /*BUSY=*/ 19));

// Variables pour l'heure
int currentHour = 12;
int currentMinute = 34;
int currentSecond = 0;

void drawClockFace() {
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    
    // Affichage de l'heure
    char timeStr[10];
    sprintf(timeStr, "%02d:%02d", currentHour, currentMinute);
    
    display.setCursor(20, 60);
    display.setTextSize(2);
    display.println(timeStr);
    
    // Affichage des secondes
    display.setCursor(50, 80);
    display.setTextSize(1);
    sprintf(timeStr, "%02d", currentSecond);
    display.println(timeStr);
    
    // Affichage de la date (simulée)
    display.setCursor(10, 100);
    display.println("2024-01-15");
    
    display.display(false);
}

void updateTime() {
    currentSecond++;
    if (currentSecond >= 60) {
        currentSecond = 0;
        currentMinute++;
        if (currentMinute >= 60) {
            currentMinute = 0;
            currentHour++;
            if (currentHour >= 24) {
                currentHour = 0;
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
    
    // Initialisation de l'écran
    display.init(115200);
    display.setRotation(1);
    
    // Affichage initial
    drawClockFace();
    
    // Configuration du réveil
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0);
}

void loop() {
    // Simulation de la mise à jour de l'heure
    updateTime();
    drawClockFace();
    
    // Attendre 1 seconde
    delay(1000);
    
    // Mise en veille après 10 secondes
    if (currentSecond % 10 == 0) {
        esp_deep_sleep_start();
    }
} 