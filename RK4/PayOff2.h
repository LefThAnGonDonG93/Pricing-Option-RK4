#ifndef PAYOFF2_H
#define PAYOFF2_H

#include <algorithm>

template <typename T>
class PayOff
{
public:
    PayOff() {}
    virtual T operator()(T Spot) const = 0;
    virtual ~PayOff() {}
};

template <typename T>
class PayOffCall : public PayOff<T>
{
public:
    PayOffCall(T Strike_) : Strike(Strike_) {}
    virtual T operator()(T Spot) const override
    {
        return std::max(Spot - Strike, static_cast<T>(0.0));
    }
    virtual ~PayOffCall() {}

private:
    T Strike;
};

template <typename T>
class PayOffPut : public PayOff<T>
{
public:
    PayOffPut(T Strike_) : Strike(Strike_) {}
    virtual T operator()(T Spot) const override
    {
        return std::max(Strike - Spot, static_cast<T>(0.0));
    }
    virtual ~PayOffPut() {}

private:
    T Strike;
};

#endif
