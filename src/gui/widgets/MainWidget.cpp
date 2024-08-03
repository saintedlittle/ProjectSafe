//
// Created by rrarw on 02.08.2024.
//

#include "MainWidget.h"

#include "ChatListWidget.h"
#include <qsplitter.h>

#include "chat/ChatHeaderWidget.h"
#include "chat/ChatInputPanel.h"
#include "chat/ChatWindowWidget.h"

namespace Widgets {

    MainWidget::MainWidget()
        : QWidget(nullptr),
          chatList(new ChatListWidget(this)),
          chatHeader(new ChatHeaderWidget("Select a chat", "", this)),
          splitter(new QSplitter(Qt::Horizontal, this)),
          chatContentWidget(new QWidget(this)) {

        auto* mainLayout = new QHBoxLayout(this);
        mainLayout->addWidget(splitter);

        connect(chatList, &ChatListWidget::chatSelected, this, &MainWidget::updateChatHeader);

        splitter->addWidget(chatList);

        auto* chatContentLayout = new QVBoxLayout(chatContentWidget);
        chatContentLayout->addWidget(chatHeader);

        auto* chatWindow = new ChatWindowWidget(this);
        chatContentLayout->addWidget(chatWindow);

        auto* chatInputPanel = new ChatInputPanel(this);
        chatContentLayout->addWidget(chatInputPanel);

        chatContentWidget->setLayout(chatContentLayout);
        splitter->addWidget(chatContentWidget);

        splitter->setSizes({300, 700});  // Adjust as needed

        setLayout(mainLayout);
        setWindowTitle("Chat Application");
    }

    void MainWidget::updateChatHeader(const QString& name, const QString& status) const {
        chatHeader->setChatDetails(name, status);
    }

} // Widgets