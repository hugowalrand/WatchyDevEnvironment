# 🚀 Guide de Configuration GitHub

Ce guide vous aide à configurer votre projet Watchy Development Environment sur GitHub avec les meilleures pratiques.

## 📋 Prérequis

- Compte GitHub
- Git installé localement
- Accès en ligne de commande

## 🔧 Configuration Initiale

### 1. Configuration Git Locale

```bash
# Configurer votre identité Git
git config --global user.name "Votre Nom"
git config --global user.email "votre.email@example.com"

# Vérifier la configuration
git config --list
```

### 2. Créer le Repository GitHub

1. **Allez sur GitHub.com**
2. **Cliquez sur "New repository"**
3. **Configurez le repository :**
   - **Nom** : `WatchyDevEnvironment`
   - **Description** : `Environnement de développement complet pour créer et tester des watch-faces Watchy sans hardware`
   - **Visibilité** : Public (recommandé)
   - **Ne pas initialiser** avec README (déjà créé)

### 3. Lier le Repository Local à GitHub

```bash
# Ajouter le remote GitHub
git remote add origin https://github.com/votre-username/WatchyDevEnvironment.git

# Vérifier le remote
git remote -v

# Pousser le code initial
git push -u origin main
```

## 🏷️ Configuration des Releases

### 1. Pousser les Tags

```bash
# Pousser le tag v1.0.0
git push origin v1.0.0

# Pour les futures releases
git push origin --tags
```

### 2. Créer une Release sur GitHub

1. **Allez dans votre repository**
2. **Cliquez sur "Releases"**
3. **Cliquez sur "Create a new release"**
4. **Configurez la release :**
   - **Tag** : `v1.0.0`
   - **Titre** : `v1.0.0 - Initial Release`
   - **Description** : Copiez le contenu de `VERSION.md`

## 📝 Configuration des Issues

### 1. Templates d'Issues

Créez le dossier `.github/ISSUE_TEMPLATE/` avec :

#### `bug_report.md`
```markdown
---
name: Bug report
about: Signaler un bug dans le simulateur ou l'environnement
title: '[BUG] '
labels: bug
assignees: ''
---

**Description du bug**
Description claire et concise du bug.

**Étapes pour reproduire**
1. Aller à '...'
2. Cliquer sur '....'
3. Faire défiler jusqu'à '....'
4. Voir l'erreur

**Comportement attendu**
Description de ce qui devrait se passer.

**Captures d'écran**
Si applicable, ajoutez des captures d'écran.

**Environnement :**
 - OS: [ex: macOS, Windows, Linux]
 - Version Python: [ex: 3.8, 3.9]
 - Version PlatformIO: [ex: 6.1.0]
 - Version Watchy: [ex: V2.0]

**Informations supplémentaires**
Tout autre contexte sur le problème.
```

#### `feature_request.md`
```markdown
---
name: Feature request
about: Suggérer une nouvelle fonctionnalité
title: '[FEATURE] '
labels: enhancement
assignees: ''
---

**Votre demande de fonctionnalité est-elle liée à un problème ?**
Description claire et concise du problème.

**Décrivez la solution souhaitée**
Description claire et concise de ce que vous voulez.

**Décrivez les alternatives envisagées**
Description claire et concise des solutions alternatives.

**Contexte supplémentaire**
Tout autre contexte ou captures d'écran.
```

## 🔄 Configuration des Actions GitHub

### 1. Tests Automatisés

Créez `.github/workflows/tests.yml` :

```yaml
name: Tests

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Set up Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.9'
    
    - name: Install PlatformIO
      run: |
        python -m pip install --upgrade pip
        pip install platformio
    
    - name: Run tests
      run: |
        python dev_environment.py test
        python dev_environment.py compile
    
    - name: Check simulator
      run: |
        python -c "import webbrowser; print('Simulator check passed')"
```

### 2. Build et Release

