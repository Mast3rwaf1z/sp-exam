class Algorithm {
public:
  Algorithm();
  Algorithm(Algorithm &&) = default;
  Algorithm(const Algorithm &) = default;
  Algorithm &operator=(Algorithm &&) = default;
  Algorithm &operator=(const Algorithm &) = default;
  ~Algorithm();
  void run(vector<Reactant>, int);
private:
  
};

class Reactant {
public:
  Reactant();
  Reactant(Reactant &&) = default;
  Reactant(const Reactant &) = default;
  Reactant &operator=(Reactant &&) = default;
  Reactant &operator=(const Reactant &) = default;
  ~Reactant();
  void calculateDelay();

private:
  
};

Reactant::Reactant() {
}

Reactant::~Reactant() {
}

Algorithm::Algorithm() {
}

Algorithm::~Algorithm() {
} 
