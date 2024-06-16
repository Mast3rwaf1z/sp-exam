#pragma once
#include "Reactant.hpp"

using namespace std;

namespace stochastic {
    class ReactionBuilder {
    public:
        vector<shared_ptr<Reactant>> lhs;
        double rhs;
        ReactionBuilder(vector<shared_ptr<Reactant>> lhs, const double& rhs);
        ~ReactionBuilder();
    };

    ReactionBuilder::ReactionBuilder(vector<shared_ptr<Reactant>> lhs, const double& rhs) {
        this->lhs = lhs;
        this->rhs = rhs;
    }
    
    ReactionBuilder::~ReactionBuilder() {
    }
}
