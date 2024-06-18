#include <chrono>

#include "Vessel.hpp"
#include "SimulationBatch.hpp"
#include "Utils.hpp"
#include "Models.hpp"

using namespace stochastic;
using namespace std;


int main(int argc, char const *argv[]) {
    map<int, double> speeds;
    for(auto cores : make_range<int>(1, 9)) {
        auto start = chrono::high_resolution_clock::now();
        auto simulations = make_range<Vessel>(1, 101, [](int index){ return circadian_rhythm(); });
        cout << "Simulations using " << cores << " core(s)" << endl;
        SimulationBatch batch1(simulations, cores, 24);
        batch1.run();
        auto end = chrono::high_resolution_clock::now();
        speeds[cores] = chrono::duration_cast<chrono::seconds>(end - start).count();
    }
    for(auto [cores, speed] : speeds) {
        cout << "Core count: " << cores << "\tSpeed(seconds): " << speed << endl;
    }

    return 0;
}
