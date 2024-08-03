//
// Created by rrarw on 02.08.2024.
//

#ifndef CHATITEMWIDGET_H
#define CHATITEMWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

namespace Widgets {

    class ChatItemWidget final : public QWidget {
        Q_OBJECT

    public:
        ChatItemWidget(const QString& name, const QString& lastMessage, QWidget* parent = nullptr);

    private:
        QLabel* iconLabel;
        QLabel* nameLabel;
        QLabel* messageLabel;
    };

} // Widgets

#endif //CHATITEMWIDGET_H
