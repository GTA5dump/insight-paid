#include "cheat/features/globals.hpp"
#include "Discord_Register.hpp"
#include "Discord_RPC.hpp"
#include <g3log/g3log.hpp>
#include "util/timer.hpp"
#include "common.hpp"
#include <TlHelp32.h>
#include <natives.hpp>

namespace DiscordIntegration {

    namespace Handles {
        using ReadyCallback = void (*)(void);
        using DisconnectedCallback = void (*)(int errorCode, const char* message);
        using ErroredCallback = void (*)(int errorCode, const char* message);
        using JoinRequestCallback = void (*)(const DiscordJoinRequest* request);
        using JoinGameCallback = void (*)(const char* joinSecret);
        using SpectateGameCallback = void (*)(const char* spectateSecret);

        inline ReadyCallback onReady = nullptr;
        inline DisconnectedCallback onDisconnected = nullptr;
        inline ErroredCallback onError = nullptr;
        inline JoinRequestCallback onJoinRequest = nullptr;
        inline JoinGameCallback onJoinGame = nullptr;
        inline SpectateGameCallback onSpectateGame = nullptr;

        inline std::chrono::system_clock::time_point startTime;
        inline bool unloadNeeded = false;
        inline bool discordReady = false;
    }

    namespace Utility {
        inline bool IsDiscordRunningCheck() {
            PROCESSENTRY32W processEntry = { 0 };
            processEntry.dwSize = sizeof(processEntry);
            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (snapshot == INVALID_HANDLE_VALUE)
                return false;
            if (!Process32FirstW(snapshot, &processEntry)) {
                CloseHandle(snapshot);
                return false;
            } do {
                if (wcsstr(processEntry.szExeFile, L"Discord.exe")) {
                    CloseHandle(snapshot);
                    return true;
                }
            } while (Process32NextW(snapshot, &processEntry));
            CloseHandle(snapshot);
            return false;
        }

        inline void UpdatePresence() {
            DiscordRichPresence discordPresence;
            memset(&discordPresence, 0, sizeof(discordPresence));

            bool isMultiplayer = insight::globals::get()->in_multiplayer();
            discordPresence.state = isMultiplayer ? xorstr_("Multiplayer") : xorstr_("Single Player");

            std::string details = xorstr_("Playing Grand Theft Auto V");
            discordPresence.details = details.c_str();

            discordPresence.partySize = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
            discordPresence.partyMax = 32;
            discordPresence.largeImageKey = "insight";
            discordPresence.smallImageKey = "insight";
            discordPresence.smallImageText = "https://insightcheats.com/";
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - Handles::startTime);
            discordPresence.startTimestamp = std::time(nullptr) - elapsed.count() / 1000;

            Discord_UpdatePresence(&discordPresence);
            Handles::unloadNeeded = true;
        }

        inline timer discordCheck(std::chrono::seconds(5));
        inline bool firstTimeDiscord = true;
        inline bool isDiscordRunning = false;

        inline void tick() {
            if (discordCheck.update()) {
                if (isDiscordRunning) {
                    if (!Handles::discordReady) {
                        UpdatePresence();
                        Handles::discordReady = true;
                    }
                    return;
                }
                else {
                    if (firstTimeDiscord) {
                        isDiscordRunning = Utility::IsDiscordRunningCheck();
                        firstTimeDiscord = false;
                    }
                    return;
                }
            }
        }

        inline void UnloadRPC() {
            if (Handles::unloadNeeded) {
                Discord_ClearPresence();
                Discord_Shutdown();
            }
        }
    }
}
