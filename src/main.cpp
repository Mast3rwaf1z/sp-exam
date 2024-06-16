#include <iostream>
#include <format>
#include <cstdint>
#include <cmath>
#include <map>

#include "matplot/matplot.h"

#include "Vessel.hpp"
#include "SimulationBatch.hpp"
#include "Models.hpp"
#include "Observer.hpp"

using namespace std;
using namespace stochastic;

int main (int argc, char *argv[]) {
    vector<string> args(argv+1, argv+argc);
    auto T = args.size() > 0 ? stoi(args[0]) : 1000;

    cout << "Starting test program" << endl;
    cout << "Running with T = " << T << endl;
    auto simulation = circadian_rhythm();
    simulation = simulation.enable_printing(true);
    simulation.enable_plotting(false);
    simulation.run(T);
    cout << simulation << endl;
    simulation.plot_data({"A", "R", "C"});

}
