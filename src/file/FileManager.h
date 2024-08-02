//
// Created by lkapi on 05.03.2023.
//

#pragma once

#ifndef PROJECTSAFE_FILEMANAGER_H
#define PROJECTSAFE_FILEMANAGER_H

#include <string>
#include <filesystem>

#include <fstream>

namespace Files {

    class FileManager {
    public:
        explicit FileManager(std::string  programName="ProjectSafe");

        [[nodiscard]] std::ofstream createFile(const std::string& filename) const;

        [[nodiscard]] std::ofstream createBinaryFile(const std::string& filename) const;

        [[nodiscard]] std::ifstream openFile(const std::string& filename) const;
        [[nodiscard]] std::ifstream openBinaryFile(const std::string& filename) const;

        [[nodiscard]] bool deleteFile(const std::string& filename) const;

        [[nodiscard]] std::string getFolderPath() const { return m_folderPath.string(); }

        std::filesystem::path getKeysPath() { return m_folderPath_keys; }

    private:
        std::string m_programName;
        std::filesystem::path m_folderPath;
        std::filesystem::path m_folderPath_keys;
        std::filesystem::path m_folderPath_data;

        [[nodiscard]] bool createFolder() const;
        [[nodiscard]] bool createData() const;
        [[nodiscard]] bool createKeys() const;
    };

} // Files

#endif //PROJECTSAFE_FILEMANAGER_H
