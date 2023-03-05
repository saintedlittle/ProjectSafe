//
// Created by lkapi on 05.03.2023.
//

#pragma once

#ifndef PROJECTSAFE_FILEMANAGER_H
#define PROJECTSAFE_FILEMANAGER_H

#include <string>
#include <filesystem>

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

namespace Files {

    class FileManager {
    public:
        explicit FileManager(string  programName="ProjectSafe");
        ofstream createFile(const string& filename);
        ofstream createBinaryFile(const string& filename);

        ifstream openFile(const string& filename);
        ifstream openBinaryFile(const string& filename);

        bool deleteFile(const string& filename);

        string getFolderPath() { return m_folderPath.string(); }

        filesystem::path getKeysPath() { return m_folderPath_keys; }

    private:
        string m_programName;
        filesystem::path m_folderPath;
        filesystem::path m_folderPath_keys;
        filesystem::path m_folderPath_data;

        bool createFolder();
        bool createData();
        bool createKeys();
    };

} // Files

#endif //PROJECTSAFE_FILEMANAGER_H
