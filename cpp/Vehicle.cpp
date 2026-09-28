#include "Vehicle.h"

Vehicle::Vehicle(const std::string &licensePlate, VehicleType type)
    : licensePlate(licensePlate), type(type) {}

std::string Vehicle::getLicensePlate() const
{
    return licensePlate;
}

VehicleType Vehicle::getType() const
{
    return type;
}
