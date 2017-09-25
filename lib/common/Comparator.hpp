//
// Created by Daniil_Vodopian on 9/20/2017.
//

#ifndef OPSIN_CPP_COMPARATOR_HPP
#define OPSIN_CPP_COMPARATOR_HPP

#include <winioctl.h>

template <typename Type>
class Comparator {
public:
    virtual int compare(Type *a, Type *b)= 0;

    virtual bool cmp(const Type &a, const Type &b) {
        return compare(a, b) <= 0;
    }
};

#endif //OPSIN_CPP_COMPARATOR_HPP
