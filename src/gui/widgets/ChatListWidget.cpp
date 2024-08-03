//
// Created by rrarw on 02.08.2024.
//

#include "ChatListWidget.h"
#include <QListWidgetItem>

#include "chat/ChatItemWidget.h"

namespace Widgets {

    ChatListWidget::ChatListWidget(QWidget* parent) : QListWidget(parent) {
        setViewMode(ListMode);
        setSpacing(10);
        setStyleSheet("QListWidget::item { border-bottom: 1px solid #ddd; }");

        // Connect item clicked signal
        connect(this, &QListWidget::itemClicked, this, &ChatListWidget::onItemClicked);

        addChatItem("John Doe", "Hello there!");
        addChatItem("Jane Smith", "How are you?");
        addChatItem("Alice Johnson", "See you at 5 PM");
    }

    void ChatListWidget::addChatItem(const QString& name, const QString& lastMessage) {
        auto* item = new QListWidgetItem();  // Removed parent parameter
        auto* widget = new ChatItemWidget(name, lastMessage);
        item->setSizeHint(widget->sizeHint());
        addItem(item);  // Add the item to the list
        setItemWidget(item, widget);  // Associate the widget with the item
    }

    void ChatListWidget::onItemClicked(QListWidgetItem* item) {
        // Extract chat details from the item widget
        if (const auto* chatItemWidget = dynamic_cast<ChatItemWidget*>(itemWidget(item))) {
            emit chatSelected(chatItemWidget->objectName(), 10, 100);  // Example values for onlineCount and totalCount
        }
    }

} // Widgets