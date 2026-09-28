#include "ParkingSpot.h"

ParkingSpot::ParkingSpot(const std::string &spotId, VehicleType spotType)
    : spotId(spotId), spotType(spotType), occupied(false) {}

std::string ParkingSpot::getSpotId() const
{
    return spotId;
}

VehicleType ParkingSpot::getSpotType() const
{
    return spotType;
}

bool ParkingSpot::isFree() const
{
    return !occupied;
}

void ParkingSpot::occupy()
{
    occupied = true;
}

void ParkingSpot::vacate()
{
    occupied = false;
}
