#include <memory>

#include "Observer.hpp"
#include "Vessel.hpp"
#include "Models.hpp"

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
    virtual void run() override {
        return collector();
    }
};
template<typename T>
Observer<T>::Observer(function<void(void)> c) {
    collector = c;
}

int main(){
    auto v = circadian_rhythm();
    shared_ptr<Observer<double>> observer = make_shared<Observer<double>>([&v, &observer](){ observer->data = v["A"]->value; });
    v.enable_printing(true);
    v.add_observer(observer);
    v.run(10);
    cout << observer->data << endl;
}