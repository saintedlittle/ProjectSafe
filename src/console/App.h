//
// Created by lkapi on 25.02.2023.
//

#pragma once

#ifndef PROJECTSAFE_APP_H
#define PROJECTSAFE_APP_H

#include "../encryption/Encryptor.h"
#include "../util/Colors.h"

using namespace UI;
using namespace Encryption;

#define WAIT                 USE_COLOR(BOLD_WHITE); cout << "\nPRESS ANY BUTTON... " << endl; RESET_COLOR getchar();

namespace Application {

    class App {
    public:
        void process();

        void setKey(std::string str);

        void setOutput(std::string str);
        void setInput(std::string str);

    private:
        std::string key;

        std::string output;
        bool isOutputDefined;

        std::string input;
        bool isInputDefined;

        std::string askKeyInput();

        static std::string getInputString();
        static std::string getFilename();
        static int getOperation();

        static void helpMessage();

        static void helpMessageBody();

        static void waitForAnyKey();

        static void display_file_table();
        };

} // Application

#endif //PROJECTSAFE_APP_H
