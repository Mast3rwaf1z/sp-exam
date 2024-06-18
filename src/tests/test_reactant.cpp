#include <cassert>
#include <sstream>
#include <format>

#include "Reactant.hpp"
#include "Test.hpp"

using namespace stochastic;

int main(int argc, char const *argv[]){
    TestTemplate test("Reactant tests");
    new_test(test, "Test Reactant Constructors",
        Reactant r("test", 1);
        Reactant r1;
        assert(r.name == "test");
        assert(r1.name != "test");
    );

    new_test(test, "Test Reactant operators",
        Reactant r("test", 1);
        r++;
        assert(r.value == 2);
        r--;
        assert(r.value == 1);
    );

    new_test(test, "Test Reactant printing",
        Reactant r("test", 1);
        stringstream ss;
        ss << r;
        assert(ss.str() == format("{}:{}", r.name, r.value));
    );

    new_test(test, "Test constexpr reactant", 
        if constexpr (Reactant("test", 0).name == "test") {
            assert(true);
        }
    );

    test.run();
    
}
