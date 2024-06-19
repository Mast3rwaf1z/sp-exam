#pragma once
#include <vector>
#include <functional>
#include <string>
#include <sstream>

using namespace std;

namespace stochastic {

    template<typename T>
    constexpr bool all(const vector<T>& input){
        for(const auto& e : input)
            if (!e)
                return false;
        return true;
    }

    template<typename T>
    bool all(const vector<T>& input, const function<bool(T)>& validator) {
        for(const auto& value : input) {
            if(!validator(value))
                return false;
        }
        return true;
    }

    template<typename T>
    constexpr bool any(const vector<T>& input){
        for(const auto e : input)
            if (e)
                return true;
        return false;
    }

    template<typename T>
    bool any(const vector<T>& input, const function<const bool(T)>& validator) {
        for(const auto value : input) {
            if(validator(value))
                return true;
        }
        return false;
    }

    template<typename T>
    string join(const vector<T>& input, const string& delimiter) {
        stringstream ss;
        const auto last = &(input.back());
        for(auto index = 0; index < input.size()-1; index++)
            ss << input[index] << delimiter;
        ss << input[input.size()-1];
        return ss.str();
    }

    template<typename T>
    constexpr vector<T> make_range(const size_t& size) {
        vector<T> result;
        for(auto i = 0; i < size; i++)
            result.push_back((T)i);
        return result;
    }

    template<typename T>
    constexpr vector<T> make_range(const size_t& lower, const size_t& upper) {
        vector<T> result;
        for(auto i = lower; i < upper; i++)
            result.push_back((T)i);
        return result;
    }
    template<typename T>
    vector<T> make_range(const size_t& size, const function<const T(const int)>& func) {
        vector<T> result; 
        for(auto i = 0; i < size; i++)
            result.push_back(func(i));
        return result;
    }
    template<typename T>
    vector<T> make_range(const size_t& lower, const size_t& upper, const function<const T(const int)>& func) {
        vector<T> result;
        for(auto i = lower; i < upper; i++)
            result.push_back(func(i));
        return result;
    }

    template<typename T1, typename T2>
    vector<T2> make_range(const vector<T1>& input, const function<T2(T1)>& func){
        vector<T2> result;
        for(auto value : input)
            result.push_back(func(value));
        return result;
    }

    template<typename T>
    constexpr T sum(const vector<T>& inputs) {
        auto result = 0;
        for(auto v : inputs)
            result += v;
        return result;
    }

    template<typename T>
    constexpr T mean(const vector<T>& inputs) {
        return sum(inputs)/inputs.size();
    }
}