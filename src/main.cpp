#include <cxxopts.hpp>

#include "app/App.h"

using namespace Application;

using namespace cxxopts;

void optionsParse(int argc, char** argv);

int main(int argc, char** argv) {
    auto app = new App();

    Options options("Project Safe", "Encryption project.");

    options.add_options()
            ("k,key", "Define key.", cxxopts::value<string>())
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

    string key;
    if (result.count("key"))
        key = result["key"].as<string>();
    
    string output;
    if (result.count("output"))
        output = result["output"].as<string>();

    string file;
    if (result.count("file"))
        file = result["file"].as<string>();

    if (!key.empty())
        app->setKey(key);
    if (!output.empty())
        app->setOutput(output);
    if(!file.empty())
        app->setInput(file);


    app->process();

    return EXIT_SUCCESS;
}
