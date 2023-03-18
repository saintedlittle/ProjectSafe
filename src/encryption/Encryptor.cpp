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

    bool Encryptor::encryptFile(const string &key, const string &inputFile, const string &outputFile) {
        // Open the input file for reading
        ifstream in(inputFile, ios::binary);
        if (!in) {
            cerr << "Error: could not open input file: " << inputFile << endl;
            return false;
        }

        // Open the output file for writing
        ofstream out(outputFile, ios::binary);
        if (!out) {
            cerr << "Error: could not open output file: " << outputFile << endl;
            return false;
        }

        // Generate a random initialization vector
        AutoSeededRandomPool prng;
        CryptoPP::byte iv[AES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));

        // Write the IV to the output file
        out.write(reinterpret_cast<const char*>(iv), AES::BLOCKSIZE);

        // Create the encryption object
        CBC_Mode<AES>::Encryption encryptor(reinterpret_cast<const CryptoPP::byte*>(key.data()), key.size(), iv);

        // Encrypt the data and write it to the output file
        FileSource(in, true, new StreamTransformationFilter(encryptor, new FileSink(out)));

        return true;
    }

    string Encryptor::decryptFile(const string &key, const string &encryptedFilename, const string &decryptedFilename) {
        // Read the encrypted data from the file
        ifstream encryptedFile(encryptedFilename, ios::binary);
        string encryptedData((istreambuf_iterator<char>(encryptedFile)), istreambuf_iterator<char>());
        encryptedFile.close();

        // Generate the initialization vector and decrypt the data
        AutoSeededRandomPool prng;
        CryptoPP::byte iv[AES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));
        CBC_Mode<AES>::Decryption decryption((CryptoPP::byte*)key.data(), key.length(), iv);
        string decryptedData;
        StringSource(encryptedData, true,
                     new StreamTransformationFilter(decryption, new StringSink(decryptedData)));

        // Write the decrypted data to the output file
        ofstream decryptedFile(decryptedFilename, ios::binary);
        decryptedFile.write(decryptedData.data(), decryptedData.length());
        decryptedFile.close();

        return decryptedFilename;
    }

} // Encryption