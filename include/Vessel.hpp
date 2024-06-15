#pragma once
    
#include <iostream>
#include <format>
#include <map>
#include <vector>
#include <ostream>
#include <memory>

#include "Reactant.hpp"
#include "ReactionBuilder.hpp"
#include "Reaction.hpp"
#include "Utils.hpp"

using namespace std;

namespace stochastic {
    
    

    class Vessel {
    private:
        string name;
        vector<shared_ptr<Reactant>> reactants;
        vector<shared_ptr<Reaction>> reactions; 
    public:
        Vessel(string name);
        ~Vessel();
        shared_ptr<Reactant> add(string, double);
        void add(shared_ptr<Reaction>);
        shared_ptr<Reactant> environment();
        void run(double);
        void run(double, bool);

        friend ostream& operator<<(ostream& os, const Vessel& v){
            os << "--------------- " << v.name << " ---------------" << endl;
            os << "--------------- Reactions ---------------" << endl;
            for(auto reaction : v.reactions) {
                os << *(reaction) << endl;
            }
            os << "--------------- Reactants ---------------" << endl;
            for(auto reactant : v.reactants) {
                os << *(reactant) << endl;
            }
            return os;
        }
        
        shared_ptr<Reactant> operator[](const string& name) {
            for(auto reactant : reactants) {
                if(reactant->name == name) {
                    return reactant;
                }
            }
            exit(1);
        }
    };
    
    Vessel::Vessel(string name) {
        this->name = name;
    }
    
    Vessel::~Vessel() {
    }
    shared_ptr<Reactant> Vessel::add(string name, double value) {
        auto r = make_shared<Reactant>(name, value);
        reactants.push_back(r);
        return r;
    }
    void Vessel::add(shared_ptr<Reaction> r){
        this->reactions.push_back(r);
    }

    shared_ptr<Reactant> Vessel::environment(){
        return make_shared<Reactant>("env", 0);
    }

    ReactionBuilder operator>>(shared_ptr<Reactant> lhs, double rhs) {
        ReactionBuilder builder({lhs}, rhs);
        return builder;
    }
    ReactionBuilder operator>>(vector<shared_ptr<Reactant>> lhs, double rhs) {
        ReactionBuilder builder(lhs, rhs);
        return builder;
    }

    vector<shared_ptr<Reactant>> operator+(shared_ptr<Reactant> lhs, shared_ptr<Reactant> rhs) {
        return {lhs, rhs};
    }

    shared_ptr<Reaction> operator>>=(ReactionBuilder lhs, shared_ptr<Reactant> rhs) {
        vector<shared_ptr<Reactant>> obj{rhs};
        return make_shared<Reaction>(lhs, obj);
    }
    shared_ptr<Reaction> operator>>=(ReactionBuilder lhs, vector<shared_ptr<Reactant>> rhs) {
        Reaction r(lhs, rhs);
        return make_shared<Reaction>(lhs, rhs);
    }

    void Vessel::run(double T){
        return run(T, true);
    }

    void Vessel::run(double T, bool print) {
        double t = 0;
        while(t <= T) {
            for(auto r : this->reactions)
                r->computeDelay();
            auto r = argmin(reactions);
            t = t + r->delay;
            if(all(r->input, (function<bool(shared_ptr<Reactant>)>)[](shared_ptr<Reactant> r) { return r->value > 0; })) {
                if(print) cout << *(r) << endl;
                for(auto i : r->input)
                    i->value--;
                for(auto o : r->output)
                    o->value++;
            }
        }
    }
    
}