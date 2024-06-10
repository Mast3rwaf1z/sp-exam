namespace stochastic {
  class Vessel {
  public:
    Vessel();
    Vessel(Vessel &&) = default;
    Vessel(const Vessel &) = default;
    Vessel &operator=(Vessel &&) = default;
    Vessel &operator=(const Vessel &) = default;
    ~Vessel();
    template<typename T>
    T add(std::string, T);
    T environment();
  private:
    
  };

  Vessel::Vessel() {
  }

  Vessel::~Vessel() {
  }
}
