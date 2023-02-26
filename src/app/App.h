//
// Created by lkapi on 25.02.2023.
//

#pragma once

#ifndef PROJECTSAFE_APP_H
#define PROJECTSAFE_APP_H

#include <string>
#include <conio.h>

#include "cryptopp/osrng.h"

#include "../encryption/Encryptor.h"
#include "../util/Colors.h"

using namespace std;

using namespace UI;

namespace Application {

    class App {
    public:
        void process();

        void setKey(string str);
        void setOutput(string str);
        void setInput(string str);

    private:
        string key;
        bool isKeyDefined;

        string output;
        bool isOutputDefined;

        string input;
        bool isInputDefined;

        string getKey();
        static string askKeyInput();

        static string getInputString();
        static string getFilename();
        static int getOperation();

        static void helpMessage();

        static void waitForAnyKey();
    };

} // Application

#endif //PROJECTSAFE_APP_H
