#include "App.h"

#include <filesystem>
#include <fstream>
#include "../file/FileManager.h"
#include "../key/SafeKey.h"

using namespace Encryption;
using namespace std;

namespace Application {

    void App::process() {

        helpMessage();

        bool isFirst = true;
        while (true) {
            if (!isFirst) {
                cout << endl;
                helpMessageBody();
            }
            RESET_COLOR

            int operation = getOperation();

            if (operation == 2) {
                USE_COLOR(BOLD_GREEN);
                cout << "TOKEN FOR USE: " << key << endl;
                RESET_COLOR
                WAIT
            } else if (operation == 3) {
                display_file_table();
                WAIT
            } else if (operation == 4) {
                string inputString = getInputString();

                if (!isOutputDefined)
                    output = getFilename();

                // Encrypt and write to files
                Encryptor::encryptToFile(key, inputString, output);
                WAIT
            } else if (operation == 5) {
                // Read and decrypt from files
                if (!isInputDefined)
                    input = getFilename();

                string decrypted = Encryptor::decryptFromFile(key, input);
                USE_COLOR(BOLD_GREEN);
                cout << "Decrypted output: " << decrypted << endl;
                RESET_COLOR
                WAIT
            } else if (operation == 1) {
                askKeyInput();
                WAIT
            } else if (operation == 6) {
                break;
            } else {
                getOperation();
            }

            isFirst = false;
        }

        waitForAnyKey();

    }

    string App::askKeyInput() {
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

        SafeKey keyFile;
        keyFile.save(getFilename(), key);

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
        USE_COLOR(BOLD_BLACK);
        cout << "Select operation(1/2/3/4/5/6):";
        RESET_COLOR

        cin >> answer;

        return answer;
    }

    void App::helpMessage() {
        USE_COLOR(CYAN);
        cout << "**********************************************\n";
        cout << "*          Welcome to ProjectSafe!           *\n";
        cout << "* This program can encrypt and decrypt files *\n";
        cout << "* and strings. Choose an option from below   *\n";
        cout << "**********************************************\n";
        helpMessageBody();
        cout << "*********************************************\n";
        RESET_COLOR
    }

    void App::waitForAnyKey() {
        cout << endl;
        USE_COLOR(BACKGROUND_RED);
        cout << "======== Done ========";
        RESET_COLOR
        cout << "\n";
        USE_COLOR(BOLD_CYAN);
        cout << "Press any key to exit." << endl;
        getchar();  // wait for a key press
    }

    void App::setKey(string str) {
        this->key = move(str);
    }

    void App::setOutput(string str) {
        this->output = move(str);
        isOutputDefined = true;
    }

    void App::setInput(string str) {
        this->input = move(str);
        isInputDefined = true;
    }

    void App::helpMessageBody() {
        USE_COLOR(CYAN);
        cout << "1. Change/Select key.\n";
        cout << "2. View key.\n";
        cout << "3. View available keys.\n";
        cout << "4. Encrypt string.\n";
        cout << "5. Decrypt files.\n";
        cout << "6. Exit\n";
    }

    void App::display_file_table() {
        FileManager fileManager;
        const filesystem::path folder_path = fileManager.getKeysPath();

        const filesystem::directory_iterator end_itr;
        int file_number = 1;

        for (filesystem::directory_iterator itr(folder_path); itr != end_itr; ++itr) {
            if (is_regular_file(itr->path())) {
                auto creation_time = last_write_time(itr->path());
                auto system_time = chrono::time_point_cast<chrono::system_clock::duration>(creation_time - filesystem::file_time_type::clock::now() + chrono::system_clock::now());
                time_t creation_date = chrono::system_clock::to_time_t(system_time);
                cout << file_number << ". " << itr->path().filename().string() << " - " << ctime(&creation_date);
                file_number++;
            }
        }
    }

} // Application