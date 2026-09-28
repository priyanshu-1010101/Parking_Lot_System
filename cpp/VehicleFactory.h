#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H

#include <memory>
#include <string>
#include "Vehicle.h"
#include "VehicleType.h"

class VehicleFactory
{
public:
    static std::unique_ptr<Vehicle> createVehicle(VehicleType type, const std::string &licensePlate);
};

#endif
