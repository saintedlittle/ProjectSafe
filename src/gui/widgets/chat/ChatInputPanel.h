//
// Created by rrarw on 02.08.2024.
//

#ifndef CHATINPUTPANEL_H
#define CHATINPUTPANEL_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

namespace Widgets {

    class ChatInputPanel final : public QWidget {
        Q_OBJECT

    public:
        explicit ChatInputPanel(QWidget* parent = nullptr);

    private:
        QLineEdit* messageEdit;
        QPushButton* attachButton;
        QPushButton* sendButton;
        QPushButton* stickersButton;
    };

} // Widgets

#endif //CHATINPUTPANEL_H
