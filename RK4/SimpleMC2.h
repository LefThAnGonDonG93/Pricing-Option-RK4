#ifndef SIMPLEMC2_H
#define SIMPLEMC2_H

#include "PayOff2.h"
#include "Random1.h"
#include <cmath>

template <typename T>
T SimpleMonteCarlo2(const PayOff<T>& thePayOff,
    T Expiry,
    T Spot,
    T Vol,
    T r,
    unsigned long NumberOfPaths)
{
    T variance = Vol * Vol * Expiry;
    T rootVariance = std::sqrt(variance);
    T itoCorrection = -0.5 * variance;
    T movedSpot = Spot * std::exp(r * Expiry + itoCorrection);

    T runningSum = 0;
    for (unsigned long i = 0; i < NumberOfPaths; i++)
    {
        T thisGaussian = GetOneGaussianByBoxMuller<T>();
        T thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        runningSum += thePayOff(thisSpot);
    }

    T mean = runningSum / static_cast<T>(NumberOfPaths);
    mean *= std::exp(-r * Expiry);
    return mean;
}

#endif
