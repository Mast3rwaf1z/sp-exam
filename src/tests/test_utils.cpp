#include <cassert>
#include <sstream>
#include <format>

#include "Utils.hpp"
#include "Test.hpp"

using namespace stochastic;

#define test_vector vector{0,1,2,3,4,5,6,7,8,9}

int main(int argc, char const *argv[]){
    TestTemplate test("Constexpr tests");
    new_test(test, "test make_range",
        if constexpr (make_range<int>(10) == test_vector)
            assert(true);
        else
            assert(false);
    );
    
    new_test(test, "test sum",
        if constexpr (sum(test_vector) > 0)
            assert(true);
        else
            assert(false);
    );

    new_test(test, "test mean",
        if constexpr (mean(test_vector) > 0)
            assert(true);
        else
            assert(false);
    );

    new_test(test, "test all",
        if constexpr (!all(test_vector)) // test_vector[0] is false
            assert(true);
        else
            assert(false);
    );

    new_test(test, "test any",
        if constexpr (any(test_vector))
            assert(true);
        else
            assert(false);
    );

    test.run();
}