#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

// Définition exacte de l'écran e-paper pour Watchy
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=*/ 5, /*DC=*/ 10, /*RST=*/ 9, /*BUSY=*/ 19));

// Variables globales
unsigned long startTime = 0;
int batteryLevel = 85;
int currentHour = 12;
int currentMinute = 34;
int currentSecond = 0;
bool isSleeping = false;

// Structure pour les données météo simulées
struct WeatherData {
    int temperature = 22;
    int humidity = 65;
    String condition = "Sunny";
} weather;

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

void drawClock() {
    // Affichage de l'heure principale
    char timeStr[10];
    sprintf(timeStr, "%02d:%02d", currentHour, currentMinute);
    
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextSize(2);
    display.setCursor(20, 40);
    display.println(timeStr);
    
    // Affichage des secondes
    display.setFont(&FreeMono9pt7b);
    display.setTextSize(1);
    sprintf(timeStr, "%02d", currentSecond);
    display.setCursor(70, 60);
    display.println(timeStr);
}

void drawBattery() {
    // Barre de batterie
    int barWidth = (batteryLevel * 30) / 100;
    display.drawRect(10, 120, 32, 8, GxEPD_BLACK);
    display.fillRect(12, 122, barWidth, 4, GxEPD_BLACK);
    
    // Pourcentage
    display.setFont(&FreeMono9pt7b);
    display.setTextSize(1);
    display.setCursor(45, 128);
    display.print(batteryLevel);
    display.print("%");
}

void drawWeather() {
    display.setFont(&FreeMono9pt7b);
    display.setTextSize(1);
    
    // Température
    display.setCursor(10, 80);
    display.print(weather.temperature);
    display.println("°C");
    
    // Condition météo
    display.setCursor(10, 95);
    display.println(weather.condition);
    
    // Humidité
    display.setCursor(10, 110);
    display.print("H: ");
    display.print(weather.humidity);
    display.println("%");
}

void drawDate() {
    display.setFont(&FreeMono9pt7b);
    display.setTextSize(1);
    display.setCursor(80, 80);
    display.println("2024-01-15");
    
    display.setCursor(80, 95);
    display.println("Monday");
}

void drawWatchFace() {
    // Configuration de l'affichage
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    
    // Dessiner les différents éléments
    drawClock();
    drawWeather();
    drawDate();
    drawBattery();
    
    // Ligne de séparation
    display.drawLine(0, 70, 154, 70, GxEPD_BLACK);
    
    // Affichage sur l'écran
    display.display(false);
}

void handleButtonPress(int buttonPin) {
    switch(buttonPin) {
        case 26: // Bouton principal
            if (isSleeping) {
                isSleeping = false;
                drawWatchFace();
            }
            break;
        case 4: // Bouton 2 - Changer l'affichage
            weather.temperature = random(15, 30);
            weather.humidity = random(40, 90);
            drawWatchFace();
            break;
        case 0: // Bouton 3 - Mode veille
            isSleeping = true;
            display.fillScreen(GxEPD_WHITE);
            display.display(false);
            break;
        case 2: // Bouton 4 - Reset
            currentHour = 12;
            currentMinute = 34;
            currentSecond = 0;
            batteryLevel = 85;
            drawWatchFace();
            break;
    }
}

void setup() {
    // Initialisation du port série
    Serial.begin(115200);
    Serial.println("Advanced Watchy starting...");
    
    // Sauvegarde du temps de démarrage
    startTime = millis();
    
    // Initialisation de l'écran
    display.init(115200);
    display.setRotation(1);
    Serial.println("Display initialized");
    
    // Configuration des boutons (simulation)
    pinMode(26, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(0, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);
    
    // Affichage initial
    drawWatchFace();
    Serial.println("Advanced watch face drawn");
    
    // Configuration du réveil
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0);
    Serial.println("Sleep mode configured");
}

void loop() {
    // Mise à jour de l'heure
    updateTime();
    
    // Vérification des boutons (simulation)
    if (digitalRead(26) == LOW) handleButtonPress(26);
    if (digitalRead(4) == LOW) handleButtonPress(4);
    if (digitalRead(0) == LOW) handleButtonPress(0);
    if (digitalRead(2) == LOW) handleButtonPress(2);
    
    // Mise à jour de l'affichage toutes les secondes
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate >= 1000) {
        if (!isSleeping) {
            drawWatchFace();
        }
        lastUpdate = millis();
        
        // Simulation de la décharge de batterie
        static int batteryCounter = 0;
        batteryCounter++;
        if (batteryCounter >= 60 && batteryLevel > 0) {
            batteryLevel--;
            batteryCounter = 0;
        }
    }
    
    // Mise en veille après 30 secondes d'inactivité
    static unsigned long lastActivity = 0;
    if (millis() - lastActivity > 30000) {
        Serial.println("Auto sleep after 30s");
        esp_deep_sleep_start();
    }
} 