#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "tasks/DiscordThread.h"

namespace GUI {

    class GUIManager {
    public:
        GUIManager();
        int init(int argc, char **argv);
    private:

        void preinit();

        void startPresence();

        std::string title;
        std::pair<int, int> size;
        bool use_fullscreen;

        Threads::DiscordThread *discordThread; // Указатель на поток Discord

    };

} // namespace GUI

#endif // GUIMANAGER_H
