#include <ranges>

#include "matplot/matplot.h"

#include "Vessel.hpp"
#include "Models.hpp"

using namespace stochastic;

int main(int argc, char* argv[]){
    vector<string> args(argv+1, argv+argc);
    auto plottarget = args.size() > 0 ? stoi(args[0]) : -1;
    vector<Vessel> sims = {example1(), example2(), example3()};
    for(auto [i, sim] : views::zip(make_range<int>(sims.size()), sims)) {
        if(i == plottarget) sim.enable_plotting(true);
        sim.enable_printing(false);
        sim.run(3000);
        cout << sim << endl;
        if(i == plottarget) 
            sim.plot_data({"A", "B", "C"});
    }
}