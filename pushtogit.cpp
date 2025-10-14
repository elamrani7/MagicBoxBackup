#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

void pushToGitHub(const std::string& repoPath) {
    std::string date;
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timeNow));
    date = buffer;

    // Vérifie si le dossier est un dépôt Git
    if (!fs::exists(repoPath + "/.git")) {
        std::cerr << "[MagicBoxRogue] Erreur : le dossier n'est pas un dépôt Git." << std::endl;
        return;
    }

    std::string cdCommand =
#ifdef _WIN32
        "cd /d \"" + repoPath + "\" && ";
#else
        "cd \"" + repoPath + "\" && ";
#endif

    std::string gitCommands =
        cdCommand +
        "git add . && " +
        "git commit -m \"Backup Workshop " + date + "\" && " +
        "git push";

    int result = std::system(gitCommands.c_str());

    if (result == 0) {
        std::cout << "[MagicBoxRogue] Sauvegarde GitHub réussie." << std::endl;
    } else {
        std::cerr << "[MagicBoxRogue] Échec du push Git. Vérifiez votre configuration Git et vos droits d'accès." << std::endl;
    }
}
