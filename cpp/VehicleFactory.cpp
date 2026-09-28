#include "VehicleFactory.h"
#include "Car.h"
#include "Bike.h"
#include "Truck.h"
#include <stdexcept>

std::unique_ptr<Vehicle> VehicleFactory::createVehicle(VehicleType type, const std::string &licensePlate)
{
    switch (type)
    {
    case VehicleType::CAR:
        return std::make_unique<Car>(licensePlate);
    case VehicleType::BIKE:
        return std::make_unique<Bike>(licensePlate);
    case VehicleType::TRUCK:
        return std::make_unique<Truck>(licensePlate);
    default:
        throw std::invalid_argument("Unknown vehicle type");
    }
}
