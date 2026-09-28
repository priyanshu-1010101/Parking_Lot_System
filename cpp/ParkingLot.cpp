#include "ParkingLot.h"
#include "HourlyPricingStrategy.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>

ParkingLot::ParkingLot() : ticketCounter(1000)
{
    pricingStrategy = std::make_unique<HourlyPricingStrategy>();
}

ParkingLot &ParkingLot::getInstance()
{
    static ParkingLot instance; 
    return instance;
}

void ParkingLot::addFloor(std::unique_ptr<ParkingFloor> floor)
{
    floors.push_back(std::move(floor));
    std::sort(floors.begin(), floors.end(),
              [](const std::unique_ptr<ParkingFloor> &a, const std::unique_ptr<ParkingFloor> &b)
              {
                  return a->getFloorNumber() < b->getFloorNumber();
              });
}

std::string ParkingLot::parkVehicle(Vehicle *vehicle)
{
    for (auto &floor : floors)
    {
        ParkingSpot *spot = floor->findFreeSpot(vehicle->getType());
        if (spot != nullptr)
        {
            spot->occupy();
            ticketCounter++;
            std::string ticketId = "T" + std::to_string(ticketCounter);
            auto entryTime = std::chrono::system_clock::now();

            auto ticket = std::make_unique<Ticket>(ticketId, vehicle, spot, entryTime);
            activeTickets[ticketId] = std::move(ticket);

            std::time_t entryC = std::chrono::system_clock::to_time_t(entryTime);
            std::cout << "[ENTRY] " << vehicleTypeToString(vehicle->getType())
                      << " (" << vehicle->getLicensePlate() << ") parked at Floor "
                      << floor->getFloorNumber() << ", Spot " << spot->getSpotId() << "\n";
            std::cout << "        Ticket ID: " << ticketId
                      << " | Entry Time: " << std::ctime(&entryC);
            return ticketId;
        }
    }

    std::cout << "[ERROR] No available spot for vehicle type: "
              << vehicleTypeToString(vehicle->getType()) << "\n";
    std::cout << "        " << vehicleTypeToString(vehicle->getType())
              << " (" << vehicle->getLicensePlate() << ") - Entry Denied\n";
    return "";
}

double ParkingLot::unparkVehicle(const std::string &ticketId)
{
    auto it = activeTickets.find(ticketId);
    if (it == activeTickets.end())
    {
        std::cout << "[ERROR] Invalid ticket ID: " << ticketId << "\n";
        return -1;
    }

    Ticket *ticket = it->second.get();
    auto exitTime = std::chrono::system_clock::now();
    ticket->setExitTime(exitTime);

    long minutes = std::chrono::duration_cast<std::chrono::minutes>(
                       exitTime - ticket->getEntryTime())
                       .count();

    double fee = pricingStrategy->calculateFee(ticket->getVehicle()->getType(), minutes);

    ticket->getSpot()->vacate();

    std::cout << "[EXIT] " << vehicleTypeToString(ticket->getVehicle()->getType())
              << " (" << ticket->getVehicle()->getLicensePlate() << ") left Spot "
              << ticket->getSpot()->getSpotId() << "\n";
    std::cout << "       Ticket ID: " << ticketId << "\n";
    std::cout << "       Duration: " << minutes << " minutes\n";
    std::cout << "       Fee Charged: Rs." << fee << "\n";

    activeTickets.erase(it);
    return fee;
}

void ParkingLot::printOccupancyStatus() const
{
    std::cout << "\n----- Current Occupancy Status -----\n";
    for (auto &floor : floors)
    {
        std::cout << "Floor " << floor->getFloorNumber() << ":\n";
        auto status = floor->getOccupancyStatus();
        for (auto &entry : status)
        {
            std::cout << "  " << vehicleTypeToString(entry.first) << " Spots: "
                      << entry.second.first << "/" << entry.second.second << " occupied\n";
        }
    }
}