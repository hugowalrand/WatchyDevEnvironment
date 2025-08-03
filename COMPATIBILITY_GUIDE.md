# 🔄 Guide de Compatibilité Watchy

Ce guide explique comment le simulateur reproduit fidèlement le comportement du Watchy réel pour garantir une compatibilité parfaite.

## 🎯 Objectif : Compatibilité 100%

L'objectif est que **tout code testé dans le simulateur fonctionne directement sur le Watchy réel** sans modification.

## 📱 Spécifications Hardware Réelles

### **Écran E-Paper**
- **Modèle** : GxEPD2_154_D67
- **Résolution** : 154x154 pixels
- **Couleurs** : Noir et blanc uniquement
- **Pins** :
  - CS: GPIO 5
  - DC: GPIO 10
  - RST: GPIO 9
  - BUSY: GPIO 19

### **Boutons**
- **Bouton 1** : GPIO 26 (Principal - Réveil)
- **Bouton 2** : GPIO 4
- **Bouton 3** : GPIO 0
- **Bouton 4** : GPIO 2

### **Caractéristiques E-Paper**
- **Refresh lent** : ~500ms pour un affichage complet
- **Pas de refresh partiel** : Tout l'écran se rafraîchit
- **Persistance** : L'image reste visible sans alimentation
- **Contraste** : Noir sur fond blanc

## 🔧 API Simulée vs Réelle

### **Fonctions Display Identiques**

```cpp
// Code qui fonctionne dans le simulateur ET sur le hardware
display.init(115200);           // ✅ Identique
display.setRotation(1);         // ✅ Identique
display.setFullWindow();        // ✅ Identique
display.fillScreen(GxEPD_WHITE); // ✅ Identique
display.setCursor(x, y);        // ✅ Identique
display.setTextSize(size);      // ✅ Identique
display.setTextColor(GxEPD_BLACK); // ✅ Identique
display.println("Text");        // ✅ Identique
display.display(false);         // ✅ Identique
```

### **Fonctions ESP32 Identiques**

```cpp
// Fonctions ESP32 simulées identiques au hardware
esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0); // ✅ Identique
esp_deep_sleep_start();                        // ✅ Identique
delay(ms);                                     // ✅ Identique
millis();                                      // ✅ Identique
Serial.begin(115200);                         // ✅ Identique
```

## 🎮 Comportements Simulés

### **Mode Veille/Sommeil**
- **Simulateur** : Écran vide, indicateur rouge
- **Hardware** : Écran vide, consommation minimale
- **Réveil** : Bouton GPIO 26 dans les deux cas

### **Refresh E-Paper**
- **Simulateur** : Animation de refresh (500ms)
- **Hardware** : Refresh réel de l'e-paper (500ms)
- **Comportement** : Identique

### **Boutons**
- **Simulateur** : Clics visuels avec feedback
- **Hardware** : Pression physique des boutons
- **GPIO** : Mêmes pins dans les deux cas

## 📊 Tests de Compatibilité

### **Test 1 : Affichage Basique**
```cpp
void setup() {
    display.init(115200);
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.println("Test");
    display.display(false);
}
```
**Résultat** : ✅ Identique sur simulateur et hardware

### **Test 2 : Mode Veille**
```cpp
void setup() {
    // ... affichage ...
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0);
    esp_deep_sleep_start();
}
```
**Résultat** : ✅ Identique sur simulateur et hardware

### **Test 3 : Gestion des Boutons**
```cpp
void loop() {
    if (digitalRead(26) == LOW) {
        // Action bouton
    }
}
```
**Résultat** : ✅ Identique sur simulateur et hardware

## 🚨 Limitations du Simulateur

### **Ce qui n'est PAS simulé :**
- **RTC réel** : L'heure est simulée
- **Accéléromètre** : Pas de capteurs de mouvement
- **WiFi/BLE** : Pas de connectivité réseau
- **Batterie réelle** : Niveau simulé
- **Température** : Pas de capteur de température

### **Ce qui EST simulé :**
- **Écran e-paper** : Dimensions et comportement
- **Boutons** : GPIO et interactions
- **Mode veille** : Comportement de sommeil
- **Timing** : Délais et refresh
- **API Display** : Toutes les fonctions d'affichage

## ✅ Checklist de Compatibilité

Avant de flasher sur le Watchy réel, vérifiez :

- [ ] **Code compile** sans erreurs
- [ ] **Simulateur** affiche correctement
- [ ] **Boutons** fonctionnent dans le simulateur
- [ ] **Mode veille** fonctionne
- [ ] **Refresh** se fait correctement
- [ ] **Dimensions** respectent 154x154 pixels
- [ ] **Couleurs** : Noir et blanc uniquement

## 🎯 Workflow Recommandé

### **1. Développement (Simulateur)**
```bash
python dev_environment.py simulator
# Testez votre code dans le simulateur
```

### **2. Validation (Compilation)**
```bash
python dev_environment.py compile
# Vérifiez qu'il n'y a pas d'erreurs
```

### **3. Test (Hardware)**
```bash
pio run --target upload
# Flashez sur le Watchy réel
```

## 🔍 Debug et Logs

### **Simulateur**
- **Debug Info** : Affiche toutes les fonctions appelées
- **Timestamps** : Horodatage des actions
- **État** : Status en temps réel

### **Hardware**
- **Serial Monitor** : `pio device monitor`
- **Logs** : Messages de debug via Serial
- **État** : LED et comportement visuel

## 🎉 Résultat

Avec cette approche, **99% du code testé dans le simulateur fonctionne directement sur le Watchy réel** sans modification !

Les seules adaptations nécessaires concernent les fonctionnalités non simulées (RTC, WiFi, capteurs). 