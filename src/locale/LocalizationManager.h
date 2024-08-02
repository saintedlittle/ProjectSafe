//
// Created by saintedlittle on 20.05.2023.
//

#pragma once


#ifndef PROJECTSAFE_LOCALIZATIONMANAGER_H
#define PROJECTSAFE_LOCALIZATIONMANAGER_H


#include <string>
#include <unordered_map>


namespace localize {

    class LocalizationManager {
    public:
        LocalizationManager();

        void LoadLocalizationFiles(const std::string& locale);
        void ReloadLocalizationFiles(const std::string& locale);
        static void AddLocalizationFile(const std::string& locale);
        [[nodiscard]] const std::string& GetValue(const std::string& key) const;

    private:
        std::unordered_map<std::string,
                std::unordered_map<std::string, std::string>>
                localization_files_;
        std::string current_locale_ = "en_US";
    };

} // localize

#endif //PROJECTSAFE_LOCALIZATIONMANAGER_H
