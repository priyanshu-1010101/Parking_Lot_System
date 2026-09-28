#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle
{
public:
    explicit Car(const std::string &licensePlate)
    : Vehicle(licensePlate, VehicleType::CAR) {}
};

#endif
