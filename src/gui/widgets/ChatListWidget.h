//
// Created by rrarw on 02.08.2024.
//

#ifndef CHATLISTWIDGET_H
#define CHATLISTWIDGET_H

#include <QListWidget>

namespace Widgets {

    class ChatListWidget final : public QListWidget {
        Q_OBJECT

    public:
        explicit ChatListWidget(QWidget* parent = nullptr);

        signals:
            void chatSelected(const QString& name, int onlineCount, int totalCount);

        private slots:
            void onItemClicked(QListWidgetItem* item);

    private:
        void addChatItem(const QString& name, const QString& lastMessage);
    };


} // Widgets

#endif //CHATLISTWIDGET_H
