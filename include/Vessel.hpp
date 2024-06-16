#pragma once
    
#include <iostream>
#include <format>
#include <map>
#include <vector>
#include <ostream>
#include <memory>

#include "matplot/matplot.h"

#include "Reactant.hpp"
#include "ReactionBuilder.hpp"
#include "Reaction.hpp"
#include "Utils.hpp"
#include "Observer.hpp"

using namespace std;

namespace stochastic {

    class Vessel {
    private:
        string name;
        vector<shared_ptr<Reactant>> reactants;
        vector<shared_ptr<Reaction>> reactions; 
        bool plot = false;
        bool printing = false;
        map<string, pair<vector<double>, vector<double>>> plotting_data;

    public:
        vector<shared_ptr<Observer_t>> observers;
        Vessel(string name);
        ~Vessel();
        shared_ptr<Reactant> add(string, double);
        Vessel add(shared_ptr<Reaction>);
        shared_ptr<Reactant> environment();
        Vessel run(double);
        Vessel enable_plotting(bool);
        Vessel enable_printing(bool);
        Vessel add_observer(shared_ptr<Observer_t>);
        void plot_data(vector<string>);

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
            throw illegal_reactant_exception();
        }
    };
    
    Vessel::Vessel(string name) {
        this->name = name;
    }
    
    Vessel::~Vessel() {
    }
    shared_ptr<Reactant> Vessel::add(string name, double value) {
        for(auto r : reactants) if(r->name == name){
            throw illegal_reactant_exception(r);
        }
        auto r = make_shared<Reactant>(name, value);
        reactants.push_back(r);
        plotting_data[name] = {{}, {}};
        return r;
    }
    Vessel Vessel::add(shared_ptr<Reaction> r){
        this->reactions.push_back(r);
        return *(this);
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

    Vessel Vessel::enable_plotting(bool enable) {
        plot = enable;
        return *(this);
    }

    Vessel Vessel::enable_printing(bool enable) {
        printing = enable;
        return *(this);
    }

    Vessel Vessel::add_observer(shared_ptr<Observer_t> o) {
        observers.push_back(o);
        return *this;
    }

    Vessel Vessel::run(double T) {
        double t = 0;
        while(t <= T) {
            for(auto r : this->reactions)
                r->computeDelay();
            auto r = argmin(reactions);
            t = t + r->delay;
            if(all(r->input, (function<bool(shared_ptr<Reactant>)>)[](shared_ptr<Reactant> r) { return r->value > 0; })) {
                if(printing) cout << *(r) << endl;
                for(auto i : r->input)
                    i->operator--();
                for(auto o : r->output)
                    o->operator++();
            }
            for(auto observer : observers)
                observer->run();

            if(plot) for(auto reactant : reactants){
                plotting_data[reactant->name].first.push_back(t);
                plotting_data[reactant->name].second.push_back(reactant->value);
            }
        }
        return *this;
    }

    void Vessel::plot_data(vector<string> names){
        namespace plt = matplot;
        if(!plot) {
            cerr << "Error! plotting is not enabled for this simulation!" << endl;
            exit(1);
        }
        plt::hold(plt::on);
        for(auto name : names) {
            auto [xs, ys] = plotting_data[name];
            plt::plot(xs, ys);
        }
        plt::legend(names);
        cout << "Plotting data" << endl;
        plt::save(format("figures/{}.png", this->name));
    }
    
}