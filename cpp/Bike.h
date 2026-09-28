#ifndef BIKE_H
#define BIKE_H

#include "Vehicle.h"

class Bike : public Vehicle
{
public:
    explicit Bike(const std::string &licensePlate)
        : Vehicle(licensePlate, VehicleType::BIKE) {}
};

#endif
