#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

namespace SP {
    int verbosity = 0;

    void log(string input, int targetverbosity) {
        auto now = chrono::system_clock::now();
        ofstream file("/tmp/sp-exam.log", ios::app);
        file << '[' << now << "]: " << input << endl;
        file.close();
        if (verbosity >= targetverbosity) {
            int intensity = 0xff - (targetverbosity * 0x11);
            cout << "\033[38;2;" << intensity << ';' << intensity << ';' << intensity << 'm' 
                 << '[' << targetverbosity << ']' << '\t' 
                 << input 
                 << "\033[0m" << endl;
        }
    }
    void log(string input){
        log(input, 2);
    }
}