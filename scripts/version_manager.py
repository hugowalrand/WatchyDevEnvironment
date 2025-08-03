#!/usr/bin/env python3
"""
Gestionnaire de versions pour Watchy Development Environment
Automatise la création de releases et la mise à jour des versions
"""

import os
import sys
import re
import subprocess
from pathlib import Path
from datetime import datetime

class VersionManager:
    def __init__(self):
        self.project_root = Path(__file__).parent.parent
        self.version_file = self.project_root / "VERSION.md"
        self.readme_file = self.project_root / "README.md"
        
    def get_current_version(self):
        """Récupère la version actuelle depuis VERSION.md"""
        if not self.version_file.exists():
            return "0.0.0"
            
        with open(self.version_file, 'r') as f:
            content = f.read()
            match = re.search(r'## \[(\d+\.\d+\.\d+)\]', content)
            if match:
                return match.group(1)
        return "0.0.0"
    
    def update_version(self, new_version, version_type="patch"):
        """Met à jour la version dans tous les fichiers"""
        current_version = self.get_current_version()
        
        # Mise à jour de VERSION.md
        if self.version_file.exists():
            with open(self.version_file, 'r') as f:
                content = f.read()
            
            # Ajouter la nouvelle version en haut
            new_entry = f"""## [{new_version}] - {datetime.now().strftime('%Y-%m-%d')}

### 🎉 Release {new_version}
**{self.get_version_description(version_type)}**

### ✨ Changements
- Mise à jour de la version {current_version} vers {new_version}

### 🔧 Détails Techniques
- **Version précédente** : {current_version}
- **Nouvelle version** : {new_version}
- **Type de mise à jour** : {version_type}
- **Date** : {datetime.now().strftime('%Y-%m-%d')}

---

"""
            
            # Insérer la nouvelle version après le titre
            lines = content.split('\n')
            insert_index = 0
            for i, line in enumerate(lines):
                if line.startswith('## ['):
                    insert_index = i
                    break
            
            lines.insert(insert_index, new_entry)
            
            with open(self.version_file, 'w') as f:
                f.write('\n'.join(lines))
        
        # Mise à jour de README.md
        if self.readme_file.exists():
            with open(self.readme_file, 'r') as f:
                content = f.read()
            
            # Remplacer la version dans le footer
            content = re.sub(
                r'\*\*Version\*\* : \d+\.\d+\.\d+',
                f'**Version** : {new_version}',
                content
            )
            
            # Remplacer la date
            content = re.sub(
                r'\*\*Dernière mise à jour\*\* : \d{4}-\d{2}-\d{2}',
                f'**Dernière mise à jour** : {datetime.now().strftime("%Y-%m-%d")}',
                content
            )
            
            with open(self.readme_file, 'w') as f:
                f.write(content)
        
        print(f"✅ Version mise à jour : {current_version} → {new_version}")
    
    def get_version_description(self, version_type):
        """Retourne une description basée sur le type de version"""
        descriptions = {
            "major": "Changement majeur avec incompatibilités",
            "minor": "Nouvelles fonctionnalités compatibles",
            "patch": "Corrections de bugs et améliorations"
        }
        return descriptions.get(version_type, "Mise à jour")
    
    def bump_version(self, version_type="patch"):
        """Incrémente la version selon le type spécifié"""
        current = self.get_current_version()
        major, minor, patch = map(int, current.split('.'))
        
        if version_type == "major":
            major += 1
            minor = 0
            patch = 0
        elif version_type == "minor":
            minor += 1
            patch = 0
        else:  # patch
            patch += 1
        
        new_version = f"{major}.{minor}.{patch}"
        self.update_version(new_version, version_type)
        return new_version
    
    def create_release(self, version_type="patch", message=""):
        """Crée une nouvelle release"""
        new_version = self.bump_version(version_type)
        
        # Commit des changements
        subprocess.run(["git", "add", "."], cwd=self.project_root)
        
        commit_message = f"release: v{new_version}"
        if message:
            commit_message += f" - {message}"
        
        subprocess.run(["git", "commit", "-m", commit_message], cwd=self.project_root)
        
        # Créer un tag
        subprocess.run(["git", "tag", f"v{new_version}"], cwd=self.project_root)
        
        print(f"🎉 Release v{new_version} créée avec succès!")
        print(f"📝 Commit: {commit_message}")
        print(f"🏷️  Tag: v{new_version}")
        
        return new_version
    
    def show_status(self):
        """Affiche le statut actuel du projet"""
        current_version = self.get_current_version()
        
        # Vérifier le statut Git
        result = subprocess.run(["git", "status", "--porcelain"], 
                              cwd=self.project_root, capture_output=True, text=True)
        has_changes = bool(result.stdout.strip())
        
        print(f"📊 Statut du projet Watchy Development Environment")
        print(f"📍 Répertoire: {self.project_root}")
        print(f"🏷️  Version actuelle: {current_version}")
        print(f"📝 Modifications: {'Oui' if has_changes else 'Non'}")
        
        if has_changes:
            print("\n📋 Fichiers modifiés:")
            print(result.stdout)
    
    def show_help(self):
        """Affiche l'aide"""
        print("""
🕐 Gestionnaire de versions Watchy Development Environment

Commandes disponibles:
  status                    - Affiche le statut actuel
  bump [type]              - Incrémente la version (major/minor/patch)
  release [type] [message] - Crée une nouvelle release
  help                     - Affiche cette aide

Types de version:
  major                    - Changement majeur (incompatibilités)
  minor                    - Nouvelles fonctionnalités
  patch                    - Corrections de bugs (défaut)

Exemples:
  python scripts/version_manager.py status
  python scripts/version_manager.py bump patch
  python scripts/version_manager.py release minor "Ajout simulateur Wokwi"
  python scripts/version_manager.py release major "Refactorisation complète"
        """)

def main():
    manager = VersionManager()
    
    if len(sys.argv) < 2:
        manager.show_help()
        return
    
    command = sys.argv[1].lower()
    
    if command == "status":
        manager.show_status()
    elif command == "bump":
        version_type = sys.argv[2] if len(sys.argv) > 2 else "patch"
        manager.bump_version(version_type)
    elif command == "release":
        version_type = sys.argv[2] if len(sys.argv) > 2 else "patch"
        message = sys.argv[3] if len(sys.argv) > 3 else ""
        manager.create_release(version_type, message)
    elif command == "help":
        manager.show_help()
    else:
        print(f"❌ Commande inconnue: {command}")
        manager.show_help()

if __name__ == "__main__":
    main() 