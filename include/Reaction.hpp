#pragma once
#include <vector>
#include <random>
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>

#include "ReactionBuilder.hpp"
#include "Reactant.hpp"
#include "Utils.hpp"

using namespace std;

namespace stochastic {
    class Reaction {
    public:
        vector<Reactant> input;
        double lambda;
        vector<Reactant> output;
        double delay;

        constexpr Reaction() = default;
        constexpr Reaction(const vector<Reactant>&, const double, const vector<Reactant>&);
        constexpr ~Reaction() = default;
        void computeDelay(const unordered_map<string, double>);


        constexpr Reaction& operator=(const Reaction& rhs){
            this->input = rhs.input;
            this->lambda = rhs.lambda;
            this->output = rhs.output;
            return *this;
        }
    };
    constexpr Reaction::Reaction(const vector<Reactant>& input, const double lambda, const vector<Reactant>& output) : input(input), lambda(lambda), output(output) {
    }


    ostream& operator<<(ostream& os, const Reaction& r) {
        vector<string> inputNames;
        vector<string> outputNames;
        for(const auto& input : r.input)
            inputNames.push_back(input.name);
        for(const auto& output : r.output)
            outputNames.push_back(output.name);

        os << join(inputNames, " + ");
        os << "\t--" << "\u03bb" << "->\t";
        os << join(outputNames, " + ");
        return os;
    }

    void Reaction::computeDelay(unordered_map<string, double> reactants) {
        double product = 1;
        random_device rd;
        mt19937 gen(rd());
        for(const auto& i : input){
            product *= reactants[i.name];
        }

        delay = exponential_distribution(lambda * product)(gen);
    }
    Reaction& argmin(vector<Reaction>& reactions) {
        auto choice = 0;
        for(auto i = 0; i < reactions.size(); i++){
            if(reactions[i].delay <= reactions[choice].delay){
                choice = i;
            }
        }
        return reactions[choice];
    }
}