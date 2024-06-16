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
        vector<shared_ptr<Vessel>> simulations;
        future<void> instance;
        shared_ptr<mutex> m;
        int T;
        int id;
    public:
        Worker(int, int);
        ~Worker();
        void start();
        void add(shared_ptr<Vessel>);
        void run();
        void join();
    };
    Worker::Worker(int T, int id) : T(T), id(id) {
        m = make_shared<mutex>();
    }
    Worker::~Worker(){
    }
    void Worker::start() {
        m->lock();
        instance = async(launch::async, [&](){ return this->run(); });
    }
    void Worker::run() {
        for(auto [i, simulation] : views::zip(make_range<int>(simulations.size()), simulations)) {
            simulation->run(T);
            cout << "Worker " << id << " Finished a simulation. " << simulations.size()-i << " left." << endl;
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
            workers.push_back(make_shared<Worker>(T, i));
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