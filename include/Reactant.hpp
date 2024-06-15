#pragma once

#include <string>
#include <ostream>

using namespace std;

namespace stochastic {
    class Reactant {
    public:
        string name;
        double value;
        Reactant() = default;
        Reactant(string name, double value);
        ~Reactant();
    };

    Reactant::Reactant(string name, double value) {
        this->value = value;
        this->name = name;
    }
    
    Reactant::~Reactant() {
    }

    ostream& operator<<(ostream& os, const Reactant& r) {
        return os << r.name << ":" << r.value;
    }
}