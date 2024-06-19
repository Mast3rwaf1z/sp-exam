#include <memory>

#include "SimulationBatch.hpp"
#include "Observer.hpp"
#include "Models.hpp"
#include "Utils.hpp"

using namespace stochastic;

template<typename T>
class Observer : public Observer_t {
private:
    function<void(void)> collector;
public:
    T data;
    shared_ptr<Vessel> vessel;
    Observer() = default;
    Observer(function<void(void)>);
    ~Observer() = default;
    void add_vessel(shared_ptr<Vessel> v) {
        this->vessel = v;
    }
    void setData(T in) {
        data = in;
    }
    virtual void run() override {
        return collector();
    }
};
template<typename T>
Observer<T>::Observer(function<void(void)> c) {
    collector = c;
}

int main(){
    vector<shared_ptr<Observer<double>>> observers;
    SimulationBatch batch(make_range<Vessel>(100, [&](int i){
        auto v = seihr(NNJ);
        shared_ptr<Observer<double>> observer = make_shared<Observer<double>>([&v, observer](){
            if(v["H"].value > observer->data)
                observer->data = v["H"].value;
        });
        observer->setData(0);
        v.add_observer(observer);
        observers.push_back(observer);
        return v;
    }), 12, 100);

    batch.run();
    vector<double> results;
    for(auto observer : observers){
        results.push_back(observer->data);
    }
    vector<double> results_s;
    for(auto sim : batch.simulations){
        results_s.push_back((*sim)["H"].max);
    }
    cout << "Mean hospitalized: " << mean(results) << endl;

    // This implementation should get removed, its just a jank workaround to get the max, but it should ideally get fetched from the observer.
    cout << "Sanity check:      " << mean(results_s) << endl;
}