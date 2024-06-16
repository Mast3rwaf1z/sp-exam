#include <cassert>
#include <sstream>
#include <format>

#include "Reaction.hpp"
#include "Test.hpp"

using namespace stochastic;

// sorry this is just a quick implementation...

int main(int argc, char const *argv[]){
    TestTemplate t("Reaction tests");
    t.add("Test reaction constructors", [](){
        // etc etc...
    });

    t.run();
}