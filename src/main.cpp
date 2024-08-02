#include <string>
#include <thread>
#include <cxxopts.hpp>

#include "app/App.h"
#include "discord/Discord.h"
#include "locale/LocalizationManager.h"

#include <QtWidgets/QtWidgets>

#include "key/SafeKey.h"

std::string loadKey(const std::string& filename);

int main(int argc, char** argv) {
    QApplication qtapp(argc, argv);

    // Create a basic Qt window
    QWidget window;
    window.setWindowTitle("Qt Window");
    window.resize(400, 300);

    // Optionally, add a button to the window
    auto* button = new QPushButton("Click me", &window);
    button->setGeometry(10, 10, 100, 30);

    // Show the window
    window.show();

    qtapp.exec();

    auto localizationManager = localize::LocalizationManager();

    std::thread t(discord); // create a new thread to execute discord()

    const auto app = new Application::App();

    cxxopts::Options options("Project Safe", "Encryption project.");

    options.add_options()
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

    app->process();

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
    }

    return key.getToken();
}