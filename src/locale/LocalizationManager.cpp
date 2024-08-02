//
// Created by saintedlittle on 20.05.2023.
//

#include "LocalizationManager.h"

#include <clocale>
#include <fstream>

namespace localize {
    LocalizationManager::LocalizationManager() {
        // определение языка системы
        std::string system_locale = std::setlocale(LC_ALL, "");
        if (system_locale.empty()) {
            system_locale = "en_US";
        }
        // загрузка файлов локализации
        LoadLocalizationFiles(system_locale);
    }

    void LocalizationManager::LoadLocalizationFiles(const std::string& locale) {
        std::string lang_folder = "lang/";
        std::string file_name = lang_folder + locale + ".properties";
        std::ifstream file(file_name);
        if (!file.good()) {
            // если файл не найден - создаем его
            std::ofstream new_file(file_name);
            new_file.close();
            localization_files_[locale] = {};
            return;
        }
        // считываем файл и сохраняем его в unordered_map
        std::unordered_map<std::string, std::string> localization_map;
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                localization_map[key] = value;
            }
        }
        localization_files_[locale] = localization_map;
    }

    void LocalizationManager::ReloadLocalizationFiles(const std::string& locale) {
        localization_files_.erase(locale);
        LoadLocalizationFiles(locale);
    }

    void LocalizationManager::AddLocalizationFile(const std::string& locale) {
        std::string lang_folder = "lang/";
        std::string file_name = lang_folder + locale + ".properties";
        std::ofstream new_file(file_name);
        new_file.close();
    }

    const std::string& LocalizationManager::GetValue(const std::string& key) const {
        auto it = localization_files_.find(current_locale_);
        if (it == localization_files_.end()) {
            return "";
        }
        auto map_it = it->second.find(key);
        if (map_it == it->second.end()) {
            return "";
        }
        return map_it->second;
    }

} // localize