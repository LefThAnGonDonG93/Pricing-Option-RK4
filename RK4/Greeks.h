#ifndef GREEKS_H
#define GREEKS_H

#include "RungeKuttaMC.h"

template <typename T>
struct Greeks {
    T delta, gamma, vega, rho, theta;
};

template <typename T>
Greeks<T> ComputeGreeks(
    const PayOff<T>& payoff,
    T expiry,
    T spot,
    T vol,
    T r,
    unsigned long numPaths,
    unsigned long timeSteps = 100, // <-- cohérent avec RK4
    T h = 0.01
) {
    Greeks<T> g;

    // Prix de base
    T base = RungeKuttaMonteCarlo(payoff, expiry, spot, vol, r, numPaths, timeSteps);

    // Delta & Gamma
    T up = RungeKuttaMonteCarlo(payoff, expiry, spot + h, vol, r, numPaths, timeSteps);
    T down = RungeKuttaMonteCarlo(payoff, expiry, spot - h, vol, r, numPaths, timeSteps);
    g.delta = (up - down) / (2.0 * h);
    g.gamma = (up - 2.0 * base + down) / (h * h);

    // Vega
    T vUp = RungeKuttaMonteCarlo(payoff, expiry, spot, vol + h, r, numPaths, timeSteps);
    T vDown = RungeKuttaMonteCarlo(payoff, expiry, spot, vol - h, r, numPaths, timeSteps);
    g.vega = (vUp - vDown) / (2.0 * h);

    // Rho
    T rUp = RungeKuttaMonteCarlo(payoff, expiry, spot, vol, r + h, numPaths, timeSteps);
    T rDown = RungeKuttaMonteCarlo(payoff, expiry, spot, vol, r - h, numPaths, timeSteps);
    g.rho = (rUp - rDown) / (2.0 * h);

    // Theta (attention au signe)
    T tUp = RungeKuttaMonteCarlo(payoff, expiry + h, spot, vol, r, numPaths, timeSteps);
    T tDown = RungeKuttaMonteCarlo(payoff, expiry - h, spot, vol, r, numPaths, timeSteps);
    g.theta = (tDown - tUp) / (2.0 * h); // convention: θ < 0 quand le temps passe

    return g;
}

#endif
