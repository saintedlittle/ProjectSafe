//
// Created by lkapi on 25.02.2023.
//

#pragma once

#ifndef PROJECTSAFE_ENCRYPTOR_H
#define PROJECTSAFE_ENCRYPTOR_H

#include <cryptopp/aes.h>

using CryptoPP::AES;

namespace Encryption {

    class Encryptor {
    public:
        static std::string encryptToFile(const std::string& key, const std::string& input, const std::string& filename);

        static std::string decryptFromFile(const std::string& key, const std::string& filename);

        static bool encryptFile(const std::string& key, const std::string& inputFile, const std::string& outputFile);
        static std::string decryptFile(const std::string& key, const std::string& encryptedFilename, const std::string& decryptedFilename);

    };

} // Encryption

#endif //PROJECTSAFE_ENCRYPTOR_H
