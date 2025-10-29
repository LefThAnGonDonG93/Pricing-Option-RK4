#ifndef RANDOM1_H
#define RANDOM1_H

#include <cstdlib>
#include <cmath>

template <typename T>
T GetOneGaussianByBoxMuller()
{
    T x, y, sizeSquared;
    do
    {
        x = static_cast<T>(2.0) * rand() / static_cast<T>(RAND_MAX) - static_cast<T>(1.0);
        y = static_cast<T>(2.0) * rand() / static_cast<T>(RAND_MAX) - static_cast<T>(1.0);
        sizeSquared = x * x + y * y;
    } while (sizeSquared >= static_cast<T>(1.0));

    return x * std::sqrt(-2.0 * std::log(sizeSquared) / sizeSquared);
}

#endif
