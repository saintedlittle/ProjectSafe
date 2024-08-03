#ifndef CHATHEADERWIDGET_H
#define CHATHEADERWIDGET_H

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

namespace Widgets {

    class ChatHeaderWidget final : public QWidget {
        Q_OBJECT

    public:
        ChatHeaderWidget(const QString& chatName, const QString& status, QWidget* parent = nullptr);

        void setChatDetails(const QString& chatName, const QString& status) const;

    private:
        QLabel* avatarLabel;
        QLabel* nameLabel;
        QLabel* statusLabel;
        QPushButton* settingsButton;
    };

} // Widgets

#endif //CHATHEADERWIDGET_H
