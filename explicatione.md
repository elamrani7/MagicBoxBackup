# 🧙‍♂️ MagicBoxRogue

**MagicBoxRogue** est une application C++ avec interface graphique ImGui qui permet de sauvegarder automatiquement un dossier de travail dans un répertoire de backup local. Elle est conçue pour les étudiants, développeurs et magiciens du code souhaitant sécuriser leur projet avant de le pousser sur GitHub.

---

## ✨ Fonctionnalités

- 📁 Interface graphique simple et intuitive (ImGui + GLFW)
- 🔍 Saisie du chemin du dossier à sauvegarder
- 📦 Copie complète du dossier dans un répertoire `backup_<nom>`
- 🔄 Écrasement intelligent des fichiers existants
- 🛡️ Vérification du chemin et gestion des erreurs
- 🧠 Compatible avec Git pour automatiser les commits

---

## 🖼️ Aperçu

![Interface MagicBoxRogue](assets/screenshot.png)

---

## 🚀 Lancer l'application

### Prérequis

- CMake ≥ 3.10
- MinGW ou Ninja
- GLFW
- ImGui (inclus dans `external/`)

### Compilation

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
