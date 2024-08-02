//
// Created by lkapi on 05.03.2023.
//


/**
 * Explanation:

    This implementation uses the C++20 filesystem library to provide multiplatform support for creating, opening, and deleting files
    in a folder with the program name in the user's home directory.

    The FileManager class is declared in the header file with a constructor that takes the program name as an argument.
    It also includes public member functions for creating, opening, and deleting files in the folder created with the program name.

    The source file includes the header file and uses preprocessor directives to include the necessary headers and define the necessary macros for multiplatform support.
    In this case, we include windows.h and define ENV_HOME as "USERPROFILE" for Windows, and include unistd.h and define ENV_HOME as "HOME" for Unix-like systems.

    The constructor initializes the class members m_programName and m_folderPath, where m_programName stores the name of the program, and m_folderPath stores the full path to the folder created in the user's home directory with the program name.
    The createFolder() function is called inside the constructor to check whether the folder exists or not, and create the folder if it does not exist.
    The createFolder() function uses the filesystem::exists() function to check whether the folder exists or not.
    If the folder exists, it returns true; otherwise, it creates the folder using the filesystem::create_directories() function.

    The createFile() function takes a filename as an argument and creates a file in the folder by combining the folder path and filename.
    The function returns true if the file is created

 */
#include "FileManager.h"

#ifdef _WIN32
    #include <utility>
    #define ENV_HOME "USERPROFILE"
#else
    #include <unistd.h>
    #define ENV_HOME "HOME"
#endif

namespace Files {

    FileManager::FileManager(std::string  programName)
            : m_programName(std::move(programName))
    {
        m_folderPath = std::filesystem::path(getenv(ENV_HOME)) / m_programName;
        m_folderPath_keys = m_folderPath / "keys";
        m_folderPath_data = m_folderPath / "data";

        createFolder();
        createData();
        createKeys();
    }

    bool FileManager::createFolder() const {
        if (std::filesystem::exists(m_folderPath))
        {
            return true;
        }

        std::error_code error;
        std::filesystem::create_directories(m_folderPath, error);

        return !error;
    }

    bool FileManager::createData() const {
        if (std::filesystem::exists(m_folderPath_data))
        {
            return true;
        }

        std::error_code error;
        std::filesystem::create_directories(m_folderPath_data, error);

        return !error;
    }

    bool FileManager::createKeys() const {
        if (std::filesystem::exists(m_folderPath_keys))
        {
            return true;
        }

        std::error_code error;
        std::filesystem::create_directories(m_folderPath_keys, error);

        return !error;
    }

    std::ofstream FileManager::createFile(const std::string& filename) const {
        std::filesystem::path filePath = m_folderPath_data / filename;

        if (std::filesystem::exists(filePath))
        {
            return std::ofstream(filePath.string(), std::ios::out);
        }

        return std::ofstream(filePath.string(), std::ios::out);
    }


    std::ofstream FileManager::createBinaryFile(const std::string &filename) const {
        std::filesystem::path filePath = m_folderPath_keys / filename;

        if (std::filesystem::exists(filePath))
        {
            return std::ofstream(filePath.string(), std::ios::binary | std::ios::out);
        }

        return std::ofstream(filePath.string(), std::ios::binary | std::ios::out);
    }

    std::ifstream FileManager::openFile(const std::string& filename) const {
        std::filesystem::path filePath = m_folderPath_data / filename;

        if (!std::filesystem::exists(filePath))
        {
            return {};
        }

        return std::ifstream(filePath.string());
    }


    std::ifstream FileManager::openBinaryFile(const std::string &filename) const {
        std::filesystem::path filePath = m_folderPath_keys / filename;

        if (!std::filesystem::exists(filePath))
        {
            return {};
        }

        return std::ifstream(filePath.string(), std::ios::binary);
    }

    bool FileManager::deleteFile(const std::string& filename) const {
        const std::filesystem::path filePath = m_folderPath_data / filename;

        if (!std::filesystem::exists(filePath))
        {
            return false;
        }

        std::error_code error;
        std::filesystem::remove(filePath, error);

        return !error;
    }

} // Files