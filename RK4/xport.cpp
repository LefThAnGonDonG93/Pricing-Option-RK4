#include "PayOff2.h"
#include "RungeKuttaMC.h"
#include "Greeks.h"

// --- Monte Carlo price export for Excel ---
extern "C" __declspec(dllexport)
double PriceOption_MC(int optionType, double S0, double K, double r, double sigma, double T,
    unsigned long paths, unsigned long timeSteps)
{
    PayOff<double>* payoff;

    if (optionType == 0)
        payoff = new PayOffCall<double>(K);
    else
        payoff = new PayOffPut<double>(K);

    double price = RungeKuttaMonteCarlo(*payoff, T, S0, sigma, r, paths, timeSteps);

    delete payoff;
    return price;
}

// --- Greeks exports for Excel ---
extern "C" __declspec(dllexport)
double Delta(int optionType, double S0, double K, double r, double sigma, double T,
    unsigned long paths, unsigned long timeSteps)
{
    PayOff<double>* payoff = (optionType == 0)
        ? static_cast<PayOff<double>*>(new PayOffCall<double>(K))
        : static_cast<PayOff<double>*>(new PayOffPut<double>(K));

    auto g = ComputeGreeks(*payoff, T, S0, sigma, r, paths, timeSteps);
    delete payoff;
    return g.delta;
}

extern "C" __declspec(dllexport)
double Gamma(int optionType, double S0, double K, double r, double sigma, double T,
    unsigned long paths, unsigned long timeSteps)
{
    PayOff<double>* payoff = (optionType == 0)
        ? static_cast<PayOff<double>*>(new PayOffCall<double>(K))
        : static_cast<PayOff<double>*>(new PayOffPut<double>(K));

    auto g = ComputeGreeks(*payoff, T, S0, sigma, r, paths, timeSteps);
    delete payoff;
    return g.gamma;
}

extern "C" __declspec(dllexport)
double Vega(int optionType, double S0, double K, double r, double sigma, double T,
    unsigned long paths, unsigned long timeSteps)
{
    PayOff<double>* payoff = (optionType == 0)
        ? static_cast<PayOff<double>*>(new PayOffCall<double>(K))
        : static_cast<PayOff<double>*>(new PayOffPut<double>(K));

    auto g = ComputeGreeks(*payoff, T, S0, sigma, r, paths, timeSteps);
    delete payoff;
    return g.vega;
}

extern "C" __declspec(dllexport)
double Theta(int optionType, double S0, double K, double r, double sigma, double T,
    unsigned long paths, unsigned long timeSteps)
{
    PayOff<double>* payoff = (optionType == 0)
        ? static_cast<PayOff<double>*>(new PayOffCall<double>(K))
        : static_cast<PayOff<double>*>(new PayOffPut<double>(K));

    auto g = ComputeGreeks(*payoff, T, S0, sigma, r, paths, timeSteps);
    delete payoff;
    return g.theta;
}

extern "C" __declspec(dllexport)
double Rho(int optionType, double S0, double K, double r, double sigma, double T,
    unsigned long paths, unsigned long timeSteps)
{
    PayOff<double>* payoff = (optionType == 0)
        ? static_cast<PayOff<double>*>(new PayOffCall<double>(K))
        : static_cast<PayOff<double>*>(new PayOffPut<double>(K));

    auto g = ComputeGreeks(*payoff, T, S0, sigma, r, paths, timeSteps);
    delete payoff;
    return g.rho;
}
