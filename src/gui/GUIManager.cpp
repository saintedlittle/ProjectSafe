#include "GUIManager.h"

#include <QApplication>
#include <QThread>
#include "widgets/MainWidget.h"

namespace GUI {

    GUIManager::GUIManager() : use_fullscreen(false), discordThread(nullptr) {
        preinit();
    }

    void GUIManager::preinit() {
        title = "My Qt Application";
        size.first = 800;
        size.second = 600;
    }

    void GUIManager::startPresence() {
        if (discordThread == nullptr) {
            discordThread = new Threads::DiscordThread();
            discordThread->setPriority(QThread::NormalPriority);
            discordThread->start();
        }
    }

    int GUIManager::init(int argc, char **argv) {
        QApplication qtapp(argc, argv);

        Widgets::MainWidget mainWindow;
        mainWindow.resize(size.first, size.second);
        mainWindow.show();

        startPresence();

        int result = qtapp.exec();

        if (discordThread != nullptr) {
            discordThread->quit();
            discordThread->wait();
            delete discordThread;
        }

        return result;
    }

}
