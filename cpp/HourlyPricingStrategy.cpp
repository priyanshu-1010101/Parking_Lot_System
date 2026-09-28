#include "HourlyPricingStrategy.h"
#include <cmath>

double HourlyPricingStrategy::calculateFee(VehicleType type, long durationInMinutes)
{
    double hours = std::ceil(durationInMinutes / 60.0);
    if (hours < 1)
        hours = 1;

    switch (type)
    {
    case VehicleType::BIKE:
        return hours * 20;
    case VehicleType::CAR:
        return hours * 50;
    case VehicleType::TRUCK:
        return hours * 100;
    default:
        return 0;
    }
}
