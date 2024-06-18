#include "SimulationBatch.hpp"
#include "Utils.hpp"
#include "Models.hpp"

using namespace std;
using namespace stochastic;

int main(int argc, char const *argv[]){
    SimulationBatch batch(make_range<shared_ptr<Vessel>>(100, [](int i){
        return make_shared<Vessel>(seihr(NNJ));
    }), 8, 100);
    batch.run();

    vector<double> results;
    for(auto sim : batch.simulations)
        results.push_back((*sim)["H"]->max);
    std::cout << "---------------" << endl;
    std::cout << "Hospitalized mean: " << mean(results) << endl;
}
