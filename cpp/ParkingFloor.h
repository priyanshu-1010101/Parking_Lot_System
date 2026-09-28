#ifndef PARKING_FLOOR_H
#define PARKING_FLOOR_H

#include <memory>
#include <vector>
#include <map>
#include <utility>
#include "ParkingSpot.h"
#include "VehicleType.h"

class ParkingFloor
{
private:
    int floorNumber;
    std::vector<std::unique_ptr<ParkingSpot>> spots;

public:
    explicit ParkingFloor(int floorNumber);

    void addSpot(std::unique_ptr<ParkingSpot> spot);
    int getFloorNumber() const;

    ParkingSpot *findFreeSpot(VehicleType type);

    std::map<VehicleType, std::pair<int, int>> getOccupancyStatus() const;
};

#endif