#include "Vessel.hpp"

using namespace stochastic;

Vessel example1(){
    Vessel v{"Example 1"};
    const auto lambda = 0.001;
    const auto A = v.add("A", 100);
    const auto B = v.add("B", 0);
    const auto C = v.add("C", 1);
    v.add((A + C) >> lambda >>= (B + C));
    return v;
}

Vessel example2(){
    Vessel v{"Example 2"};
    const auto lambda = 0.001;
    const auto A = v.add("A", 100);
    const auto B = v.add("B", 0);
    const auto C = v.add("C", 2);
    v.add((A + C) >> lambda >>= (B + C));
    return v;
}

Vessel example3(){
    Vessel v{"Example 3"};
    const auto lambda = 0.001;
    const auto A = v.add("A", 50);
    const auto B = v.add("B", 50);
    const auto C = v.add("C", 1);
    v.add((A + C) >> lambda >>= (B + C));
    return v;
}
int main(){
    auto sims = {example1(), example2(), example3()};
    for(auto sim : sims) {
        sim.run(2000);
        cout << sim << endl;
    }
}