Créez `.github/workflows/release.yml` :

```yaml
name: Build and Release

on:
  push:
    tags:
      - 'v*'

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Set up Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.9'
    
    - name: Install PlatformIO
      run: |
        python -m pip install --upgrade pip
        pip install platformio
    
    - name: Build firmware
      run: python dev_environment.py compile
    
    - name: Create Release Assets
      run: |
        mkdir -p release
        cp .pio/build/watchy/firmware.bin release/
        cp -r examples/ release/
        cp README.md release/
        cp VERSION.md release/
    
    - name: Upload Release Assets
      uses: actions/upload-artifact@v3
      with:
        name: watchy-firmware-${{ github.ref_name }}
        path: release/
```

## 📊 Configuration des Insights

### 1. Badges

Ajoutez ces badges dans votre `README.md` :

```markdown
[![Tests](https://github.com/votre-username/WatchyDevEnvironment/workflows/Tests/badge.svg)](https://github.com/votre-username/WatchyDevEnvironment/actions)
[![Release](https://github.com/votre-username/WatchyDevEnvironment/workflows/Build%20and%20Release/badge.svg)](https://github.com/votre-username/WatchyDevEnvironment/releases)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Python 3.9+](https://img.shields.io/badge/python-3.9+-blue.svg)](https://www.python.org/downloads/)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-6.1.0+-green.svg)](https://platformio.org/)
```

### 2. Statistiques

Activez les insights dans votre repository :
- **Settings** → **Options** → **Features**
- Cochez "Wikis", "Issues", "Discussions"

## 🎯 Workflow de Développement

### 1. Branches

```bash
# Branche principale
git checkout main

# Branche de développement
git checkout -b develop
git push -u origin develop

# Branche pour une fonctionnalité
git checkout -b feature/nouvelle-fonctionnalite
```

### 2. Pull Requests

1. **Développez** sur votre branche feature
2. **Testez** localement
3. **Poussez** votre branche
4. **Créez** une Pull Request
5. **Décrivez** les changements
6. **Attendez** la review

### 3. Releases

```bash
# Utiliser le script de version
python scripts/version_manager.py release minor "Nouvelle fonctionnalité"

# Ou manuellement
git tag v1.1.0
git push origin v1.1.0
```

## 📚 Documentation

### 1. Wiki

Créez un Wiki avec :
- **Installation** : Guide d'installation détaillé
- **Tutoriels** : Exemples pas à pas
- **FAQ** : Questions fréquentes
- **API Reference** : Documentation technique

### 2. Discussions

Activez les discussions pour :
- **Questions** : Aide utilisateur
- **Idées** : Suggestions d'amélioration
- **Showcase** : Partage de watch-faces

## 🔒 Sécurité

### 1. Security Policy

Créez `SECURITY.md` :

```markdown
# Security Policy

## Supported Versions

| Version | Supported          |
| ------- | ------------------ |
| 1.x.x   | :white_check_mark: |
| < 1.0   | :x:                |

## Reporting a Vulnerability

Si vous trouvez une vulnérabilité, contactez-nous à :
- Email: security@votre-domaine.com
- Issue privée: [Créer une issue privée](https://github.com/votre-username/WatchyDevEnvironment/security/advisories/new)

Nous répondrons dans les 48h.
```

### 2. Dependabot

Activez Dependabot pour les mises à jour automatiques :
- **Settings** → **Security & analysis**
- Activez "Dependency graph" et "Dependabot alerts"

## 🎉 Résultat

Avec cette configuration, votre projet aura :
- ✅ **Tests automatisés** à chaque commit
- ✅ **Releases automatiques** avec assets
- ✅ **Documentation complète** avec Wiki
- ✅ **Support communautaire** avec Discussions
- ✅ **Sécurité renforcée** avec Dependabot
- ✅ **Workflow professionnel** avec PR et reviews

Votre projet sera prêt pour une communauté open-source ! 🚀 