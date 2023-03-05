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
        explicit FileManager(string  programName);
        ofstream createFile(const string& filename);
        ifstream openFile(const string& filename);
        bool deleteFile(const string& filename);

    private:
        string m_programName;
        filesystem::path m_folderPath;

        bool createFolder();
    };

} // Files

#endif //PROJECTSAFE_FILEMANAGER_H
