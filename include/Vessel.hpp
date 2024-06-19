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
        vector<Reactant> reactants = {Reactant("env", 0)};
        vector<Reaction> reactions; 
        bool plot = false;
        bool printing = false;
        map<string, pair<vector<double>, vector<double>>> plotting_data;

    public:
        vector<shared_ptr<Observer_t>> observers;
        Vessel(const string& name);
        ~Vessel() = default;
        Reactant& add(const string&, const double&);
        Vessel& add(const Reaction&);
        Reactant& environment();
        Vessel& run(const double&);
        Vessel& enable_plotting(const bool&);
        Vessel& enable_printing(const bool&);
        Vessel& add_observer(shared_ptr<Observer_t>);
        void plot_data(const vector<string>&);

        friend ostream& operator<<(ostream& os, const Vessel& v){
            os << "--------------- " << v.name << " ---------------" << endl;
            os << "--------------- Reactions ---------------" << endl;
            for(const auto& reaction : v.reactions) {
                os << reaction << endl;
            }
            os << "--------------- Reactants ---------------" << endl;
            for(const auto& reactant : v.reactants) {
                os << reactant << endl;
            }
            return os;
        }
        
        Reactant& operator[](const string& name) {
            for(auto& reactant : reactants) {
                if(reactant.name == name) {
                    return reactant;
                }
            }
            throw illegal_reactant_exception();
        }
    };
    
    Vessel::Vessel(const string& name) {
        this->name = name;
    }
    Reactant& Vessel::add(const string& name, const double& value) {
        for(auto& r : reactants) if(r.name == name){
            throw illegal_reactant_exception(r);
        }
        auto r = Reactant(name, value);
        reactants.push_back(r);
        plotting_data[name] = {{}, {}};
        return reactants.back();
    }
    Vessel& Vessel::add(const Reaction& r){
        this->reactions.push_back(r);
        return *(this);
    }

    Reactant& Vessel::environment(){
        return (*this)["env"];
    }

    ReactionBuilder operator>>(const Reactant& lhs, const double rhs) {
        return {{lhs}, rhs};
    }
    ReactionBuilder operator>>(const vector<Reactant>& lhs, const double rhs) {
        return {lhs, rhs};
    }

    vector<Reactant> operator+(const Reactant& lhs, const Reactant& rhs) {
        return {lhs, rhs};
    }

    Reaction operator>>=(const ReactionBuilder& lhs, const Reactant& rhs) {
        vector<Reactant> obj{rhs};
        auto& [input, lambda] = lhs;
        return Reaction(input, lambda, obj);
    }
    Reaction operator>>=(const ReactionBuilder& lhs, const vector<Reactant>& rhs) {
        auto& [input, lambda] = lhs;
        return Reaction(input, lambda, rhs);
    }

    Vessel& Vessel::enable_plotting(const bool& enable) {
        plot = enable;
        return *(this);
    }

    Vessel& Vessel::enable_printing(const bool& enable) {
        printing = enable;
        return *(this);
    }

    Vessel& Vessel::add_observer(shared_ptr<Observer_t> o) {
        observers.push_back(o);
        return *this;
    }

    Vessel& Vessel::run(const double& T) {
        double t = 0;
        while(t <= T) {
            for(auto& r : this->reactions)
                r.computeDelay();
            auto& r = argmin(reactions);
            t = t + r.delay;
            if(all(r.input, (function<bool(shared_ptr<Reactant>)>)[](shared_ptr<Reactant> r) { return r->value > 0; })) {
                if(printing) cout << r << endl;
                for(auto& i : r.input)
                    i->operator--();
                for(auto& o : r.output)
                    o->operator++();
            }
            for(auto observer : observers)
                observer->run();

            if(plot) for(const auto& reactant : reactants){
                plotting_data[reactant.name].first.push_back(t);
                plotting_data[reactant.name].second.push_back(reactant.value);
            }
        }
        return *this;
    }

    void Vessel::plot_data(const vector<string>& names){
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