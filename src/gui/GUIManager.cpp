#include "GUIManager.h"

#include <qapplication.h>
#include <qpushbutton.h>

namespace GUI {

    GUIManager::GUIManager(): use_fullscreen(false) {
        preinit();
    }

    void GUIManager::preinit() {
        title = "My Qt Application";
        size.first = 400;
        size.second = 300;
    }

    int GUIManager::init(int argc, char **argv) const {
        QApplication qtapp(argc, argv);

        QWidget window;
        window.setWindowTitle("Hello QT!");
        window.resize(400, 300);

        auto* button = new QPushButton("Click me", &window);
        button->setGeometry(10, 10, 100, 30);

        window.show();

        return qtapp.exec();
    }

} // namespace GUI
