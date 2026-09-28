#ifndef PARKING_SPOT_H
#define PARKING_SPOT_H

#include <string>
#include "VehicleType.h"

class ParkingSpot
{
private:
    std::string spotId;
    VehicleType spotType;
    bool occupied;

public:
    ParkingSpot(const std::string &spotId, VehicleType spotType);

    std::string getSpotId() const;
    VehicleType getSpotType() const;
    bool isFree() const;

    void occupy();
    void vacate();
};

#endif
