//
// Created by rrarw on 02.08.2024.
//

#ifndef CHATWINDOWWIDGET_H
#define CHATWINDOWWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

namespace Widgets {

    class ChatWindowWidget final : public QWidget {
        Q_OBJECT

    public:
        explicit ChatWindowWidget(QWidget* parent = nullptr);

    private:
        QVBoxLayout* messageLayout;
    };

} // Widgets

#endif //CHATWINDOWWIDGET_H
