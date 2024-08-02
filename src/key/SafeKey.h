//
// Created by lkapi on 04.03.2023.
//

#ifndef PROJECTSAFE_SAFEKEY_H
#define PROJECTSAFE_SAFEKEY_H

#define CREATE_FILE(filename)             cout << "File " << filename << " does not exist. Creating the file..." << endl; \
                                                  ofstream new_file = fileManager.createBinaryFile(filename); \
                                            new_file.close();

#include <string>
#include <utility>

#include "../util/Colors.h"
#include "../file/FileManager.h"

using namespace UI;
using namespace Files;

namespace Encryption {

    class SafeKey {
    public:
        explicit SafeKey(std::string xor_key="You are on thin ice") : xor_key_(std::move(xor_key)) {}

        bool save(const std::string& filename, const std::string& data);

        int load(const std::string& filename);

        std::string getToken();

    private:
        [[nodiscard]] std::string xor_cipher(const std::string& data) const;

        std::string xor_key_;

        std::string token;

        FileManager fileManager;
    };

} // Encryption

#endif //PROJECTSAFE_SAFEKEY_H
