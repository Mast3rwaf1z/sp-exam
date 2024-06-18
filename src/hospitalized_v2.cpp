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
    auto vessels = make_range<shared_ptr<Vessel>>(100, [](int i){
        return make_shared<Vessel>(seihr(NNJ));
    });
    auto observers = make_range<shared_ptr<Observer<double>>>(100, [&vessels](int i){
        auto vessel = vessels[i];
        shared_ptr<Observer<double>> observer = make_shared<Observer<double>>([&vessel, &observer](){
            if((*vessel)["H"]->value > observer->data)
                observer->data = (*vessel)["H"]->value;
        });
        observer->setData(0);
        return observer;
    });

    SimulationBatch batch(vessels, 8, 100);
    batch.run();

    vector<double> result;
    for(auto observer : observers){
        result.push_back(observer->data);
    }
    cout << "result: " << mean(result) << endl;
}