#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// Définition exacte de l'écran e-paper pour Watchy
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=*/ 5, /*DC=*/ 10, /*RST=*/ 9, /*BUSY=*/ 19));

// Variables globales
unsigned long startTime = 0;
int batteryLevel = 85;

void drawWatchFace() {
    // Configuration de l'affichage
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    
    // Affichage principal
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.println("Hello Watchy!");
    
    // Affichage de l'uptime
    unsigned long uptime = (millis() - startTime) / 1000;
    display.setCursor(10, 60);
    display.setTextSize(1);
    display.print("Uptime: ");
    display.print(uptime);
    display.println("s");
    
    // Affichage de la batterie
    display.setCursor(10, 80);
    display.print("Battery: ");
    display.print(batteryLevel);
    display.println("%");
    
    // Affichage de la date/heure (simulée)
    display.setCursor(10, 100);
    display.println("2024-01-15 12:34");
    
    // Affichage sur l'écran
    display.display(false);
}

void setup() {
    // Initialisation du port série
    Serial.begin(115200);
    Serial.println("Watchy starting...");
    
    // Sauvegarde du temps de démarrage
    startTime = millis();
    
    // Initialisation de l'écran
    display.init(115200);
    display.setRotation(1);
    Serial.println("Display initialized");
    
    // Affichage du watch-face
    drawWatchFace();
    Serial.println("Watch face drawn");
    
    // Configuration du réveil par bouton (GPIO 26)
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0);
    Serial.println("Sleep mode configured");
    
    // Attendre un peu pour voir l'affichage
    delay(2000);
    
    // Mise en veille
    Serial.println("Entering sleep mode...");
    esp_deep_sleep_start();
}

void loop() {
    // Le code ne repasse jamais ici car le Watchy s'endort
    // Cette fonction est vide par design
}
