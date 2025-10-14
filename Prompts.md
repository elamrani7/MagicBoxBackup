Prompts utilisés pour construire le projet MagicBoxRogue
🎯 Objectif du projet
Créer une interface graphique en C++ avec ImGui permettant de sauvegarder automatiquement un dossier local vers un dépôt GitHub, avec gestion des commits, des pushs, des erreurs système, et une interface fluide — le tout piloté par des prompts IA.

1 Prompt pour initialiser le projet

💬 Prompt à donner à Claud ia (dans VS Code ou cursor)

“Agis comme un ingénieur logiciel senior.
Crée un projet C++ cross-platform (Windows/Linux) utilisant CMake.
Le projet doit être nommé MagicBoxRogue.
Il doit contenir un fichier principal main.cpp et un CMakeLists.txt minimal permettant de compiler le projet sur les deux systèmes.
Propose-moi la structure complète du dossier du projet avec les fichiers nécessaires.”

2 Prompt pour générer le contenu du CMakeLists.txt

💬 Prompt :

“Génère un fichier CMakeLists.txt compatible Linux et Windows pour le projet MagicBoxRogue.
Le projet doit compiler tous les fichiers C++ du dossier src/, utiliser la norme C++17 et générer un exécutable magicbox.
Ajoute des commentaires dans le fichier pour expliquer chaque section.”

3️⃣ Prompt pour le programme principal (main.cpp)

💬 Prompt :

“Écris le code C++ du fichier main.cpp pour un programme nommé MagicBoxRogue qui :

Demande à l’utilisateur le chemin du dossier contenant ses fichiers du Workshop (sources).

Exécute des commandes Git pour ajouter, commit et push automatiquement les fichiers sur un dépôt GitHub existant.

Affiche un message de succès ou d’erreur.
Le code doit fonctionner sous Linux et Windows. Utilise des fonctions standard et détecte le système d’exploitation via des directives de préprocesseur.
Fournis le code complet avec les include nécessaires.”


4️⃣ Prompt pour la partie Git automatique

💬 Prompt :

“Ajoute au programme une fonction C++ nommée pushToGitHub() qui :

Vérifie si le dossier courant est un dépôt Git

Exécute les commandes git add ., git commit -m "Backup Workshop <date>", git push

Capture et affiche les erreurs éventuelles.

Doit fonctionner sur Linux et Windows.
Donne-moi le code complet de cette fonction avec des explications.”

🪶 5️⃣ Prompt pour créer un README professionnel


“Rédige un fichier README.md professionnel pour le projet MagicBoxRogue.
Il doit expliquer :

le contexte du Workshop ‘Poudlard à l’EPSI/WIS’

l’objectif du projet (sauvegarde automatique de sources sur GitHub)

les technologies utilisées (C++, CMake, Git)

les instructions pour compiler et exécuter sous Linux et Windows.

un exemple d’utilisation du programme.”


6️⃣ Prompt pour documenter le projet

💬 Prompt :

“Génère une documentation simple au format Markdown expliquant le fonctionnement du projet MagicBoxRogue :

Schéma des fichiers

Description des principales fonctions

Exemple de commande CMake pour compiler le projet

Étapes du push automatique vers GitHub.
Le ton doit être clair, professionnel et adapté à une présentation de workshop.”


AUTRES :

🔹 Interface graphique et structure du projet
"Je veux une interface en C++ avec ImGui qui permet de sélectionner un dossier et de le sauvegarder dans un dossier local nommé backup_WorkshopFiles."

"Comment structurer mon projet C++ avec GLFW, ImGui et std::filesystem pour gérer des backups de fichiers ?"

🔹 Copie de fichiers et gestion des erreurs
"Donne-moi une fonction C++ qui copie tous les fichiers d’un dossier source vers un dossier de backup, en recréant l’arborescence."

"Comment gérer les erreurs lors de la copie avec std::filesystem::copy_file et afficher les messages dans l’interface ?"

🔹 Git automatisé en ligne de commande
"Ajoute une fonction qui initialise un dépôt Git, ajoute un remote, fait un pull --rebase, commit et push automatiquement."

"Pourquoi git remote add échoue silencieusement ? Comment vérifier si le remote existe déjà avant de l’ajouter ?"

"Comment afficher dans l’interface un message clair si le git pull échoue à cause de commits distants non présents localement ?"

🔹 Suppression du dossier de backup
"Je veux écraser le dossier de backup précédent, mais seulement après confirmation dans l’interface. Comment gérer ça avec ImGui ?"

"Comment éviter l’erreur 'access denied' lors de la suppression d’un dossier avec std::filesystem::remove_all sur Windows ?"

"Donne-moi une fonction C++ qui supprime tous les fichiers et sous-dossiers d’un dossier sans supprimer le dossier lui-même."

🔹 Stratégie alternative sans suppression
"Est-ce que je peux simplement écraser le contenu du dossier sans le supprimer entièrement pour éviter les erreurs système ?"

"Comment nettoyer le contenu d’un dossier en C++ sans toucher à ses permissions ou métadonnées ?"

🔹 Interface utilisateur fluide
"Je veux supprimer le bouton de confirmation et lancer le backup directement avec un seul bouton dans ImGui."

"Comment désactiver le bouton pendant l’exécution du backup pour éviter les doublons ?"

"Comment afficher les logs dans une zone scrollable avec ImGui::TextWrapped ?"

🔹 Multithreading et fluidité
"Comment lancer performBackup() dans un thread détaché pour ne pas bloquer l’interface ImGui ?"