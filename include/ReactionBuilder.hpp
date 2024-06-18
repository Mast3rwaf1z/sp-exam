#pragma once
#include <vector>
#include <map>
#include <memory>

#include "Reactant.hpp"

using namespace std;

namespace stochastic {
    typedef vector<shared_ptr<Reactant>> Input;
    typedef Input Output;
    typedef pair<Input, double> ReactionBuilder;

}
