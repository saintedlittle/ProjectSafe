//
// Created by rrarw on 02.08.2024.
//

#include "ChatInputPanel.h"

namespace Widgets {

    ChatInputPanel::ChatInputPanel(QWidget* parent)
    : QWidget(parent) {

        auto* layout = new QHBoxLayout(this);
        layout->setContentsMargins(10, 10, 10, 10);

        // Attach button
        attachButton = new QPushButton("📎", this);
        attachButton->setFixedSize(30, 30);
        layout->addWidget(attachButton);

        // Message input field
        messageEdit = new QLineEdit(this);
        messageEdit->setPlaceholderText("Type a message...");
        layout->addWidget(messageEdit);

        // Send button
        sendButton = new QPushButton("Send", this);
        sendButton->setFixedSize(60, 30);
        layout->addWidget(sendButton);

        // Stickers button
        stickersButton = new QPushButton("🎨", this);  // You can use an icon or text for stickers
        stickersButton->setFixedSize(30, 30);
        layout->addWidget(stickersButton);

        setLayout(layout);
    }

} // Widgets