#include <cassert>
#include <sstream>
#include <format>

#include "Reactant.hpp"
#include "Vessel.hpp"
#include "Test.hpp"

using namespace stochastic;

int main(int argc, char const *argv[]){
    TestTemplate test("Vessel tests");
    new_test(test, "Test collissions",
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
    );

    test.add("Test constexpr", [](){
        if constexpr (Reactant("r1", 0).value == 0)
            assert(true);
        else
            assert(false);
            
        if constexpr ((Reactant("r1", 0) + Reactant("r2", 0))[0].value == 0)
            assert(true);
        else
            assert(false);

        if constexpr ((Reactant("r1", 0) + Reactant("r2", 0) >> 1.0).second == 1.0)
            assert(true);
        else
            assert(false);

        if constexpr (((Reactant("r1", 0) + Reactant("r2", 0)) >> 1.0 >>= (Reactant("r3", 0) + Reactant("r4", 0))).lambda == 1.0)
            assert(true);
        else
            assert(false);
    });

    test.run();
}