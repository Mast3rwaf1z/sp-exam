#pragma once

#include <string>
#include <sstream>
#include <ostream>
#include <memory>

using namespace std;

namespace stochastic {
    class Reactant {
    public:
        string name;
        double value;
        double max;
        double min;
        constexpr Reactant() = default;
        constexpr Reactant(const string& name, const double& value);
        constexpr ~Reactant() = default;

        Reactant& operator++() {
            value++;
            if(value > max)
                max = value;
            return *this;
        }
        Reactant& operator--() {
            value--;
            if(value < max)
                max = value;
            return *this;
        }

        Reactant operator++(int) {
            Reactant old = *this;
            operator++();
            return old;
        }
        Reactant operator--(int) {
            Reactant old = *this;
            operator--();
            return old;
        }
    };

    constexpr Reactant::Reactant(const string& name, const double& value) : value(value), max(value), min(value), name(name) {
    }

    ostream& operator<<(ostream& os, const Reactant& r) {
        return os << r.name << ":" << r.value;
    }

    class illegal_reactant_exception : public exception {
        Reactant r;
        string message = "";
        public:
            illegal_reactant_exception(Reactant r) : r(r) {
            }
            string what(){
                if(message != "") return message;
                stringstream ss;
                ss << "\033[38;2;255;0;0m" << "ERROR! illegal reactant" << "\033[0m " << r.name << ":" << r.value;
                return ss.str();
            }
    };
}