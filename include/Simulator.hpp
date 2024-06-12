namespace stochastic {
    template<typename T>
    class Reactant {
    private:
        T value;
        std::string name;
    public:
        Reactant() = delete;
        Reactant(T&& value) : value(value) {

        }

        ~Reactant() = default;

        friend Reactant operator+(Reactant lhs, const Reactant& rhs) {
            return lhs.value + rhs.value;
        }

        friend std::ostream& operator<<(std::ostream& os, const Reactant& obj) {
            return os << "Reactant: " << obj.value;
        }
        
        friend Reactant operator>>(Reactant lhs, const Reactant time) {
            return lhs + time;
        }

        friend Reactant operator>>=(Reactant lhs, const Reactant rhs) {
            return lhs + rhs;
        }
    };

    class Vessel {
    public:
        Vessel(std::string name) {
            this->name = name;
        }
        Vessel(Vessel &&) = default;
        Vessel(const Vessel &) = default;
        Vessel &operator=(Vessel &&) = default;
        Vessel &operator=(const Vessel &) = default;
        ~Vessel() = default;
        template<typename T>
        Reactant<T> add(std::string name, T value){
            return add(value);
        }
        template<typename T>
        Reactant<T> add(const Reactant<T> value) {
        }
        template<typename T>
        Reactant<T> environment() {

        }
    private:
        double value;
        std::string name;

    };
}