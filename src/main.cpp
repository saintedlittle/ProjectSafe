#include <string>
#include <thread>
#include <cxxopts.hpp>

#include "console/App.h"
#include "locale/LocalizationManager.h"

#include <QtWidgets/QtWidgets>

#include "gui/GUIManager.h"
#include "key/SafeKey.h"

std::string loadKey(const std::string& filename);

int main(const int argc, char** argv) {
    cxxopts::Options options("Project Safe", "Encryption project.");

    bool useConsole = false;
    const auto app = new Application::App();

    options.add_options()
            ("c,console", "Open in console mode", cxxopts::value<bool>())
            ("k,key", "Define key.", cxxopts::value<std::string>())
            ("ik,key-file", "Define key-file.", cxxopts::value<std::string>())
            ("f,file", "Define input file.", cxxopts::value<std::string>())
            ("o,output", "Define output file.", cxxopts::value<std::string>())
            ("h,help", "This menu.")
            ;

    const auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    if (result.count("console"))
        useConsole = result["console"].as<bool>();

    std::string output;
    if (result.count("output"))
        output = result["output"].as<std::string>();

    std::string file;
    if (result.count("file"))
        file = result["file"].as<std::string>();

    if (!output.empty())
        app->setOutput(output);
    if(!file.empty())
        app->setInput(file);

    std::string key;
    if (result.count("key"))
        key = result["key"].as<std::string>();

    std::string ik;
    if (result.count("key-file"))
        ik = result["key-file"].as<std::string>();

    if (ik.empty())
        if (!key.empty())
            app->setKey(key);
        else app->setKey("TOKEN");
    else if (!ik.empty())
        app->setKey(loadKey(ik));

    if (useConsole) {
        auto localizationManager = localize::LocalizationManager();
        app->process();
        exit(EXIT_SUCCESS);
    }

    auto window = GUI::GUIManager();
    return window.init(argc, argv);
}

std::string loadKey(const std::string& filename) {
    SafeKey key;
    switch (key.load(filename)) {
        case 1:
            key.save(filename, "TOKEN");
        key.load(filename);
        return key.getToken();
        case 2:
            getchar();
        exit(EXIT_FAILURE);
        default:;
    }

    return key.getToken();
}