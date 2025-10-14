#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <thread>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

// ---- Bibliothèques ImGui / OpenGL ----
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// Alias pour simplifier
namespace fs = std::filesystem;

// === Variables globales ===
std::string statusMessage;
char pathBuffer[512] = "";
bool confirmOverwrite = false;
float progress = 0.0f;

// === Fonction pour journaliser les événements ===
void appendLog(const std::string& msg) {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::ofstream logFile("magicbox_log.txt", std::ios::app);
    logFile << "[" << std::put_time(std::localtime(&now), "%H:%M:%S") << "] " << msg << std::endl;
    statusMessage += msg + "\n";
    std::cout << msg << std::endl;
}

// === Générer un timestamp ===
std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", std::localtime(&timeNow));
    return std::string(buffer);
}

// === Nettoyer un dossier (en ignorant .git) ===
bool clearFolderContents(const std::string& folderPath) {
    try {
        if (!fs::exists(folderPath)) return true;

        for (const auto& entry : fs::directory_iterator(folderPath)) {
            // ✅ Ignorer le dossier .git pour éviter les erreurs de suppression
            if (entry.path().filename() == ".git")
                continue;

            fs::remove_all(entry);
        }
        appendLog("🧹 Dossier nettoyé : " + folderPath);
        return true;
    } catch (const std::exception& e) {
        appendLog("❌ Impossible de nettoyer le dossier : " + std::string(e.what()));
        return false;
    }
}

// === Copier récursivement un dossier ===
bool copyFiles(const std::string& sourcePath, const std::string& backupPath) {
    try {
        size_t totalFiles = 0, copied = 0;
        for (auto& p : fs::recursive_directory_iterator(sourcePath))
            if (fs::is_regular_file(p)) totalFiles++;

        fs::create_directories(backupPath);

        for (const auto& entry : fs::recursive_directory_iterator(sourcePath)) {
            const auto& path = entry.path();
            auto relativePath = fs::relative(path, sourcePath);
            auto targetPath = fs::path(backupPath) / relativePath;

            if (fs::is_directory(path)) {
                fs::create_directories(targetPath);
            } else if (fs::is_regular_file(path)) {
                fs::copy_file(path, targetPath, fs::copy_options::overwrite_existing);
                copied++;
                progress = static_cast<float>(copied) / totalFiles;
            }
        }

        appendLog("📦 " + std::to_string(copied) + " fichiers copiés avec succès.");
        return true;
    } catch (const std::exception& e) {
        appendLog("❌ Erreur lors de la copie : " + std::string(e.what()));
        return false;
    }
}

// === Commandes Git automatisées ===
void executeGitCommands(const std::string& rootBackupPath) {
    std::string cdCommand =
#ifdef _WIN32
        "cd /d \"" + rootBackupPath + "\" && ";
#else
        "cd \"" + rootBackupPath + "\" && ";
#endif

    try {
        // Initialisation Git si nécessaire
        if (!fs::exists(fs::path(rootBackupPath) / ".git")) {
            std::system((cdCommand + "git init").c_str());
            std::system((cdCommand + "git branch -M main").c_str());
            appendLog("✅ Dépôt Git initialisé sur la branche main.");
        }

        // Vérifier le remote
#ifdef _WIN32
        int remoteCheck = std::system((cdCommand + "git remote get-url origin >nul 2>&1").c_str());
#else
        int remoteCheck = std::system((cdCommand + "git remote get-url origin >/dev/null 2>&1").c_str());
#endif
        if (remoteCheck != 0) {
            std::system((cdCommand + "git remote add origin https://github.com/elamrani7/MagicBoxBackup.git").c_str());
            appendLog("🔗 Dépôt distant ajouté à GitHub.");
        }

        // Pull + commit + push
        std::system((cdCommand + "git pull origin main --rebase").c_str());

        std::string commitMsg = "Backup automatique " + getCurrentDate();
        std::string commitCmd = cdCommand + "git add . && git commit -m \"" + commitMsg + "\"";
        if (std::system(commitCmd.c_str()) != 0) {
            appendLog("⚠️ Aucun changement à committer.");
        }

        int pushResult = std::system((cdCommand + "git push origin main").c_str());
        if (pushResult != 0) {
            appendLog("⚠️ Push échoué, nouvelle tentative forcée...");
            std::system((cdCommand + "git push origin main --force").c_str());
        }

        appendLog("🚀 Backup envoyé avec succès sur GitHub !");
    } catch (const std::exception& e) {
        appendLog("💥 Erreur Git : " + std::string(e.what()));
    }
}

// === Sauvegarde complète ===
void performBackup(const std::string& sourceFolder) {
    statusMessage.clear();
    progress = 0.0f;

    if (!fs::exists(sourceFolder)) {
        appendLog("❌ Le dossier spécifié n'existe pas.");
        return;
    }

    std::string backupFolder = "backup_WorkshopFiles";
    fs::create_directories(backupFolder);

    if (!clearFolderContents(backupFolder)) return;

    appendLog("🔄 Copie des fichiers en cours...");
    if (copyFiles(sourceFolder, backupFolder)) {
        appendLog("✅ Copie terminée !");
        executeGitCommands(backupFolder);
    } else {
        appendLog("❌ La copie a échoué.");
    }
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main() {
#endif
    try {
        if (!glfwInit()) throw std::runtime_error("GLFW init failed.");
        GLFWwindow* window = glfwCreateWindow(800, 400, "🪄 MagicBoxRogue", NULL, NULL);
        if (!window) throw std::runtime_error("Erreur lors de la création de la fenêtre.");
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("La Boîte Magique de Severus Rogue 🧙‍♂️");
            ImGui::Text("Entrez le chemin du dossier à sauvegarder :");
            ImGui::InputText("##Path", pathBuffer, IM_ARRAYSIZE(pathBuffer));

            ImGui::Separator();

            if (ImGui::Button("🚀 Lancer le backup")) {
                std::thread([=]() {
                    performBackup(std::string(pathBuffer));
                }).detach();
            }
            

            ImGui::Separator();
            ImGui::TextWrapped("%s", statusMessage.c_str());
            ImGui::ProgressBar(progress, ImVec2(-1, 0), "");
            ImGui::End();

            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    } catch (const std::exception& e) {
#ifdef _WIN32
        MessageBoxA(NULL, e.what(), "Erreur critique", MB_ICONERROR | MB_OK);
#endif
        appendLog(std::string("💥 Exception critique : ") + e.what());
        return -1;
    }
}
