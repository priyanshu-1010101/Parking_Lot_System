#include "ParkingFloor.h"

ParkingFloor::ParkingFloor(int floorNumber) : floorNumber(floorNumber) {}

void ParkingFloor::addSpot(std::unique_ptr<ParkingSpot> spot)
{
    spots.push_back(std::move(spot));
}

int ParkingFloor::getFloorNumber() const
{
    return floorNumber;
}

ParkingSpot *ParkingFloor::findFreeSpot(VehicleType type)
{
    for (auto &spot : spots)
    {
        if (spot->getSpotType() == type && spot->isFree())
        {
            return spot.get();
        }
    }
    return nullptr;
}

std::map<VehicleType, std::pair<int, int>> ParkingFloor::getOccupancyStatus() const
{
    std::map<VehicleType, std::pair<int, int>> status;
    for (auto &spot : spots)
    {
        auto &entry = status[spot->getSpotType()];
        entry.second++; // total
        if (!spot->isFree())
            entry.first++; // occupied
    }
    return status;
}
