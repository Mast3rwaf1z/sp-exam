#include <string>
#include <functional>
#include <map>
#include <iostream>

using namespace std;

typedef function<void(void)> test_function;

class TestTemplate {
    string name;

    public:
        TestTemplate(string name) : name(name) {

        }
        map<string, test_function> tests;

        TestTemplate add(const string& name, const test_function& f) {
            tests[name] = f;
            return *this;
        }

        void run(){
            cout << "--------------- " << this->name << "---------------" << endl;
            for(auto [name, test] : tests) try {
                cout << name << "\t........\t";
                test();
                cout << "ok" << endl;
            }
            catch(const std::exception& e) {
                cout << "fail" << endl;
                cerr << e.what() << endl;
            }
        }
};