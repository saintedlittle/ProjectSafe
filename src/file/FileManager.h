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
        explicit FileManager(std::string programName);
        bool createFile(const std::string& filename);
        bool openFile(const std::string& filename);
        bool deleteFile(const std::string& filename);

    private:
        std::string m_programName;
        boost::filesystem::path m_folderPath{}{};

        bool createFolder();
    };

} // Files

#endif //PROJECTSAFE_FILEMANAGER_H
