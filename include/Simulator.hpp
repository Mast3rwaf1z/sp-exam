#include <map>

namespace stochastic {
  template<typename T>
  class Value {
  public:
    Value(T value) {
      this->value = value;
    };
    Value(Value &&) = default;
    Value(const Value &) = default;
    Value &operator=(Value &&) = default;
    Value &operator=(const Value &) = default;
    ~Value() = default;

  private:
    T value;
    
  };

  class IntValue : public Value<int>{
  public:
    using Value::Value;
    IntValue(IntValue &&) = default;
    IntValue(const IntValue &) = default;
    IntValue &operator=(IntValue &&) = default;
    IntValue &operator=(const IntValue &) = default;
    ~IntValue();

  };

  class Vessel {
  public:
    Vessel(std::string name) {

    }
    Vessel(Vessel &&) = default;
    Vessel(const Vessel &) = default;
    Vessel &operator=(Vessel &&) = default;
    Vessel &operator=(const Vessel &) = default;
    ~Vessel();
    template<typename T>
    T add(std::string, T);
    template<typename T>
    T environment();
  private:
    std::map<std::string, Value> values;
  };

  int Vessel::add<int>(std::string name, int value){
    values[name] = IntValue{value};
    return value;
  }

  int Vessel::environment(){
    return 0;
  }
}
