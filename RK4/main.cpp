#include <iostream>
#include "PayOff2.h"
#include "Greeks.h"

using namespace std;

int main()
{
    using T = double;

    T Expiry;
    T Strike;
    T Spot;
    T Vol;
    T r;
    unsigned long NumberOfPaths;
    unsigned long TimeSteps;

    cout << "\nEnter expiry: ";
    cin >> Expiry;

    cout << "\nEnter strike: ";
    cin >> Strike;

    cout << "\nEnter spot: ";
    cin >> Spot;

    cout << "\nEnter volatility: ";
    cin >> Vol;

    cout << "\nEnter risk-free rate: ";
    cin >> r;

    cout << "\nEnter number of Monte Carlo paths: ";
    cin >> NumberOfPaths;

    cout << "\nEnter number of time steps (for RK4 integration): ";
    cin >> TimeSteps;

    unsigned long OptionType;
    cout << "\nEnter 0 for Call, 1 for Put: ";
    cin >> OptionType;

    PayOff<T>* thePayOffPtr = nullptr;

    if (OptionType == 0)
        thePayOffPtr = new PayOffCall<T>(Strike);
    else
        thePayOffPtr = new PayOffPut<T>(Strike);

    // ---- Calcul du prix par Monte Carlo Runge-Kutta 4 ----
    T Price = RungeKuttaMonteCarlo(*thePayOffPtr, Expiry, Spot, Vol, r, NumberOfPaths, TimeSteps);

    // ---- Calcul des Greeks ----
    Greeks<T> g = ComputeGreeks(*thePayOffPtr, Expiry, Spot, Vol, r, NumberOfPaths);

    cout << "\n===== Résultats (Méthode RK4) =====\n";
    cout << "Prix RK4 Monte Carlo : " << Price << "\n";
    cout << "Delta : " << g.delta << "\n";
    cout << "Gamma : " << g.gamma << "\n";
    cout << "Vega  : " << g.vega << "\n";
    cout << "Rho   : " << g.rho << "\n";
    cout << "Theta : " << g.theta << "\n";
    cout << "===================================\n";

    delete thePayOffPtr;

    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}
