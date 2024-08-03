//
// Created by rrarw on 02.08.2024.
//

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <qsplitter.h>

#include "ChatListWidget.h"
#include "chat/ChatHeaderWidget.h"

namespace Widgets {

    class MainWidget final : public QWidget {
        Q_OBJECT

    public:
        MainWidget();

        private slots:
            void updateChatHeader(const QString& name, const QString& status) const;

    private:
        ChatListWidget* chatList;
        ChatHeaderWidget* chatHeader;
        QSplitter* splitter;
        QWidget* chatContentWidget;
    };

} // Widgets

#endif //MAINWIDGET_H
