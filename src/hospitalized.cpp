#include "SimulationBatch.hpp"
#include "Utils.hpp"
#include "Models.hpp"

using namespace std;
using namespace stochastic;

int main(int argc, char const *argv[]){
    SimulationBatch batch(make_range<Vessel>(100, [](int i){
        return seihr(NNJ);
    }), 12, 100);
    batch.run();

    vector<double> results;
    for(auto sim : batch.simulations)
        results.push_back((*sim)["H"]->max);
    std::cout << "---------------" << endl;
    std::cout << "Hospitalized mean: " << mean(results) << endl;
}
