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

#if 0
    #include <chrono>
    #include <thread>
    #define DEBUG this_thread::sleep_for(chrono::seconds(1))
#else
    #define DEBUG 
#endif

using namespace std;

namespace stochastic {

    class Vessel {
    private:
        string name;
        unordered_map<string, double> reactants = {{"env", 0}};
        vector<Reaction> reactions; 
        bool plot = false;
        bool printing = false;
        unordered_map<string, pair<vector<double>, vector<double>>> plotting_data;

    public:
        vector<shared_ptr<Observer_t>> observers;
        Vessel(const string& name);
        ~Vessel() = default;
        Reactant add(const string&, const double&);
        Vessel& add(const Reaction&);
        Reactant environment();
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
            for(const auto& [name, value] : v.reactants) {
                os << Reactant(name, value) << endl;
            }
            return os;
        }
        
        double& operator[](const string& name) {
            return reactants[name];
        }
    };
    
    Vessel::Vessel(const string& name) {
        this->name = name;
    }
    Reactant Vessel::add(const string& name, const double& value) {
        for(auto& [name_, value_] : reactants) if(name_ == name){
            throw illegal_reactant_exception(Reactant(name_, value_));
        }
        auto r = Reactant(name, value);
        reactants[name] = value;
        plotting_data[name] = {{}, {}};
        return r;
    }
    Vessel& Vessel::add(const Reaction& r){
        this->reactions.push_back(r);
        return *(this);
    }

    Reactant Vessel::environment(){
        return Reactant("env", operator[]("env"));
    }

    constexpr ReactionBuilder operator>>(const Reactant& lhs, const double rhs) {
        return {{lhs}, rhs};
    }
    constexpr ReactionBuilder operator>>(const vector<Reactant>& lhs, const double rhs) {
        return {lhs, rhs};
    }

    constexpr vector<Reactant> operator+(const Reactant& lhs, const Reactant& rhs) {
        return {lhs, rhs};
    }

    constexpr Reaction operator>>=(const ReactionBuilder& lhs, const Reactant& rhs) {
        vector<Reactant> obj{rhs};
        auto& [input, lambda] = lhs;
        return Reaction(input, lambda, obj);
    }
    constexpr Reaction operator>>=(const ReactionBuilder& lhs, const vector<Reactant>& rhs) {
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
                r.computeDelay(reactants);
            auto& r = argmin(reactions);
            t = t + r.delay;
            DEBUG; // sleep for 1 if debugging is enabled
            if(all(r.input, (function<bool(Reactant)>)[this](Reactant r) { return reactants[r.name] > 0; })) {
                if(printing) cout << r << endl;
                for(auto& i : r.input)
                    reactants[i.name]--;
                for(auto& o : r.output)
                    reactants[o.name]++;
            }
            for(auto observer : observers)
                observer->run();

            if(plot) for(const auto& [name, value] : reactants){
                plotting_data[name].first.push_back(t);
                plotting_data[name].second.push_back(value);
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