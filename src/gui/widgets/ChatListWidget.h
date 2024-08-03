#ifndef CHATLISTWIDGET_H
#define CHATLISTWIDGET_H

#include <QListWidget>

#include "chat/ChatType.h"

namespace Widgets {

    class ChatListWidget final : public QListWidget {
        Q_OBJECT

    public:
        explicit ChatListWidget(QWidget* parent = nullptr);

        signals:
            void chatSelected(const QString& name, const QString& status);  // Обновленный сигнал

        private slots:
            void onItemClicked(QListWidgetItem* item);

    private:
        void addChatItem(const QString& name, const QString& lastMessage, ChatType type);  // Обновленный метод
    };

} // Widgets

#endif //CHATLISTWIDGET_H
