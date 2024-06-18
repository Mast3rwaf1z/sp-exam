#include <cassert>
#include <sstream>
#include <format>
#include <memory>

#include "Reaction.hpp"
#include "Test.hpp"
#include "Vessel.hpp"

using namespace stochastic;

int main(int argc, char const *argv[]){
    TestTemplate test("Reaction tests");
    new_test(test, "Test reaction constructors",
        // etc etc...
    );

    test.run();
}