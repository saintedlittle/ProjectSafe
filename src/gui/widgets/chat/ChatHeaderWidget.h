//
// Created by rrarw on 02.08.2024.
//

#ifndef CHATHEADERWIDGET_H
#define CHATHEADERWIDGET_H

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

namespace Widgets {


    class ChatHeaderWidget final : public QWidget {
        Q_OBJECT

    public:
        ChatHeaderWidget(const QString& chatName, int onlineCount, int totalCount, QWidget* parent = nullptr);

        void setChatDetails(const QString& chatName, int onlineCount, int totalCount) const;

    private:
        QLabel* avatarLabel;
        QLabel* nameLabel;
        QLabel* onlineInfoLabel;
        QPushButton* settingsButton;
    };

} // Widgets

#endif //CHATHEADERWIDGET_H
