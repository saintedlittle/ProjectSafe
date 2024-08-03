#include "ChatItemWidget.h"

namespace Widgets {

    ChatItemWidget::ChatItemWidget(const QString& name, const QString& lastMessage, ChatType chatType, QWidget* parent)
        : QWidget(parent), chatType(chatType) {  // Инициализируем chatType

        const auto layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        iconLabel = new QLabel(this);
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::gray);
        iconLabel->setPixmap(pixmap);
        iconLabel->setFixedSize(40, 40);
        layout->addWidget(iconLabel);

        auto* textLayout = new QVBoxLayout();
        nameLabel = new QLabel(name, this);
        nameLabel->setStyleSheet("font-weight: bold;");
        textLayout->addWidget(nameLabel);

        messageLabel = new QLabel(lastMessage, this);
        textLayout->addWidget(messageLabel);

        layout->addLayout(textLayout);
        setLayout(layout);
    }

    QString ChatItemWidget::getName() const {
        return nameLabel->text();
    }

    ChatType ChatItemWidget::getChatType() const {
        return chatType;
    }

} // Widgets
