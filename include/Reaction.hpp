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
        Reaction(const vector<Reactant>&, const double, const vector<Reactant>&);
        ~Reaction() = default;
        void computeDelay();
    };
    Reaction::Reaction(const vector<Reactant>& input, const double lambda, const vector<Reactant>& output) : lambda(lambda) {
        for(const auto& element : input)
            this->input.push_back(make_shared<Reactant>(element));
        for(const auto& element : output)
            this->output.push_back(make_shared<Reactant>(element));
    }

    ostream& operator<<(ostream& os, const Reaction& r) {
        vector<string> inputNames;
        vector<string> outputNames;
        for(const auto& input : r.input)
            inputNames.push_back(input->name);
        for(const auto& output : r.output)
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
        for(const auto& i : input){
            product *= i->value;
        }
        delay = exponential_distribution(lambda * product)(gen);
    }
    Reaction& argmin(vector<Reaction>& reactions) {
        auto& choice = reactions[0];
        for(const auto& reaction : reactions) {
            if(reaction.delay <= choice.delay) {
                choice = reaction;
            }
        }
        return choice;
    }
}