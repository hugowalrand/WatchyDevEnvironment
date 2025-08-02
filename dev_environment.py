#!/usr/bin/env python3
"""
Environnement de développement Watchy
Permet de tester et développer des watch-faces sans la carte physique
"""

import os
import sys
import subprocess
import webbrowser
from pathlib import Path

class WatchyDevEnvironment:
    def __init__(self):
        self.project_root = Path(__file__).parent
        self.simulator_path = self.project_root / "simulator" / "watchy_simulator.html"
        
    def start_simulator(self):
        """Lance le simulateur web"""
        print("🚀 Lancement du simulateur Watchy...")
        if self.simulator_path.exists():
            webbrowser.open(f"file://{self.simulator_path.absolute()}")
            print("✅ Simulateur ouvert dans votre navigateur")
        else:
            print("❌ Fichier simulateur non trouvé")
            
    def run_tests(self):
        """Lance les tests unitaires"""
        print("🧪 Lancement des tests...")
        try:
            result = subprocess.run(["pio", "test"], cwd=self.project_root, capture_output=True, text=True)
            if result.returncode == 0:
                print("✅ Tests réussis")
            else:
                print("❌ Tests échoués")
                print(result.stderr)
        except FileNotFoundError:
            print("❌ PlatformIO non trouvé. Installez PlatformIO Core.")
            
    def compile_firmware(self):
        """Compile le firmware"""
        print("🔨 Compilation du firmware...")
        try:
            result = subprocess.run(["pio", "run"], cwd=self.project_root, capture_output=True, text=True)
            if result.returncode == 0:
                print("✅ Compilation réussie")
                print("📁 Firmware généré dans .pio/build/watchy/firmware.bin")
            else:
                print("❌ Compilation échouée")
                print(result.stderr)
        except FileNotFoundError:
            print("❌ PlatformIO non trouvé")
            
    def show_examples(self):
        """Affiche les exemples disponibles"""
        examples_dir = self.project_root / "examples"
        if examples_dir.exists():
            print("📚 Exemples disponibles:")
            for example in examples_dir.glob("*.cpp"):
                print(f"  - {example.stem}")
        else:
            print("📚 Aucun exemple trouvé")
            
    def create_new_watchface(self, name):
        """Crée un nouveau watch-face"""
        template = f'''#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// Définition de l'écran e-paper pour Watchy
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=*/ 5, /*DC=*/ 10, /*RST=*/ 9, /*BUSY=*/ 19));

void drawWatchFace() {{
    display.setFullWindow();
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    
    // Votre code ici
    display.setCursor(10, 30);
    display.setTextSize(2);
    display.println("{name}");
}}

void setup() {{
    Serial.begin(115200);
    
    // Initialisation de l'écran
    display.init(115200);
    display.setRotation(1);
    
    // Affichage du watch-face
    drawWatchFace();
    
    // Configuration du réveil
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0);
    esp_deep_sleep_start();
}}

void loop() {{
    // Le code ne repasse jamais ici
}}
'''
        
        watchface_path = self.project_root / "examples" / f"{name}_watchface.cpp"
        watchface_path.parent.mkdir(exist_ok=True)
        
        with open(watchface_path, 'w') as f:
            f.write(template)
            
        print(f"✅ Nouveau watch-face créé: {watchface_path}")
        
    def show_help(self):
        """Affiche l'aide"""
        print("""
🕐 Environnement de développement Watchy

Commandes disponibles:
  simulator    - Lance le simulateur web
  test         - Lance les tests unitaires
  compile      - Compile le firmware
  examples     - Liste les exemples disponibles
  new <name>   - Crée un nouveau watch-face
  help         - Affiche cette aide

Exemples d'utilisation:
  python dev_environment.py simulator
  python dev_environment.py new "MyClock"
  python dev_environment.py compile
        """)

def main():
    dev_env = WatchyDevEnvironment()
    
    if len(sys.argv) < 2:
        dev_env.show_help()
        return
        
    command = sys.argv[1].lower()
    
    if command == "simulator":
        dev_env.start_simulator()
    elif command == "test":
        dev_env.run_tests()
    elif command == "compile":
        dev_env.compile_firmware()
    elif command == "examples":
        dev_env.show_examples()
    elif command == "new" and len(sys.argv) > 2:
        dev_env.create_new_watchface(sys.argv[2])
    elif command == "help":
        dev_env.show_help()
    else:
        print("❌ Commande inconnue")
        dev_env.show_help()

if __name__ == "__main__":
    main() 