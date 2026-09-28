#ifndef VEHICLE_TYPE_H
#define VEHICLE_TYPE_H

#include <string>

enum class VehicleType
{
    BIKE,
    CAR,
    TRUCK
};

inline std::string vehicleTypeToString(VehicleType type)
{
    switch (type)
    {
    case VehicleType::BIKE:
        return "Bike";
    case VehicleType::CAR:
        return "Car";
    case VehicleType::TRUCK:
        return "Truck";
    default:
        return "Unknown";
    }
}

#endif
