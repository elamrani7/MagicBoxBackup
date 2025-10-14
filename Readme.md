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


---

## 🚀 Lancer l'application

### Prérequis

- CMake ≥ 3.10
- MinGW 
- GLFW
- ImGui (inclus dans `external/`)

💡 Remarque : Le projet utilise std::filesystem, donc nécessite un compilateur compatible C++17 ou supérieur (ex. : g++ ≥ 8, clang ≥ 7, MSVC ≥ 2017).

cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER="C:/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/mingw64/bin/g++.exe"
github.com/glfw/glfw
github.com/ocornut/imgui

### Compilation

```bash
git clone https://github.com/ton-utilisateur/MagicBoxRogue.git
cd MagicBoxRogue
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
