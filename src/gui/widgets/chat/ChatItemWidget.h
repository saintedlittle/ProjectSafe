#ifndef CHATITEMWIDGET_H
#define CHATITEMWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include "ChatType.h"  // Убедитесь, что ChatType определен здесь

namespace Widgets {

    class ChatItemWidget final : public QWidget {
        Q_OBJECT

    public:
        ChatItemWidget(const QString& name, const QString& lastMessage, ChatType chatType, QWidget* parent = nullptr);
        [[nodiscard]] QString getName() const;
        [[nodiscard]] ChatType getChatType() const;  // Возвращает значение ChatType

    private:
        QLabel* iconLabel;
        QLabel* nameLabel;
        QLabel* messageLabel;
        ChatType chatType;  // Используем значение ChatType
    };

} // Widgets

#endif //CHATITEMWIDGET_H
