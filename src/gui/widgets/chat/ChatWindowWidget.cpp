//
// Created by rrarw on 02.08.2024.
//

#include "ChatWindowWidget.h"
#include <QScrollArea>
#include <QTextBrowser>
#include <QVBoxLayout>

namespace Widgets {

    ChatWindowWidget::ChatWindowWidget(QWidget* parent)
    : QWidget(parent) {

        auto* mainLayout = new QVBoxLayout(this);

        // Create a scroll area for messages
        const auto scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);
        const auto containerWidget = new QWidget();
        messageLayout = new QVBoxLayout(containerWidget);
        containerWidget->setLayout(messageLayout);
        scrollArea->setWidget(containerWidget);

        mainLayout->addWidget(scrollArea);
        setLayout(mainLayout);
    }

} // Widgets