#pragma once
#include <vector>
#include <future>
#include <functional>
#include <mutex>

#include "Vessel.hpp"

namespace stochastic {
    class Worker{
    private:
        vector<shared_ptr<Vessel>> simulations;
        future<void> instance;
        shared_ptr<mutex> m;
        int T;
    public:
        Worker(int);
        ~Worker();
        void start();
        void add(shared_ptr<Vessel>);
        void run();
        void join();
    };
    Worker::Worker(int T) : T(T) {
        m = make_shared<mutex>();
    }
    Worker::~Worker(){
    }
    void Worker::start() {
        m->lock();
        instance = async(launch::async, [&](){ return this->run(); });
    }
    void Worker::run() {
        for(auto simulation : simulations) {
            simulation->run(T, false);
        }
        m->unlock();
    }
    void Worker::add(shared_ptr<Vessel> simulation){
        simulations.push_back(simulation);
    }
    void Worker::join(){
        // wait on the lock and unlock it again immediately
        m->lock();
        m->unlock();
    }

    class SimulationBatch {
    public:
        vector<shared_ptr<Worker>> workers;
        vector<shared_ptr<Vessel>> simulations;
        SimulationBatch(vector<shared_ptr<Vessel>>, int, int);
        ~SimulationBatch();
        void run();
    };
    
    SimulationBatch::SimulationBatch(vector<shared_ptr<Vessel>> simulations, int coreCount, int T) {
        this->simulations = simulations;
        for(auto i = 0; i < coreCount; i++) {
            workers.push_back(make_shared<Worker>(T));
        }
        for(auto i = 0; i < simulations.size(); i++) {
            workers[i%coreCount]->add(simulations[i]);
        }

    }
    
    SimulationBatch::~SimulationBatch(){
    }
    void SimulationBatch::run(){
        for(auto& worker : workers)
            worker->start();
        cout << "Started " << workers.size() << " Workers..." << endl;
        
        for(const auto& worker : workers)
            worker->join();
        
        for(auto simulation : simulations){
            cout << *(simulation) << endl;
        }
    }
    
}