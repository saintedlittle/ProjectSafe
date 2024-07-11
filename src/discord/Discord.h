//
// Created by lkapi on 18.03.2023.
//

#ifndef PROJECTSAFE_DISCORD_H
#define PROJECTSAFE_DISCORD_H

#include <iostream>
#include <discord_rpc.h>
#include <chrono>
#include <random>
#include <cstring>

[[noreturn]] void discord() {
    // Discord App ID
    const char* app_id = "1086700430882504725";

    // Discord User ID
    const char* user_id = "1086186960982388776";

    // Initialize Discord RPC
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(app_id, &handlers, 1, user_id);

    // Set Discord Rich Presence
    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));

    // Presence Details
    presence.details = "💀💀💀";

    // Presence State
    presence.state = "GitHub: https://github.com/Leanfe/ProjectSafe";

    // Presence Start Timestamp
    presence.startTimestamp = time(nullptr);

    // Presence Large Image
    presence.largeImageKey = "default";
    presence.largeImageText = "https://leanfe.github.io";

    // Presence Small Image
    presence.smallImageKey = "ukraine";
    presence.smallImageText = "TKnQbR96RX#f2AK";

    // Presence Party
    presence.partyId = "ae488379-351d-4a4f-ad32-2b9b01c91657";
    presence.partySize = 1;
    presence.partyMax = 5;

    // Presence Match
    presence.joinSecret = "MTI4NzM0OjFpMmhuZToxMjMxMjM";

    // Presence Instance
    presence.instance = 1;

    // Update Presence
    Discord_UpdatePresence(&presence);

    // Random String Generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(12, 50);

    // Update Presence Every 5 Seconds
    while (true) {
        // Generate Random String
        std::string random_string(dis(gen), ' ');
        std::generate_n(random_string.begin(), random_string.length(), []() {
            static const char alphanum[] =
                    "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 1);
            return alphanum[dis(gen)];
        });

        // Set Presence Description
        presence.details = "💀💀💀";
        presence.state = random_string.c_str();

        // Update Presence
        Discord_UpdatePresence(&presence);

        // Wait 5 Seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

}

#endif //PROJECTSAFE_DISCORD_H
