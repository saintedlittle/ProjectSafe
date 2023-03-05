//
// Created by lkapi on 04.03.2023.
//

#ifndef PROJECTSAFE_SAFEKEY_H
#define PROJECTSAFE_SAFEKEY_H

#define CREATE_FILE(filename)             cout << "File " << filename << " does not exist. Creating the file..." << endl; \
                                                  ofstream new_file = fileManager.createBinaryFile(filename); \
                                            new_file.close();

#include <string>
#include <fstream>
#include <iostream>
#include <utility>

#include "../util/Colors.h"
#include "../file/FileManager.h"

using namespace std;

using namespace UI;
using namespace Files;

namespace Encryption {

    class SafeKey {
    public:
        explicit SafeKey(string xor_key="You are on thin ice") : xor_key_(std::move(xor_key)) {}

        bool save(const string& filename, const string& data);

        int load(const string& filename);

        string getToken();

    private:
        [[nodiscard]] string xor_cipher(const string& data) const;

        string xor_key_;

        string token;

        FileManager fileManager;
    };

} // Encryption

#endif //PROJECTSAFE_SAFEKEY_H
