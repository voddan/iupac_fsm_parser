//
// Created by Daniil_Vodopian on 9/19/2017.
//

#ifndef OPSIN_CPP_COLLECTIONHELPER_HPP
#define OPSIN_CPP_COLLECTIONHELPER_HPP

#include <vector>
#include <map>
#include <set>

template<typename TK, typename TV>
std::vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
    std::vector<TK> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.first);
    }
    return retval;
}

template<typename TK, typename TV>
std::vector<TV> extract_values(std::map<TK, TV> const& input_map) {
    std::vector<TV> retval;
    for (auto const& element : input_map) {
        retval.push_back(element.second);
    }
    return retval;
}

template<typename T>
std::set<T> vector2set(std::vector<T> const& input_vector) {
    std::set<T> retval;
    for (auto const& element : input_vector) {
        retval.insert(element);
    }
    return retval;
}

template<typename T>
std::vector<T> set2vector(std::set<T> const& input_set) {
    std::vector<T> retval;
    for (auto const& element : input_set) {
        retval.push_back(element);
    }
    return retval;
}

#endif //OPSIN_CPP_COLLECTIONHELPER_HPP
