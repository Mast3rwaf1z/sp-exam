#pragma once
#include <vector>
#include <functional>
#include <string>
#include <sstream>

#include "Reaction.hpp"

using namespace std;

namespace stochastic {
    template<typename T>
    bool all(vector<T> input, function<bool(T)> validator) {
        for(auto value : input) {
            if(!validator(value))
                return false;
        }
        return true;
    }
    template<typename T>
    string join(vector<T> input, string delimiter) {
        stringstream ss;
        const auto last = &(input.back());
        for(auto index = 0; index < input.size()-1; index++)
            ss << input[index] << delimiter;
        ss << input[input.size()-1];
        return ss.str();
    }

    template<typename T>
    vector<T> make_range(size_t size) {
        vector<T> result;
        for(auto i = 0; i < size; i++)
            result.push_back((T)i);
        return result;
    }

    template<typename T>
    vector<T> make_range(size_t lower, size_t upper) {
        vector<T> result;
        for(auto i = lower; i < upper; i++)
            result.push_back((T)i);
        return result;
    }
    template<typename T>
    vector<T> make_range(size_t size, function<T(int)> func) {
        vector<T> result; 
        for(auto i = 0; i < size; i++)
            result.push_back(func(i));
        return result;
    }
    template<typename T>
    vector<T> make_range(size_t lower, size_t upper, function<T(int)> func) {
        vector<T> result;
        for(auto i = lower; i < upper; i++)
            result.push_back(func(i));
        return result;
    }
}