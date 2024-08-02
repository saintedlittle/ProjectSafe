#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include <qapplication.h>

namespace GUI {

    class GUIManager {
    public:
        GUIManager();
        int init(int argc, char **argv) const;
    private:

        void preinit();

        std::string title;
        std::pair<int, int> size;
        bool use_fullscreen;
    };

} // namespace GUI

#endif // GUIMANAGER_H
