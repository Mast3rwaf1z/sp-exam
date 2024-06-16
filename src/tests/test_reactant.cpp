#include <cassert>
#include <sstream>
#include <format>

#include "Reactant.hpp"
#include "Test.hpp"

using namespace stochastic;

// sorry this is just a quick implementation...

int main(int argc, char const *argv[]){
    TestTemplate t("Reactant tests");
    t.add("Test Reactant Constructors", [](){
        Reactant r("test", 1);
        Reactant r1;
        assert(r.name == "test");
        assert(r1.name != "test");
    });
    t.add("Test Reactant operators", [](){
        Reactant r("test", 1);
        r++;
        assert(r.value == 2);
        r--;
        assert(r.value == 1);
    });
    t.add("Test Reactant printing", [](){
        Reactant r("test", 1);
        stringstream ss;
        ss << r;
        assert(ss.str() == format("{}:{}", r.name, r.value));
    });

    t.run();
    
}
