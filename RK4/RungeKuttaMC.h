#ifndef RUNGEKUTTA_MC_H
#define RUNGEKUTTA_MC_H

#include "PayOff2.h"
#include "Random1.h"
#include <cmath>

// Template RK4 Monte Carlo for SDE: dS = r*S*dt + sigma*S*dW
template <typename T>
T RungeKuttaMonteCarlo(const PayOff<T>& thePayOff,
    T Expiry,
    T Spot,
    T Vol,
    T r,
    unsigned long NumberOfPaths,
    unsigned long TimeSteps = 100)
{
    T dt = Expiry / static_cast<T>(TimeSteps);
    T sqrt_dt = std::sqrt(dt);
    T discount = std::exp(-r * Expiry);
    T runningSum = 0;

    for (unsigned long i = 0; i < NumberOfPaths; ++i)
    {
        T S = Spot;

        for (unsigned long j = 0; j < TimeSteps; ++j)
        {
            T Z = GetOneGaussianByBoxMuller<T>();
            T dW = sqrt_dt * Z;

            // Coefficients Runge-Kutta 4
            T k1 = r * S * dt + Vol * S * dW;
            T k2 = r * (S + 0.5 * k1) * dt + Vol * (S + 0.5 * k1) * dW;
            T k3 = r * (S + 0.5 * k2) * dt + Vol * (S + 0.5 * k2) * dW;
            T k4 = r * (S + k3) * dt + Vol * (S + k3) * dW;

            S += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        }

        runningSum += thePayOff(S);
    }

    T mean = runningSum / static_cast<T>(NumberOfPaths);
    return discount * mean;
}

#endif
