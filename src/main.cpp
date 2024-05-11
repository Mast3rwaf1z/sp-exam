#include <iostream>
#include <argparse/argparse.hpp>
#include <format>

#include "Logger.hpp"


using namespace std;
using namespace argparse;

int main(int argc, char* argv[]){
    ArgumentParser parser{"sp-exam"};
    parser.add_argument("-v", "--verbose")
        .help("Increase verbosity")
        .action([&](const auto &){ ++SP::verbosity; })
        .append()
        .default_value(false)
        .implicit_value(true)
        .nargs(0);

    try {
        parser.parse_args(argc, argv);
    }
    catch (const std::exception& e) {
        cerr << "Argparse committed die, exiting..." << endl;
        exit(1);
    }
    
    SP::log("Initialized program", 1);
    SP::log(format("Verbosity: {}", SP::verbosity));
}