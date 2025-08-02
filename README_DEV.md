# 🕐 Environnement de Développement Watchy

Cet environnement vous permet de développer et tester des watch-faces pour le Watchy **sans avoir la carte physique** !

## 🚀 Démarrage Rapide

### 1. Lancez le simulateur web
```bash
python dev_environment.py simulator
```
Cela ouvrira un simulateur dans votre navigateur qui reproduit l'écran e-paper du Watchy.

### 2. Testez votre code
```bash
python dev_environment.py compile
```
Compile votre firmware pour vérifier qu'il n'y a pas d'erreurs.

### 3. Créez un nouveau watch-face
```bash
python dev_environment.py new "MonHorloge"
```

## 🛠️ Outils Disponibles

### 📱 Simulateur Web
- **Fichier** : `simulator/index.html`
- **Fonctionnalités** :
  - Écran e-paper 154x154 pixels
  - Bouton de réveil simulé
  - Mode veille/sommeil
  - Tests d'affichage en temps réel

### 🧪 Tests Unitaires
- **Fichier** : `test/test_watchy.cpp`
- **Tests inclus** :
  - Initialisation de l'écran
  - Affichage de texte
  - Fonctionnalités de sommeil
  - Réveil par bouton

### 📚 Exemples
- **Dossier** : `examples/`
- **Exemples disponibles** :
  - `clock_face.cpp` - Horloge avec affichage de l'heure
  - Templates pour nouveaux watch-faces

## 🎯 Workflow de Développement

### 1. **Développement** (Sans Watchy)
```bash
# Lancez le simulateur
python dev_environment.py simulator

# Créez un nouveau watch-face
python dev_environment.py new "MonProjet"

# Testez la compilation
python dev_environment.py compile

# Lancez les tests
python dev_environment.py test
```

### 2. **Test sur Simulateur**
- Modifiez votre code dans `src/main.cpp`
- Vérifiez le résultat dans le simulateur web
- Testez les interactions bouton
- Validez l'affichage

### 3. **Préparation pour le Hardware**
- Votre code est déjà compatible avec le vrai Watchy
- Quand vous recevez votre Watchy :
  ```bash
  pio run --target upload
  ```

## 📋 Spécifications Techniques

### Écran E-Paper
- **Résolution** : 154x154 pixels
- **Couleurs** : Noir et blanc
- **Pins** : CS(5), DC(10), RST(9), BUSY(19)

### Boutons
- **Bouton principal** : GPIO 26
- **Fonction** : Réveil du mode veille

### Modes de Fonctionnement
- **Actif** : Affichage et interactions
- **Veille** : Économie d'énergie
- **Réveil** : Par bouton ou timer

## 🔧 Commandes Utiles

```bash
# Afficher l'aide
python dev_environment.py help

# Lister les exemples
python dev_environment.py examples

# Compiler le firmware
python dev_environment.py compile

# Lancer les tests
python dev_environment.py test

# Créer un nouveau watch-face
python dev_environment.py new "NomDuProjet"
```

## 📁 Structure du Projet

```
WatchyTest/
├── src/
│   └── main.cpp              # Code principal
├── simulator/
│   └── index.html            # Simulateur web
├── test/
│   └── test_watchy.cpp       # Tests unitaires
├── examples/
│   ├── clock_face.cpp        # Exemple d'horloge
│   └── *_watchface.cpp       # Vos watch-faces
├── platformio.ini            # Configuration PlatformIO
├── dev_environment.py        # Script de développement
└── README_DEV.md             # Ce fichier
```

## 🎨 Créer un Watch-Face

### Template de Base
```cpp
#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>

GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(5, 10, 9, 19));

void drawWatchFace() {
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    
    // Votre code ici
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.println("Mon Watch-Face");
}

void setup() {
    Serial.begin(115200);
    display.init(115200);
    display.setRotation(1);
    drawWatchFace();
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0);
    esp_deep_sleep_start();
}

void loop() {
    // Vide - le Watchy s'endort
}
```

## 🚨 Limitations du Simulateur

- **Pas de RTC réel** : L'heure est simulée
- **Pas de capteurs** : Accéléromètre, etc. non disponibles
- **Pas de WiFi/BLE** : Connexions réseau non simulées
- **Performance** : L'affichage est plus rapide que l'e-paper réel

## ✅ Avantages

- **Développement rapide** : Pas besoin d'attendre le hardware
- **Tests immédiats** : Résultats visuels instantanés
- **Code compatible** : Fonctionne directement sur le vrai Watchy
- **Environnement complet** : Tests, compilation, exemples

## 🎯 Prochaines Étapes

1. **Explorez le simulateur** pour comprendre l'interface
2. **Créez votre premier watch-face** avec `python dev_environment.py new "Test"`
3. **Testez différentes fonctionnalités** dans le simulateur
4. **Préparez votre code** pour le vrai Watchy

Quand vous recevrez votre Watchy, votre code sera déjà prêt ! 🎉 