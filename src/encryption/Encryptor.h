//
// Created by lkapi on 25.02.2023.
//

#pragma once

#ifndef PROJECTSAFE_ENCRYPTOR_H
#define PROJECTSAFE_ENCRYPTOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include "cryptopp/osrng.h"

#include <cryptopp/files.h>

using namespace std;

using namespace CryptoPP;
using CryptoPP::AES;

namespace Encryption {

    class Encryptor {
    public:
        static string encryptToFile(const string& key, const string& input, const string& filename);

        static string decryptFromFile(const string& key, const string& filename);

        static bool encryptFile(const string& key, const string& inputFile, const string& outputFile);
        static string decryptFile(const string& key, const string& encryptedFilename, const string& decryptedFilename);

    };

} // Encryption

#endif //PROJECTSAFE_ENCRYPTOR_H
