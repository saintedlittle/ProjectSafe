#include <cxxopts.hpp>

#include "app/App.h"

using namespace Application;

using namespace cxxopts;

string loadKey(const string& filename);

int main(int argc, char** argv) {

    auto app = new App();

    Options options("Project Safe", "Encryption project.");

    options.add_options()
            ("k,key", "Define key.", cxxopts::value<string>())
            ("ik,key-file", "Define key-file.", cxxopts::value<string>())
            ("f,file", "Define input file.", cxxopts::value<string>())
            ("o,output", "Define output file.", cxxopts::value<string>())
            ("h,help", "This menu.")
            ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        cout << options.help() << endl;
        exit(0);
    }

    string output;
    if (result.count("output"))
        output = result["output"].as<string>();

    string file;
    if (result.count("file"))
        file = result["file"].as<string>();

    if (!output.empty())
        app->setOutput(output);
    if(!file.empty())
        app->setInput(file);

    string key;
    if (result.count("key"))
        key = result["key"].as<string>();

    string ik;
    if (result.count("key-file"))
        ik = result["key-file"].as<string>();

    if (ik.empty())
        if (!key.empty())
            app->setKey(key);
        else app->setKey("TOKEN");
    else if (!ik.empty())
        app->setKey(loadKey(ik));

    app->process();
    return EXIT_SUCCESS;
}

string loadKey(const string& filename) {
    SafeKey key;
    switch (key.load(filename)) {
        case 1:
            key.save(filename, "TOKEN");
            key.load(filename);
            return key.getToken();
        case 2:
            getch();
            exit(EXIT_FAILURE);
    }

    return key.getToken();
}
