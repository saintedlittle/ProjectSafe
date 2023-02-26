//
// Created by lkapi on 25.02.2023.
//

#include "App.h"

#include <fstream>
#include <utility>

using namespace Encryption;

namespace Application {

    void App::process() {

        getKey();

        helpMessage();

        const int operation = getOperation();

        if (operation == 2) {
            string inputString = getInputString();

            if (!isOutputDefined)
                output = getFilename();

            // Encrypt and write to files
            Encryptor::encryptToFile(key, inputString, output);
        } else if (operation == 3) {
            // Read and decrypt from files
            if (!isInputDefined)
                input = getFilename();

            string decrypted = Encryptor::decryptFromFile(key, input);
            USE_COLOR(BOLD_GREEN);
            cout << "Decrypted output: " << decrypted << endl;
            RESET_COLOR
        } else if (operation == 1) {
            askKeyInput();
        } else if (operation == 4) {
            exit(EXIT_SUCCESS);
        } else {
            cerr << "SELECT 1/2/3/4 !!!" << endl;
        }

        waitForAnyKey();
    }

    string App::getKey() {
        if (isKeyDefined)
            return key;

        ifstream configFile("config.txt");
        if (configFile.is_open()) {
            USE_COLOR(BOLD_WHITE);
            cout << "\nFound config.txt! Try load..." << endl;
            // Read the key from the files
            getline(configFile, key);
            configFile.close();
            USE_COLOR(GREEN);
            cout << "Success !" << endl;

        } else {
            cerr << "config.txt not found!" << endl;
            key = askKeyInput();
        }

        if (key.empty()) {
            cerr << "config.txt is empty!" << endl;
            key = askKeyInput();
        }

        return key;
    }

    string App::askKeyInput() {
        string key;

        string answer;

        // Get the key from the user and save it in the files
        USE_COLOR(BACKGROUND_YELLOW);
        USE_COLOR(BOLD_BLACK);
        cout << "Enter the key: ";
        RESET_COLOR

        cin >> key;

        USE_COLOR(YELLOW);
        cout << "Does i save key? (y/n) ";
        RESET_COLOR

        cin >> answer;
        if (answer.empty() || answer.starts_with('n')) {
            return key;
        }

        ofstream configFile("config.txt");
        if (configFile.is_open()) {
            configFile << key;
            configFile.close();
        }
        else {
            cerr << "Failed to save the key in config.txt!" << endl;
        }

        return key;
    }

    string App::getInputString() {
        string answer;

        string temp;

        USE_COLOR(BACKGROUND_YELLOW);
        USE_COLOR(BLACK);
        cout << "Enter the string:";
        RESET_COLOR

        cin >> temp;

        getline(cin, answer);

        return temp + answer;
    }

    string App::getFilename() {
        string answer;

        USE_COLOR(BACKGROUND_BLUE);
        USE_COLOR(BLACK);
        cout << "Enter the filename:";
        RESET_COLOR

        cin >> answer;

        return answer;
    }

    int App::getOperation() {
        int answer;

        // Get the key from the user and save it in the files
        USE_COLOR(BACKGROUND_YELLOW);
        cout << "Select operation(1/2/3/4):";
        RESET_COLOR

        cin >> answer;

        return answer;
    }

    void App::helpMessage() {
        cout << "\033[1;36m";
        cout << "**********************************************\n";
        cout << "*          Welcome to ProjectSafe!           *\n";
        cout << "* This program can encrypt and decrypt files *\n";
        cout << "* and strings. Choose an option from below   *\n";
        cout << "**********************************************\n";
        cout << "1. Change/Select key.\n";
        cout << "2. Encrypt string.\n";
        cout << "3. Decrypt files.\n";
        cout << "4. Exit\n";
        cout << "*********************************************\n";
        cout << "\033[0m";
    }

    void App::waitForAnyKey() {
        cout << endl;
        USE_COLOR(BACKGROUND_RED);
        cout << "======== Done ========";
        RESET_COLOR
        cout << "\n";
        USE_COLOR(BOLD_CYAN);
        cout << "Press any key to exit." << endl;
        _getch();  // wait for a key press
    }

    void App::setKey(string str) {
        this->key = std::move(str);
        isKeyDefined = true;
    }

    void App::setOutput(string str) {
        this->output = std::move(str);
        isOutputDefined = true;
    }

    void App::setInput(string str) {
        this->input = std::move(str);
        isInputDefined = true;
    }

} // Application