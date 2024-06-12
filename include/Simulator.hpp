#if DEBUG
    #include <iostream>
    #define log(what) std::cout << "LOG: " << what << std::endl
#else
    #define log(what)
#endif
    
#include <format>

namespace stochastic {
    template<typename T>
    class Reactant {
    private:
        std::string name;
    public:
        T value;
        Reactant() = delete;
        Reactant(T value) : value(value) {
            log("Called constructor");
        }

        ~Reactant() = default;

        template<typename T1>
        friend Reactant operator+(Reactant lhs, const Reactant<T1>& rhs) {
            log("Called operator+ with " << lhs << " and " << rhs);
            return lhs.value + rhs.value;
        }

        friend std::ostream& operator<<(std::ostream& os, const Reactant& obj) {
            return os << std::format("Reactant<{}>: ", std::string(typeid(obj.value).name())) << obj.value;
        }
        
        friend Reactant operator>>(Reactant lhs, const Reactant time) {
            log("Called operator>> with " << lhs << " and " << time);
            return lhs + time;
        }

        friend Reactant operator>>(Reactant lhs, const int time) {
            log("Called operator>> with " << lhs << " and " << time);
            Reactant r(time);
            return lhs + r;
        }

        template<typename T1>
        friend Reactant operator>>=(Reactant lhs, const Reactant<T1> rhs) {
            log("Called operator>>= with " << lhs << " and " << rhs);
            return lhs + rhs;
        }

        friend T operator+=(T lhs, const Reactant& rhs) {
            log("Called operator+= with " << lhs << " and " << rhs);
            return lhs += rhs.value;
        }
    };

    class Vessel {
    public:
        Vessel(std::string name) {
            log("Called vessel constructor with " << name);
            this->name = name;
        }
        Vessel(Vessel &&) = default;
        Vessel(const Vessel &) = default;
        Vessel &operator=(Vessel &&) = default;
        Vessel &operator=(const Vessel &) = default;
        ~Vessel() = default;
        template<typename T>
        Reactant<T> add(std::string name, const T value) {
            log("Called add with " << name << " and " << value);
            Reactant<T> r(value);
            return add(r);
        }
        template<typename T>
        Reactant<T> add(const Reactant<T>& value) {
            log("Called add with " << value);
            return this->value += value;
        }
        template<typename T>
        Reactant<T> environment() {
            log("Called environment");
            return value;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vessel& obj){
            return os << obj.value;
        }
    private:
        double value;
        std::string name;

    };
}