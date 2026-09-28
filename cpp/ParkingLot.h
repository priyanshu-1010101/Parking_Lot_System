#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "ParkingFloor.h"
#include "Ticket.h"
#include "PricingStrategy.h"
#include "Vehicle.h"

class ParkingLot
{
private:
    std::vector<std::unique_ptr<ParkingFloor>> floors;
    std::unordered_map<std::string, std::unique_ptr<Ticket>> activeTickets;
    std::unique_ptr<PricingStrategy> pricingStrategy;
    int ticketCounter;

    ParkingLot();

public:
    ParkingLot(const ParkingLot &) = delete;
    ParkingLot &operator=(const ParkingLot &) = delete;

    static ParkingLot &getInstance();

    void addFloor(std::unique_ptr<ParkingFloor> floor);

    std::string parkVehicle(Vehicle *vehicle);

    double unparkVehicle(const std::string &ticketId);

    void printOccupancyStatus() const;
};

#endif
