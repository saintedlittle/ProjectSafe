#include "ChatHeaderWidget.h"

namespace Widgets {

    ChatHeaderWidget::ChatHeaderWidget(const QString& chatName, const QString& status, QWidget* parent)
        : QWidget(parent) {

        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(10, 10, 10, 10);

        // Avatar
        avatarLabel = new QLabel(this);
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::gray);
        avatarLabel->setPixmap(pixmap);
        avatarLabel->setFixedSize(40, 40);
        layout->addWidget(avatarLabel);

        // Chat details
        QVBoxLayout* detailsLayout = new QVBoxLayout();
        nameLabel = new QLabel(chatName, this);
        nameLabel->setStyleSheet("font-weight: bold;");
        detailsLayout->addWidget(nameLabel);

        statusLabel = new QLabel(status, this);
        detailsLayout->addWidget(statusLabel);

        layout->addLayout(detailsLayout);
        layout->addStretch();  // Push settings button to the right

        // Settings button
        settingsButton = new QPushButton("⚙", this);  // You can use an icon or text for the settings button
        settingsButton->setFixedSize(30, 30);
        layout->addWidget(settingsButton);

        setLayout(layout);
    }

    void ChatHeaderWidget::setChatDetails(const QString& chatName, const QString& status) const {
        nameLabel->setText(chatName);
        statusLabel->setText(status);
    }

} // Widgets
