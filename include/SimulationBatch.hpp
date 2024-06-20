#pragma once
#include <vector>
#include <future>
#include <functional>
#include <mutex>
#include <ranges>

#include "Vessel.hpp"

namespace stochastic {
    class Worker{
    private:
        vector<Vessel> simulations;
        future<void> instance;
        mutex m;
        const int T;
        const int id;
    public:
        Worker() = default;
        Worker(const Worker&);
        Worker(const int&, const int&);
        ~Worker();
        void start();
        void add(const Vessel&);
        void run();
        void join();
    };
    Worker::Worker(const Worker& worker) : T(worker.T), id(worker.id) {

    }
    Worker::Worker(const int& T, const int& id) : T(T), id(id) {
    }
    Worker::~Worker(){
    }
    void Worker::start() {
        m.lock();
        instance = async(launch::async, [&](){ return this->run(); });
    }
    void Worker::run() {
        for(auto i : make_range<int>(simulations.size())){
            simulations[i].run(T);
            cout << "Worker " << id << " Finished a simulation. " << simulations.size()-i << " left." << endl;
        }
        m.unlock();
    }
    void Worker::add(const Vessel& simulation){
        simulations.push_back(simulation);
    }
    void Worker::join(){
        // wait on the lock and unlock it again immediately
        m.lock();
        m.unlock();
    }

    class SimulationBatch {
    public:
        vector<Worker> workers;
        vector<Vessel> simulations;
        SimulationBatch(const vector<Vessel>&, const int&, const int&);
        ~SimulationBatch();
        void run();
    };
    
    SimulationBatch::SimulationBatch(const vector<Vessel>& simulations, const int& coreCount, const int& T) : simulations(simulations) {
        for(auto i = 0; i < coreCount; i++) {
            workers.push_back(Worker(T, i));
        }
        for(auto i = 0; i < simulations.size(); i++) {
            workers[i%coreCount].add(simulations[i]);
        }

    }
    
    SimulationBatch::~SimulationBatch(){
    }
    void SimulationBatch::run(){
        for(auto& worker : workers)
            worker.start();
        cout << "Started " << workers.size() << " Workers..." << endl;
        
        for(auto& worker : workers)
            worker.join();
        
        for(auto& simulation : simulations){
            cout << simulation << endl;
        }
    }
    
}