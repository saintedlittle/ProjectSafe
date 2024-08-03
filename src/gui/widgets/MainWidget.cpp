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

    MainWidget::MainWidget() {
        auto* mainLayout = new QHBoxLayout(this);

        splitter = new QSplitter(Qt::Horizontal, this);
        mainLayout->addWidget(splitter);

        chatList = new ChatListWidget(this);
        connect(chatList, &ChatListWidget::chatSelected, this, &MainWidget::updateChatHeader);
        splitter->addWidget(chatList);

        chatContentWidget = new QWidget(this);
        auto* chatContentLayout = new QVBoxLayout(chatContentWidget);

        // Add separator
        // auto* separator = new QFrame(chatContentWidget);
        // separator->setFrameShape(QFrame::HLine);
        // separator->setFrameShadow(QFrame::Sunken);
        // chatContentLayout->addWidget(separator);

        // Chat header widget
        chatHeader = new ChatHeaderWidget("Select a chat", 0, 0, this);
        chatContentLayout->addWidget(chatHeader);

        // Chat window widget
        auto* chatWindow = new ChatWindowWidget(this);
        chatContentLayout->addWidget(chatWindow);

        // Chat input panel
        auto* chatInputPanel = new ChatInputPanel(this);
        chatContentLayout->addWidget(chatInputPanel);

        chatContentWidget->setLayout(chatContentLayout);
        splitter->addWidget(chatContentWidget);

        splitter->setSizes({300, 700});  // Adjust as needed

        setLayout(mainLayout);
        setWindowTitle("Chat Application");
    }

    void MainWidget::updateChatHeader(const QString& name, const int onlineCount, const int totalCount) const {
        chatHeader->setChatDetails(name, onlineCount, totalCount);
    }

} // Widgets