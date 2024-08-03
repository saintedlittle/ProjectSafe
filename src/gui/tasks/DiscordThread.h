//
// Created by rrarw on 02.08.2024.
//

#ifndef DISCORDTHREAD_H
#define DISCORDTHREAD_H

#include <QThread>
#include "../../discord/Discord.h"

namespace Threads {


    class DiscordThread : public QThread {
        Q_OBJECT
    public:
        explicit DiscordThread(QObject *parent = nullptr) : QThread(parent) {}

    protected:
        void run() override {
            discord();
        }
    };

} // Threads

#endif //DISCORDTHREAD_H
