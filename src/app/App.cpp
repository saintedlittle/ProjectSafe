//
// Created by lkapi on 25.02.2023.
//

#include "App.h"

#include <fstream>

using namespace Encryption;

namespace Application {

    void App::process() {

        const string key = getKey();

        helpMessage();

        const int operation = getOperation();

        if (operation == 2) {
            const string input = getInputString();

            const string filename = getFilename();

            // Encrypt and write to files
            cout << "Encrypting..." << endl;
            Encryptor::encryptToFile(key, input, filename);
        } else if (operation == 3) {
            // Read and decrypt from files
            const string filename = getFilename();

            cout << "Decrypting..." << endl;
            string decrypted = Encryptor::decryptFromFile(key, filename);
            cout << "Decrypted output: " << decrypted << endl;
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
        string key;
        ifstream configFile("config.txt");
        if (configFile.is_open()) {
            // TODO: UI::setColor(Colors::GREEN);
            cout << "\nFound config.txt! Try load..." << endl;
            // Read the key from the files
            getline(configFile, key);
            configFile.close();
            cout << "\033[32mSuccess !\033[0m" << endl;

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
        cout << "Enter the key: \033[1;36m";
        cin >> key;
        cout << "\033[0m";
        cout << "Does i save key? (y/n) \033[1;36m";
        cin >> answer;
        cout << "\033[0m";
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

        cout << "Enter the string: \033[1;36m";

        cin >> temp;

        getline(cin, answer);

        cout << "\033[0m";

        return temp + answer;
    }

    string App::getFilename() {
        string answer;

        // Get the key from the user and save it in the files
        cout << "Enter the filename: \033[1;36m";
        cin >> answer;
        cout << "\033[0m";

        return answer;
    }

    int App::getOperation() {
        int answer;

        // Get the key from the user and save it in the files
        cout << "Select operation(1/2/3/4): ";
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
        cout << "======== Done ========" << endl;
        cout << "Press any key to exit." << endl;
        _getch();  // wait for a key press
    }
} // Application