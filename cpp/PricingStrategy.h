#ifndef PRICING_STRATEGY_H
#define PRICING_STRATEGY_H

#include "VehicleType.h"

class PricingStrategy
{
public:
    virtual ~PricingStrategy() = default;
    virtual double calculateFee(VehicleType type, long durationInMinutes) = 0;
};

#endif
