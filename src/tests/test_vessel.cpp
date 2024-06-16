#include <cassert>
#include <sstream>
#include <format>

#include "Vessel.hpp"
#include "Test.hpp"

using namespace stochastic;

// sorry this is just a quick implementation...

int main(int argc, char const *argv[]){
    TestTemplate t("Vessel tests");
    t.add("Test collissions", [](){
        Vessel v("test");
        auto r = v.add("test", 1);
        bool state = false;
        try {
            auto r1 = v.add("test", 2);
        }
        catch(const illegal_reactant_exception& e){
            state = true;
        }
        assert(state);
    });

    t.run();
}