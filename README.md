# 🕐 Watchy Development Environment

Un environnement de développement complet pour créer et tester des watch-faces pour le [SQFMI Watchy](https://watchy.sqfmi.com/) **sans avoir la carte physique** !

## 🚀 Fonctionnalités

- **📱 Simulateur Web Fidèle** - Reproduction exacte de l'écran e-paper 154x154
- **🔧 API 100% Compatible** - Même code pour simulateur et hardware
- **🧪 Tests Automatisés** - Validation du code avant déploiement
- **📚 Exemples Complets** - Templates et watch-faces prêts à utiliser
- **⚡ Développement Rapide** - Pas besoin d'attendre le hardware

## 📋 Prérequis

- **Python 3.7+**
- **PlatformIO Core**
- **Navigateur web moderne**

## 🛠️ Installation

### 1. Cloner le projet
```bash
git clone https://github.com/votre-username/WatchyDevEnvironment.git
cd WatchyDevEnvironment
```

### 2. Installer PlatformIO (si pas déjà fait)
```bash
pip install platformio
```

### 3. Vérifier l'installation
```bash
python dev_environment.py help
```

## 🎯 Utilisation Rapide

### Lancer le simulateur
```bash
python dev_environment.py simulator
```

### Créer un nouveau watch-face
```bash
python dev_environment.py new "MonHorloge"
```

### Compiler le firmware
```bash
python dev_environment.py compile
```

### Tester la compilation
```bash
python dev_environment.py test
```

## 📁 Structure du Projet

```
WatchyDevEnvironment/
├── src/
│   └── main.cpp                 # Code principal
├── simulator/
│   └── watchy_simulator.html    # Simulateur web fidèle
├── test/
│   └── test_watchface.cpp       # Tests unitaires
├── examples/
│   ├── clock_face.cpp           # Exemple d'horloge
│   ├── advanced_watchface.cpp   # Watch-face avancé
│   └── *_watchface.cpp          # Vos watch-faces
├── platformio.ini               # Configuration PlatformIO
├── dev_environment.py           # Script de développement
├── .gitignore                   # Fichiers à ignorer
└── README.md                    # Ce fichier
```

## 🔧 Configuration

### PlatformIO
Le projet utilise PlatformIO avec la configuration suivante :
- **Plateforme** : ESP32 6.3.2
- **Framework** : Arduino
- **Board** : Watchy
- **Build Flags** : `-DARDUINO_WATCHY_V20`

### Simulateur
- **Résolution** : 154x154 pixels (exacte)
- **GPIO** : Tous les pins du Watchy simulés
- **Timing** : Refresh e-paper réaliste (500ms)

## 🎮 Simulateur

Le simulateur reproduit fidèlement :
- ✅ **Écran e-paper** : Dimensions et comportement
- ✅ **4 boutons** : GPIO 26, 4, 0, 2
- ✅ **Mode veille** : Comportement de sommeil
- ✅ **API Display** : Toutes les fonctions
- ✅ **Debug** : Logs en temps réel

## 📊 Compatibilité

**99% de compatibilité** entre simulateur et hardware :
- Même API pour l'affichage
- Mêmes GPIO pour les boutons
- Même comportement de veille
- Code identique pour les deux environnements

## 🚀 Workflow de Développement

### 1. Développement (Simulateur)
```bash
python dev_environment.py simulator
# Testez votre code visuellement
```

### 2. Validation (Tests)
```bash
python dev_environment.py test
python dev_environment.py compile
```

### 3. Déploiement (Hardware)
```bash
pio run --target upload
# Flashez sur le Watchy réel
```

## 📚 Exemples

### Watch-face Basique
```cpp
#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>

GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(5, 10, 9, 19));

void setup() {
    display.init(115200);
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.println("Hello Watchy!");
    display.display(false);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0);
    esp_deep_sleep_start();
}

void loop() {
    // Vide - le Watchy s'endort
}
```

## 🔍 Debug

### Simulateur
- **Debug Info** : Affiche toutes les fonctions appelées
- **Timestamps** : Horodatage des actions
- **État** : Status en temps réel

### Hardware
- **Serial Monitor** : `pio device monitor`
- **Logs** : Messages de debug via Serial

## 🤝 Contribution

1. Fork le projet
2. Créez une branche pour votre fonctionnalité
3. Committez vos changements
4. Poussez vers la branche
5. Ouvrez une Pull Request

## 📄 Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## 🙏 Remerciements

- [SQFMI](https://sqfmi.com/) pour le Watchy
- [PlatformIO](https://platformio.org/) pour l'environnement de développement
- [GxEPD2](https://github.com/ZinggJM/GxEPD2) pour la bibliothèque e-paper

## 📞 Support

- **Issues** : [GitHub Issues](https://github.com/votre-username/WatchyDevEnvironment/issues)
- **Discussions** : [GitHub Discussions](https://github.com/votre-username/WatchyDevEnvironment/discussions)
- **Documentation** : [Wiki](https://github.com/votre-username/WatchyDevEnvironment/wiki)

---

**Version** : 1.0.0  
**Dernière mise à jour** : 2024-01-15  
**Compatibilité** : Watchy V2.0 