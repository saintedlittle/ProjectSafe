#include "ChatListWidget.h"
#include "chat/ChatItemWidget.h"

namespace Widgets {

    ChatListWidget::ChatListWidget(QWidget* parent) : QListWidget(parent) {
        setViewMode(ListMode);
        setSpacing(10);
        setStyleSheet("QListWidget::item { border-bottom: 1px solid #ddd; }");

        // Connect item clicked signal
        connect(this, &QListWidget::itemClicked, this, &ChatListWidget::onItemClicked);

        // Example items with different types
        addChatItem("John Doe", "Hello there!", ChatType::Personal);
        addChatItem("Jane Smith", "How are you?", ChatType::Channel);
        addChatItem("Alice Johnson", "See you at 5 PM", ChatType::Group);
    }

    void ChatListWidget::addChatItem(const QString& name, const QString& lastMessage, const ChatType type) {
        auto* item = new QListWidgetItem();  // Removed parent parameter
        auto* widget = new ChatItemWidget(name, lastMessage, type);
        item->setSizeHint(widget->sizeHint());
        addItem(item);  // Add the item to the list
        setItemWidget(item, widget);  // Associate the widget with the item
    }

    void ChatListWidget::onItemClicked(QListWidgetItem* item) {
        if (const auto* chatItemWidget = dynamic_cast<ChatItemWidget*>(itemWidget(item))) {
            QString status;
            switch (chatItemWidget->getChatType()) {
            case ChatType::Personal:
                status = "Last seen recently";
                break;
            case ChatType::Channel:
                status = QString("%1 members online").arg(10);  // Example value
                break;
            case ChatType::Group:
                status = QString("%1 online / %2 total").arg(10).arg(100);  // Example values
                break;
            }
            emit chatSelected(chatItemWidget->getName(), status);  // Emit the signal with name and status
        }
    }

} // Widgets
