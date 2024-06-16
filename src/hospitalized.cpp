#include "SimulationBatch.hpp"
#include "Utils.hpp"
#include "Models.hpp"

using namespace std;
using namespace stochastic;


template<typename T>
class Observer : public Observer_t {
private:
    function<void(void)> collector;
public:
    shared_ptr<T> data;
    shared_ptr<Vessel> vessel;
    Observer() = default;
    Observer(function<void(void)>);
    ~Observer() = default;
    void add_vessel(shared_ptr<Vessel> v) {
        this->vessel = v;
    }
    virtual void run() override {
        return collector();
    }
};
template<typename T>
Observer<T>::Observer(function<void(void)> c) {
    collector = c;
    data = make_shared<T>();
}

int main(int argc, char const *argv[]){
    vector<shared_ptr<Observer<double>>> observers;
    SimulationBatch batch(make_range<shared_ptr<Vessel>>(100, [&observers](int i){
        shared_ptr<Observer<double>> observer = make_shared<Observer<double>>([observer]() {
            auto v = *(observer->vessel);
            auto value = v["H"]->value;
            if(value > *(observer->data))
                *(observer->data) = value;
        });
        shared_ptr<Vessel> v = make_shared<Vessel>(seihr(NNJ));
        observer->add_vessel(v);
        v->add_observer(observer);
        observers.push_back(observer);
        return v;
    }), 12, 100);
    batch.run();

    vector<double> results;
    for(auto observer : observers)
        results.push_back(*(observer->data));
    std::cout << "---------------" << endl;
    std::cout << "Hospitalized mean: " << mean(results) << endl;
}
