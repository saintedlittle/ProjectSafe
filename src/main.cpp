#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include "cryptopp/osrng.h"

using namespace std;

using namespace CryptoPP;
using CryptoPP::AES;

class Encryption {
public:
    static string encryptToFile(const string& key, const string& input, const string& filename) {
        CryptoPP::byte iv[AES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));

        AES::Encryption aesEncryption((CryptoPP::byte*)key.c_str(), AES::DEFAULT_KEYLENGTH);
        CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

        string ciphertext;
        StreamTransformationFilter stfEncryptor(cbcEncryption, new StringSink(ciphertext));
        stfEncryptor.Put(reinterpret_cast<const unsigned char*>(input.c_str()), input.length());
        stfEncryptor.MessageEnd();

        ofstream file(filename, ios::out | ios::binary);
        file.write(reinterpret_cast<const char*>(iv), AES::BLOCKSIZE);
        file.write(ciphertext.c_str(), ciphertext.length());
        file.close();
        return ciphertext;
    }

    static string decryptFromFile(const string& key, const string& filename) {
        ifstream file(filename, ios::in | ios::binary);
        if (!file) {
            throw runtime_error("Unable to open file");
        }

        CryptoPP::byte iv[AES::BLOCKSIZE];
        file.read(reinterpret_cast<char*>(iv), AES::BLOCKSIZE);

        AES::Decryption aesDecryption((CryptoPP::byte*)key.c_str(), AES::DEFAULT_KEYLENGTH);
        CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

        string decryptedData;
        vector<CryptoPP::byte> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        ArraySource arraySource(buffer.data(), buffer.size(), true,
                              new StreamTransformationFilter(cbcDecryption,
                                                                       new StringSink(decryptedData)));

        file.close();
        return decryptedData;
    }

private:
    static CryptoPP::AutoSeededRandomPool prng;
};

CryptoPP::AutoSeededRandomPool Encryption::prng;

string getKey();
string askKeyInput();

string getInputString();
string getFilename();
int getOperation();

void helpMessage();

int main() {

    const string key = getKey();

    helpMessage();

    const int operation = getOperation();

    if (operation == 2) {
        const string input = getInputString();
        const string filename = getFilename();

        // Encrypt and write to file
        cout << "Encrypting..." << endl;
        Encryption::encryptToFile(key, input, filename);
    } else if (operation == 3) {
        // Read and decrypt from file
        const string filename = getFilename();

        cout << "Decrypting..." << endl;
        string decrypted = Encryption::decryptFromFile(key, filename);
        cout << "Decrypted output: " << decrypted << endl;
    } else if (operation == 1) {
        askKeyInput();
    } else if (operation == 4) {
        exit(EXIT_SUCCESS);
    } else {
        cerr << "SELECT 1/2/3/4 !!!" << endl;
    }

    return 0;
}

string askKeyInput() {
    string key;

    string answer;

    // Get the key from the user and save it in the file
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
}

string getKey() {
    string key;
    ifstream configFile("config.txt");
    if (configFile.is_open()) {
        cout << "\nFound config.txt! Try load..." << endl;
        // Read the key from the file
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

string getInputString() {
    string answer;

    cout << "Enter the string: \033[1;36m";
    cin >> answer;
    cout << "\033[0m";

    return answer;
}

string getFilename() {
    string answer;

    // Get the key from the user and save it in the file
    cout << "Enter the filename: \033[1;36m";
    cin >> answer;
    cout << "\033[0m";

    return answer;
}

int getOperation() {
    int answer;

    // Get the key from the user and save it in the file
    cout << "Select operation(1/2/3/4): ";
    cin >> answer;

    return answer;
}

void helpMessage() {
    cout << "\033[1;36m";
    cout << "**********************************************\n";
    cout << "*          Welcome to ProjectSafe!           *\n";
    cout << "* This program can encrypt and decrypt files *\n";
    cout << "* and strings. Choose an option from below   *\n";
    cout << "**********************************************\n";
    cout << "1. Change/Select key.\n";
    cout << "2. Encrypt string.\n";
    cout << "3. Decrypt file.\n";
    cout << "4. Exit\n";
    cout << "*********************************************\n";
    cout << "\033[0m";
}