//
// Created by lkapi on 04.03.2023.
//

#include "SafeKey.h"

namespace Encryption {

    bool SafeKey::save(const string &filename, const string &data) {

        ofstream file = fileManager.createBinaryFile(filename + ".safe");

        if (!file.is_open()) {
            USE_COLOR(RED)
            cerr << "Error: failed to open file! " << filename << endl;
            RESET_COLOR;

            save(filename, data);
        }

        // Encrypt the data using the XOR cipher
        string encrypted_data = xor_cipher(data);

        // Write the encrypted data to the file
        file.write(encrypted_data.c_str(), encrypted_data.size());

        // Close the file
        file.close();

        return true;
    }

    int SafeKey::load(const string &filename) {

        ifstream file = fileManager.openFile(filename);

        if (!file.is_open()) {
            CREATE_FILE(filename);
            return 1;
        }

        // Determine the size of the file
        file.seekg(0, ios::end);
        streamsize size = file.tellg();
        file.seekg(0, ios::beg);

        // Read the entire file into memory
        string data(size, '\0');
        if (!file.read(&data[0], size)) {
            USE_COLOR(RED)
            cerr << "Error: failed to read file " << filename << endl;
            RESET_COLOR;
            return 2;
        }

        // Decrypt the data using the XOR cipher
        string decrypted_data = xor_cipher(data);

        // Close the file
        file.close();

        token = std::move(decrypted_data);

        return 0;
    }

    string SafeKey::xor_cipher(const string &data) const {
        string result;
        for (size_t i = 0; i < data.size(); i++) {
            result += data[i] ^ xor_key_[i % xor_key_.size()];
        }
        return result;
    }

    string SafeKey::getToken() {
        return token;
    }

} // Encryption