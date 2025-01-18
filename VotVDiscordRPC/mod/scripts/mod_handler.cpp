#include <windows.h>
#include <tlhelp32.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

class Logger {
private:
    std::ofstream log_file;
    
    std::string getTimestamp() {
        time_t now = time(nullptr);
        char timestamp[26];
        ctime_s(timestamp, sizeof(timestamp), &now);
        timestamp[24] = '\0'; // Remove newline
        return std::string(timestamp);
    }

public:
    Logger(const std::string& log_path) {
        log_file.open(log_path, std::ios::app);
    }
    
    ~Logger() {
        if (log_file.is_open()) {
            log_file.close();
        }
    }
    
    template<typename T>
    void log(const T& message) {
        if (log_file.is_open()) {
            log_file << "[" << getTimestamp() << "] " << message << std::endl;
        }
        std::cout << message << std::endl;
    }
};

bool killGameProcess(Logger& logger) {
    const wchar_t* processName = L"VotV-Win64-Shipping.exe";
    bool found = false;
    
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        logger.log("Failed to create process snapshot");
        return false;
    }
    
    PROCESSENTRY32W processEntry = { sizeof(PROCESSENTRY32W) };
    
    if (Process32FirstW(snapshot, &processEntry)) {
        do {
            if (_wcsicmp(processEntry.szExeFile, processName) == 0) {
                HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, processEntry.th32ProcessID);
                if (processHandle != NULL) {
                    logger.log("Found game process. Terminating...");
                    if (TerminateProcess(processHandle, 0)) {
                        logger.log("Successfully terminated game process");
                        found = true;
                    } else {
                        logger.log("Failed to terminate game process");
                    }
                    CloseHandle(processHandle);
                }
            }
        } while (Process32NextW(snapshot, &processEntry));
    }
    
    CloseHandle(snapshot);
    if (!found) {
        logger.log("Game process not found");
    }
    return found;
}

bool copyFile(const fs::path& source, const fs::path& destination, Logger& logger) {
    try {
        if (!fs::exists(source)) {
            logger.log("Source file does not exist: " + source.string());
            return false;
        }
        
        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        logger.log("Successfully copied file from " + source.string() + " to " + destination.string());
        return true;
    }
    catch (const std::exception& e) {
        logger.log("Error copying file: " + std::string(e.what()));
        return false;
    }
}

bool startGame(const std::string& exePath, const std::string& cfgDir, 
               const std::string& modDir, const std::string& pakDir, Logger& logger) {
    std::string cmdLine = "\"" + exePath + "\" " +
                         "--cfg-dir=\"" + cfgDir + "\" " +
                         "--mod-dir=\"" + modDir + "\" " +
                         "--pak-dir=\"" + pakDir + "\"";
    Sleep(2000);  // Windows API, waits for 2000 milliseconds (2 seconds)
    logger.log("Starting game with command: " + cmdLine);
    
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi;
    
    if (CreateProcessA(NULL, const_cast<LPSTR>(cmdLine.c_str()), 
                      NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        logger.log("Successfully started game process");
        return true;
    }
    
    logger.log("Failed to start game process");
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cout << "Usage: mod_handler.exe <mod_dir> <shimloader_mod_dir> <base_dir> <cfg_dir> <pak_dir>" << std::endl;
        return 1;
    }
    
    // Get the executable directory for log file placement
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    fs::path exeDir = fs::path(exePath).parent_path();
    Logger logger(exeDir.string() + "\\mod_handler.log");
    
    logger.log("Starting mod handler...");
    logger.log("Arguments:");
    logger.log("Mod Dir: " + std::string(argv[1]));
    logger.log("Shimloader Mod Dir: " + std::string(argv[2]));
    logger.log("Base Dir: " + std::string(argv[3]));
    logger.log("Cfg Dir: " + std::string(argv[4]));
    logger.log("Pak Dir: " + std::string(argv[5]));
    
    // Setup path for discord_game_sdk.dll
    fs::path sourceDiscord = fs::path(argv[2]) / "Moddy-VotVDiscordRPC" / "discord_game_sdk.dll";
    fs::path destDiscord = fs::path(argv[3]) / "discord_game_sdk.dll";
    fs::path gameExe = fs::path(argv[3]) / "VotV-Win64-Shipping.exe";
    
    bool needsGameRestart = false;

    // Check discord_game_sdk.dll
    if (!fs::exists(destDiscord)) {
        logger.log("discord_game_sdk.dll does not exist at destination, will copy");
        needsGameRestart = true;
    }

    // If DLL needs updating, perform the update
    if (needsGameRestart) {
        // Kill game process since we need to update files
        killGameProcess(logger);
        
        // Copy discord_game_sdk.dll if it doesn't exist
        if (!fs::exists(destDiscord)) {
            if (!copyFile(sourceDiscord, destDiscord, logger)) {
                logger.log("Failed to copy discord_game_sdk.dll");
                std::cout << "\nPress Enter to exit...";
                std::cin.get();
                return 1;
            }
        }
        
        // Start game since files were updated
        logger.log("Starting game since files were updated");
        if (!startGame(gameExe.string(), argv[4], argv[2], argv[5], logger)) {
            logger.log("Failed to start game");
            std::cout << "\nPress Enter to exit...";
            std::cin.get();
            return 1;
        }
        
        logger.log("Mod handler completed successfully - files updated and game restarted");
    } else {
        logger.log("No updates needed. Exiting.");
    }
    return 0;
}