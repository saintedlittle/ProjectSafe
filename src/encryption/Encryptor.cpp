//
// Created by lkapi on 25.02.2023.
//

#include "Encryptor.h"

namespace Encryption {
    string Encryptor::decryptFromFile(const string &key, const string &filename) {
        ifstream file(filename, ios::in | ios::binary);
        if (!file) {
            throw runtime_error("Unable to open files");
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

    string Encryptor::encryptToFile(const string &key, const string &input, const string &filename) {
        CryptoPP::AutoSeededRandomPool prng;
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
} // Encryption