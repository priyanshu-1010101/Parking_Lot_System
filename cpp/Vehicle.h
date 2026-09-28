#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "VehicleType.h"

class Vehicle
{
protected:
    std::string licensePlate;
    VehicleType type;

public:
    Vehicle(const std::string &licensePlate, VehicleType type);
    virtual ~Vehicle() = default;

    std::string getLicensePlate() const;
    VehicleType getType() const;
};

#endif
