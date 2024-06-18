#pragma once
#include <vector>
#include <random>
#include <memory>
#include <thread>
#include <chrono>

#include "ReactionBuilder.hpp"
#include "Reactant.hpp"
#include "Utils.hpp"

using namespace std;

namespace stochastic {
    class Reaction {
    public:
        vector<shared_ptr<Reactant>> input;
        double lambda;
        vector<shared_ptr<Reactant>> output;
        double delay;

        Reaction() = default;
        constexpr Reaction(const Input&, const double, const Output&);
        constexpr ~Reaction() = default;
        void computeDelay();
    };
    constexpr Reaction::Reaction(const Input& input, const double lambda, const Output& output) {
        this->input = input;
        this->lambda = lambda;
        this->output = output;
    }

    ostream& operator<<(ostream& os, const Reaction& r) {
        vector<string> inputNames;
        vector<string> outputNames;
        for(auto input : r.input)
            inputNames.push_back(input->name);
        for(auto output : r.output)
            outputNames.push_back(output->name);

        os << join(inputNames, " + ");
        os << "\t--" << "\u03bb" << "->\t";
        os << join(outputNames, " + ");
        return os;
    }

    void Reaction::computeDelay() {
        double product = 1;
        random_device rd;
        mt19937 gen(rd());
        for(auto i : input){
            product *= i->value;
        }
        delay = exponential_distribution(lambda * product)(gen);
    }
    shared_ptr<Reaction> argmin(vector<shared_ptr<Reaction>> reactions) {
        shared_ptr<Reaction> choice = reactions[0];
        for(auto reaction : reactions) {
            if(reaction->delay <= choice->delay) {
                choice = reaction;
            }
        }
        return choice;
    }
}