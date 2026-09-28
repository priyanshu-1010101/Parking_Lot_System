#ifndef HOURLY_PRICING_STRATEGY_H
#define HOURLY_PRICING_STRATEGY_H

#include "PricingStrategy.h"

class HourlyPricingStrategy : public PricingStrategy
{
public:
    double calculateFee(VehicleType type, long durationInMinutes) override;
};

#endif
